#pragma once

#include <map>
#include <vector>
#include <memory>
#include <cassert>

namespace ast {

    class AstObject;
    class AstVisitor;

    class Ast
    {
      public:
        Ast() = default;

        size_t add(std::shared_ptr<AstObject> obj, bool topLevelVisitable = false);
        std::shared_ptr<AstObject> find(size_t id);

        template<typename T>
        std::shared_ptr<T> resolve(size_t id)
        {
          auto object = std::dynamic_pointer_cast<T>(find(id));
          assert(object);
          return object;
        }

        void visit(AstVisitor* visitor);

        static Ast& get();

      private:
        static Ast s_instance;
        std::vector<std::shared_ptr<AstObject>> m_topLevelObjects;
        std::map<size_t, std::shared_ptr<AstObject>> m_objects;
    };

    class AstObject
    {
      public:
        AstObject();
        virtual ~AstObject() = default;
        virtual void visit(AstVisitor* visitor) const = 0;

        size_t getId() const { return m_id; }

      private:
        size_t m_id;
        static size_t s_idCounter;
    };

}