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
            printf("function '%s' redeclared\n", name.c_str());
            // make sure the signature matches!
            return func;
        }
    }

    auto func = new Function(name);
    s_functions.push_back(func);
    printf("function '%s' declared\n", name.c_str());
    return func;
}

void Function::define()
{
    m_definition = new StatementList();
}

void Function::define(StatementList* stmts)
{
    m_definition = stmts;
}
