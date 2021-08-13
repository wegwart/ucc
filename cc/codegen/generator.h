#pragma once

#include <memory>

#include <ast/visitor.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>

namespace ast {

    class FunctionDeclaration;
    class FunctionDefinition;
    class ReturnStatement;
    class IntLiteral;
    
}

namespace codegen {

    class CodeGenerator : public ast::AstVisitor
    {
      public:
        CodeGenerator(const std::string& programName);
        ~CodeGenerator();

        void print();

        void visitFunctionDeclaration(
            std::shared_ptr<const ast::FunctionDeclaration> functionDeclaration) override;        
        
        void visitFunctionDefinition(
            std::shared_ptr<const ast::FunctionDefinition> functionDefinition) override;
        
        void visitReturnStatement(
            std::shared_ptr<const ast::ReturnStatement> returnStatement) override;

        void visitIntLiteralExpr(
            std::shared_ptr<const ast::IntLiteral> intLiteralExpr) override;
      
      private:
        std::unique_ptr<llvm::Module> m_module;
        std::unique_ptr<llvm::LLVMContext> m_context;
        std::unique_ptr<llvm::IRBuilder<>> m_builder;

        // Since we cannot return results from a visitor,
        // an AST child's code generation result is stored
        // in the following member variable. 
        llvm::Value* m_result;
    };
    
} // namespace codegen
