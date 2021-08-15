#pragma once

#include <ast/expression.h>

namespace ast {

    class AstVisitor;

    class VarReference : public Expression
    {
      public:
        VarReference(const std::string& value);

        const std::string& getIdentifier() const;

        void visit(AstVisitor* visitor) const override;
    
      private:
        std::string m_value;
    };

}