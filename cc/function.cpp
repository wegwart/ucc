#include <function.h>

std::vector<Function*> Function::s_functions;

Function::Function(const std::string& name)
    : m_name(name)
{ }

const std::string& Function::name() const
{
    return m_name;
}

Function* Function::declare(const std::string& name)
{
    for (const auto func : s_functions)
    {
        if (func->name() == name)
        {
            // TODO: make sure the signature matches!
            return func;
        }
    }

    auto func = new Function(name);
    s_functions.push_back(func);
    return func;
}

void Function::define()
{
    m_definition = new EmptyStatement();
}

void Function::define(Statement* stmts)
{
    m_definition = stmts;
}
