#pragma once

#include <memory>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

namespace codegen {

    class CodeGenerator
    {
      public:
        CodeGenerator(const std::string& programName);
        ~CodeGenerator() = default;
      
      private:
        std::unique_ptr<llvm::Module> m_module;
        std::unique_ptr<llvm::LLVMContext> m_context;
        std::unique_ptr<llvm::IRBuilder<>> m_builder;
    };
    
} // namespace codegen
