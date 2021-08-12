#include <ast/statement.h>

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