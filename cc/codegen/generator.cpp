#include <codegen/generator.h>
#include <cassert>

namespace codegen {

    CodeGenerator::CodeGenerator(const std::string& programName)
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

    void CodeGenerator::visitFunctionDeclaration(
        std::shared_ptr<const ast::FunctionDeclaration> functionDeclaration)
    {
        if (m_module->getFunction(functionDeclaration->getName()))
        {
            printf("warning: function has already been declared\n");
            return;
        }

        printf("llvm gen: declaring function %s()\n", functionDeclaration->getName().c_str());

        // generate the function type
        std::vector<llvm::Type*> args;
        auto returnType = llvm::Type::getVoidTy(*m_context);
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
            printf("function hasn't yet been declared!\n");
            return;
        }

        printf("llvm-gen: generating code for function %s()\n", declaration->getName().c_str());  
        
        // llvm::BasicBlock* impl =
        //     llvm::BasicBlock::Create(*m_context, function->name(), codeFunction);
        // m_builder->SetInsertPoint(impl);

        // TODO: bring function arguments into scope! -> ScopeStack?
        // TODO: generate code for the statements

    }

}