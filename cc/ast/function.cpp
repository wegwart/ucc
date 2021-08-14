#include <ast/visitor.h>
#include <ast/function.h>
#include <ast/statement.h>
#include <ast/type.h>

using namespace ast;

FunctionDeclaration::FunctionDeclaration(const std::string& name, size_t returnType)
    : m_name(name)
{
    m_returnType = *Ast::get().resolve<Typename>(returnType);
}

void FunctionDeclaration::visit(AstVisitor* visitor) const
{
    visitor->visitFunctionDeclaration(Ast::get().resolve<FunctionDeclaration>(getId()));
}

const std::string& FunctionDeclaration::getName() const
{
    return m_name;
}


const Typename& FunctionDeclaration::getReturnType() const
{
    return m_returnType;
}

FunctionDefinition::FunctionDefinition(size_t decl, size_t stmt)
{
    m_declaration = Ast::get().resolve<const FunctionDeclaration>(decl);
    m_implementation = Ast::get().resolve<const Statement>(stmt);
}

std::shared_ptr<const FunctionDeclaration> FunctionDefinition::getDeclaration() const
{
    return m_declaration;
}

std::shared_ptr<const Statement> FunctionDefinition::getImplementation() const
{
    return m_implementation;
}

void FunctionDefinition::visit(AstVisitor* visitor) const
{
    visitor->visitFunctionDefinition(Ast::get().resolve<FunctionDefinition>(getId()));
}