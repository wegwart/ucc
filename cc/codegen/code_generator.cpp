#include <codegen/code_generator.h>
#include <cassert>

namespace codegen {

    CodeGenerator::CodeGenerator(const std::string& programName)
    {
        m_context = std::make_unique<llvm::LLVMContext>();
        m_module = std::make_unique<llvm::Module>(programName, *m_context);
        m_builder = std::make_unique<llvm::IRBuilder<>>(*m_context);
    }

    void CodeGenerator::genFunction(ast::Function* function)
    {
        llvm::Function* codeFunction = m_module->getFunction(function->name());

        if (codeFunction != nullptr)
            assert(false && "function has already been generated");
        
        if (!function->hasImplementation())
            return;
        
        llvm::BasicBlock* impl =
            llvm::BasicBlock::Create(*m_context, function->name(), codeFunction);
        m_builder->SetInsertPoint(impl);

        // TODO: bring function arguments into scope! -> ScopeStack?

        genStatements(function->getImplementation());      
    }

    void CodeGenerator::genStatements(const ast::Statement& stmt)
    {
        // TODO: generate statements
    }

}