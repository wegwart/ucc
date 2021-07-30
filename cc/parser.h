#pragma once

#include <stdint.h>
#include <string>
#include <vector>

class Expression
{
  public:
    Expression() = default;
};

class IntLiteralExpression : public Expression
{
  public:
    IntLiteralExpression(const char* num_str, int base = 10);

  private:
    uint64_t m_num;
};

class VariableExpression : public Expression
{
  public:
    VariableExpression(const char* variable_name);

  private:
    std::string m_varname;
};

class Statement
{
  public:
    Statement() = default;
};

class EmptyStatement : public Statement
{
  public:
    EmptyStatement() = default;
};

class ReturnStatement : public Statement
{
  public:
    ReturnStatement(Expression* expr);

  private:
    Expression* m_expr;
};
