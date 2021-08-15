#include <ast/variables.h>
#include <ast/visitor.h>

using namespace ast;

VarReference::VarReference(const std::string& value)
    : m_value(value)
{ }


const std::string& VarReference::getIdentifier() const
{
    return m_value;
}

void VarReference::visit(AstVisitor* visitor) const
{
    visitor->visitVarReference(Ast::get().resolve<VarReference>(getId()));
}