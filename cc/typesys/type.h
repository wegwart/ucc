#pragma once

#include <cstddef>
#include <ast/type.h>

namespace typesys {

    class Type
    {
      public:
        Type() = default;

        virtual bool isAlias() const { return false; }
        virtual bool isInteger() const { return false; }
        virtual size_t getBitSize() const = 0;
    };

    class IntegerType : public Type
    {
      public:
        IntegerType(size_t byteSize, bool isSigned = false);

        bool isInteger() const final { return true; }
        size_t getBitSize() const { return m_byteSize * 8; }

      private:
        size_t m_byteSize;
        bool m_isSigned;
    };

    class AliasType : public Type
    {
      public:
        AliasType(ast::Typename ref);

        bool isAlias() const final { return true; }
        size_t getBitSize() const { assert(false); return 0; }
      
      private:
        ast::Typename m_reference;
    };

}