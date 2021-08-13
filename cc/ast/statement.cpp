#include <ast/visitor.h>
#include <ast/statement.h>
#include <ast/expression.h>

using namespace ast;

StatementList::StatementList(size_t stmt)
{
    add(stmt);
}

size_t StatementList::add(size_t stmt)
{
    m_statements.push_back(
        Ast::get().resolve<const Statement>(stmt)
    );
    return getId();
}

void StatementList::visit(AstVisitor* visitor) const
{
    // visit all the individual statements instead
    for (auto& stmt : m_statements)
        stmt->visit(visitor);
}

ReturnStatement::ReturnStatement(size_t expression)
{
    m_expression = Ast::get()
        .resolve<const Expression>(expression); 
}

void ReturnStatement::visit(AstVisitor* visitor) const
{
    visitor->visitReturnStatement(
        Ast::get().resolve<const ReturnStatement>(getId()));
}