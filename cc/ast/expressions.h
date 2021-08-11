#pragma once

#include <cstdint>
#include <string>

class Expression
{
  public:
    Expression() = default;
    virtual ~Expression() = default;
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
    StrLiteralExpression(const char* str)
      : m_str(str)
    { }

  private:
    std::string m_str;
};

class VariableExpression : public Expression
{
  public:
    VariableExpression(const char* variable_name)
      : m_name(variable_name)
    { }

  private:
    std::string m_name;
};

class UnaryExpr : public Expression
{
  public:
    enum UnaryOp
    {
        Negative,
        AddressOf,
        SizeOf,
        Inverting,
        Negation,
        Deref
    };

    UnaryExpr(UnaryOp op, Expression* expr)
      : m_expr(expr)
      , m_operation(op)
    { }
  
  private:
    Expression* m_expr;
    UnaryOp m_operation;
};

class BinaryExpr : public Expression
{
  public:
    enum BinaryOp
    {
        Multiplication,
        Division,
        Modulo,
        Addition,
        Subtraction
    };

    BinaryExpr(BinaryOp op, Expression* expr1, Expression* expr2)
      : m_left(expr1)
      , m_right(expr2)
      , m_operation(op)
    { }
  
  private:
    Expression *m_left, *m_right;
    BinaryOp m_operation;
};

class CastExpr : public Expression
{
  public:
    CastExpr(Expression* expr)
      : m_expr(expr)
    { }

  private:
    Expression* m_expr;
};