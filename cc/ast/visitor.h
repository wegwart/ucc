#pragma once

namespace ast {

    class FunctionDeclaration;
    class FunctionDefinition;

    class AstVisitor
    {
    public:
        AstVisitor() = default;
        virtual ~AstVisitor() = default;

        virtual void visitFunctionDeclaration(
            std::shared_ptr<const FunctionDeclaration> functionDeclaration) = 0;        
        
        virtual void visitFunctionDefinition(
            std::shared_ptr<const FunctionDefinition> functionDefinition) = 0;
    };

}