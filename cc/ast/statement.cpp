#include <ast/statement.h>

using namespace ast;

StatementList::StatementList(Statement* stmt)
{
    add(stmt);
}

StatementList* StatementList::add(Statement* stmt)
{
    m_statements.push_back(stmt);
    return this;
}