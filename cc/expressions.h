#pragma once

#include <stdint.h>
#include <string>

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

class StrLiteralExpression : public Expression
{
  public:
    StrLiteralExpression(const char* str);

  private:
    std::string m_str;
};

class VariableExpression : public Expression
{
  public:
    VariableExpression(const char* variable_name);

  private:
    std::string m_varname;
};