#include <cassert>
#include <cstdint>

#include <ast/function.h>
#include <ast/statement.h>
#include <ast/literals.h>
#include <typesys/type.h>
#include <typesys/typemap.h>
#include <codegen/generator.h>

#include <llvm/Support/raw_ostream.h>

namespace codegen {

    CodeGenerator::CodeGenerator(const std::string& programName, typesys::TypeMap& typeMap)
        : m_types(typeMap)
    {
        m_context = std::make_unique<llvm::LLVMContext>();
        m_module = std::make_unique<llvm::Module>(programName, *m_context);
        m_builder = std::make_unique<llvm::IRBuilder<>>(*m_context);
    }

    CodeGenerator::~CodeGenerator()
    {
        // delete llvm objects in the correct order,
        // so they don't generate a segmentation fault.
        m_builder.reset();
        m_module.reset();
        m_context.reset();
    }

    void CodeGenerator::print()
    {
        m_module->print(llvm::outs(), nullptr);
    }

    llvm::Type* CodeGenerator::getLlvmType(const ast::Typename& type)
    {
        auto actualType = m_types.findType(type);
        
        if (actualType->isInteger())
            return llvm::Type::getIntNTy(*m_context, actualType->getBitSize());
        
        assert(false);
        return nullptr;
    }

    void CodeGenerator::visitFunctionDeclaration(
        std::shared_ptr<const ast::FunctionDeclaration> functionDeclaration)
    {
        if (m_module->getFunction(functionDeclaration->getName()))
        {
            // function has already been declared.
            return;
        }

        // generate the function type
        std::vector<llvm::Type*> args;
        auto returnType = getLlvmType(functionDeclaration->getReturnType());
        auto functionType = llvm::FunctionType::get(returnType, args, false);

        // declare the function
        auto function = llvm::Function::Create(
            functionType,
            llvm::Function::ExternalLinkage,
            functionDeclaration->getName(),
            m_module.get()
        );
    }       
    
    void CodeGenerator::visitFunctionDefinition(
        std::shared_ptr<const ast::FunctionDefinition> functionDefinition)
    {
        auto declaration = functionDefinition->getDeclaration();

        auto function = m_module->getFunction(declaration->getName());
        if (!function)
        {
            // function has already been implemented
            return;
        }

        llvm::BasicBlock* impl = // Do I have to delete this?
            llvm::BasicBlock::Create(*m_context, declaration->getName(), function);
        m_builder->SetInsertPoint(impl);

        functionDefinition->getImplementation()->visit(this);
    }

    void CodeGenerator::visitReturnStatement(
        std::shared_ptr<const ast::ReturnStatement> returnStatement)
    {
        m_result = nullptr;
        if (returnStatement->hasValue())
        {
            // if a return value expression was passed to the return
            // operator, first evaluate it and then return the result
            // m_result will be filled with the return value.
            returnStatement->getExpression()->visit(this);
        }

        m_builder->CreateRet(m_result);
    }


    void CodeGenerator::visitIntLiteralExpr(
        std::shared_ptr<const ast::IntLiteral> intLiteralExpr)
    {
        auto value = intLiteralExpr->getValue();

        auto type = llvm::IntegerType::getInt32Ty(*m_context);
        if (value > UINT32_MAX)
            type = llvm::IntegerType::getInt64Ty(*m_context);
    
        m_result = llvm::ConstantInt::get(type, llvm::APInt(32, value));
    }

}