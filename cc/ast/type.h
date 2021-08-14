#pragma once

#include <string>
#include <ast/object.h>

namespace ast {

    class Typename : public AstObject
    {
      public:
        Typename();
        Typename(const std::string& basetype);

        void visit(AstVisitor* visitor) const override { }

        const std::string& toString() const { return m_typename; }

        bool operator() (const Typename& lhs, const Typename& rhs) const;

      private:
        std::string m_typename;
    };

}