#pragma once

#include <string>
#include <vector>
#include "cc.h"
#include "parser.h"
#include <statement.h>

class Function
{
  public:
    const std::string& name() const;

    static Function* declare(const std::string& name);

    void define();
    void define(Statement* stmts);

  private:
    std::string m_name;
    // Type m_returnType;
    // ArgList* m_arguments;

    // If m_definition is nullptr, then the function
    // hasn't been defined, yet.
    Statement* m_definition;

  private:
    Function(const std::string& name);
    static std::vector<Function*> s_functions;
};