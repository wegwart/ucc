#pragma once

#include <cstdint>
#include <ast/expression.h>

namespace ast {

    class AstVisitor;

    class IntLiteral : public Expression
    {
      public:
        IntLiteral(uint64_t value);

        uint64_t getValue() const;

        void visit(AstVisitor* visitor) const override;
    
      private:
        uint64_t m_value;
    };

}