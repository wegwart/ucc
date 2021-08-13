#include <ast/literals.h>
#include <ast/visitor.h>

using namespace ast;

IntLiteral::IntLiteral(uint64_t value)
    : m_value(value)
{ }


uint64_t IntLiteral::getValue() const
{
    return m_value;
}

void IntLiteral::visit(AstVisitor* visitor) const
{
    visitor->visitIntLiteralExpr(Ast::get().resolve<IntLiteral>(getId()));
}