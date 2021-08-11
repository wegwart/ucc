#pragma once

#include <memory>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

#include <ast/function.h>

namespace codegen {

    class CodeGenerator
    {
      public:
        CodeGenerator(const std::string& programName);
        ~CodeGenerator() = default;

        void genFunction(ast::Function* function);
        void genStatements(const ast::Statement& stmt);
      
      private:
        std::unique_ptr<llvm::Module> m_module;
        std::unique_ptr<llvm::LLVMContext> m_context;
        std::unique_ptr<llvm::IRBuilder<>> m_builder;
    };
    
} // namespace codegen
