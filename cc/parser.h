#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "expressions.h"

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
