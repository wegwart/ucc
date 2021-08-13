#pragma once

#include <string>
#include <ast/object.h>

namespace ast {

    class Statement;

    class FunctionDeclaration : public AstObject
    {
      public:
        FunctionDeclaration(const std::string& name);

        const std::string& getName() const;

        void visit(AstVisitor* visitor) const override;
      
      private:
        std::string m_name;
    };

    class FunctionDefinition : public AstObject
    {
      public:
        FunctionDefinition(size_t decl, size_t stmt);

        std::shared_ptr<const FunctionDeclaration> getDeclaration() const;
        std::shared_ptr<const Statement> getImplementation() const;

        void visit(AstVisitor* visitor) const override;
      
      private:
        std::shared_ptr<const FunctionDeclaration> m_declaration;
        std::shared_ptr<const Statement> m_implementation;
    };

}