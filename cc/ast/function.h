#pragma once

#include <string>
#include <ast/type.h>
#include <ast/expression.h>
#include <ast/object.h>

namespace ast
{
  class Statement;
  class Typename;

  class FunctionDeclaration : public AstObject
  {
  public:
    FunctionDeclaration(const std::string &name, size_t returnType);

    const std::string &getName() const;
    const Typename &getReturnType() const;

    void visit(AstVisitor *visitor) const override;

  private:
    std::string m_name;
    Typename m_returnType;
  };

  class FunctionDefinition : public AstObject
  {
  public:
    FunctionDefinition(size_t decl, size_t stmt);

    std::shared_ptr<const FunctionDeclaration> getDeclaration() const;
    std::shared_ptr<const Statement> getImplementation() const;

    void visit(AstVisitor *visitor) const override;

  private:
    std::shared_ptr<const FunctionDeclaration> m_declaration;
    std::shared_ptr<const Statement> m_implementation;
  };

  class FunctionCall : public Expression
  {
  public:
    FunctionCall(size_t expression);

    std::shared_ptr<const Expression> getExpression() const;

    void visit(AstVisitor *visitor) const override;

  private:
    std::shared_ptr<const Expression> m_expression;
  };

}