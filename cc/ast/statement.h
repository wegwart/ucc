#pragma once

#include <vector>
#include <memory>

#include <ast/object.h>

namespace ast {

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
    };

    class StatementList : public Statement
    {
      public:
        StatementList() = default;
        StatementList(size_t stmt);
        size_t add(size_t stmt);

      private:
        std::vector<std::shared_ptr<const Statement>> m_statements;
    };

}