#pragma once

#include <ast/type.h>

namespace typesys {

    class Type;

    class TypeMap
    {
      public:
        TypeMap();

        std::shared_ptr<const Type> findType(const ast::Typename& type);
        void insertType(const ast::Typename& name, std::shared_ptr<const Type> type);

      private:
        std::map<std::string, std::shared_ptr<const Type>> m_knownTypes;
    };

}