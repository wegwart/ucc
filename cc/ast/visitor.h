#pragma once

#include <memory>

namespace ast {

    class FunctionDeclaration;
    class FunctionDefinition;
    class ReturnStatement;
    class IntLiteral;
    class VarReference;

    class AstVisitor
    {
    public:
        AstVisitor() = default;
        virtual ~AstVisitor() = default;

        virtual void visitFunctionDeclaration(
            std::shared_ptr<const FunctionDeclaration> functionDeclaration) = 0;        
        
        virtual void visitFunctionDefinition(
            std::shared_ptr<const FunctionDefinition> functionDefinition) = 0;

        virtual void visitReturnStatement(
          std::shared_ptr<const ReturnStatement> returnStatement) = 0;
        
        virtual void visitIntLiteralExpr(
            std::shared_ptr<const IntLiteral> intLiteralExpr) = 0;

        virtual void visitVarReference(
            std::shared_ptr<const VarReference> variable) 
            {

            }
    };

}