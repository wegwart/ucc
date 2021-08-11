#pragma once

#include <vector>

namespace ast {

    class Statement
    {
      public:
        Statement() = default;
        virtual ~Statement() = default;
    };

    class EmptyStatement : public Statement
    {
      public:
        EmptyStatement() = default;
    };

    class StatementList : public Statement
    {
      public:
        StatementList() = default;
        StatementList(Statement* stmt);
        StatementList* add(Statement* stmt);

      private:
        std::vector<Statement*> m_statements;
    };

}