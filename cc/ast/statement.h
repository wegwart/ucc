#pragma once

#include <vector>
#include <memory>

#include <ast/object.h>

namespace ast {

    class Expression;

    class Statement : public AstObject
    {
      public:
        Statement() = default;
        virtual ~Statement() = default;
    };

    class EmptyStatement : public Statement
    {
      public:
        EmptyStatement() = default;

        void visit(AstVisitor* visitor) const override { };
    };

    class StatementList : public Statement
    {
      public:
        StatementList() = default;
        StatementList(size_t stmt);
        size_t add(size_t stmt);

        void visit(AstVisitor* visitor) const override;

      private:
        std::vector<std::shared_ptr<const Statement>> m_statements;
    };

    class ReturnStatement : public Statement
    {
      public:
        ReturnStatement() = default;
        ReturnStatement(size_t expression);

        bool hasValue() const { return m_expression ? true : false; }
        std::shared_ptr<const Expression> getExpression() const { return m_expression; }

        void visit(AstVisitor* visitor) const override;

      private:
        std::shared_ptr<const Expression> m_expression;
    };

}