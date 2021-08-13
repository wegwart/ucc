#include <ast/object.h>

using namespace ast;

Ast Ast::s_instance;
size_t AstObject::s_idCounter = 1;

AstObject::AstObject()
    : m_id(s_idCounter++)
{ }

Ast& Ast::get()
{
    return s_instance;
}

size_t Ast::add(std::shared_ptr<AstObject> obj, bool topLevelVisitable)
{
    assert(m_objects.find(obj->getId()) == m_objects.end());
    m_objects[obj->getId()] = obj;

    if (topLevelVisitable)
        m_topLevelObjects.push_back(obj);
    return obj->getId();
}

std::shared_ptr<AstObject> Ast::find(size_t id)
{
    auto it = m_objects.find(id);
    assert(it != m_objects.end());
    return it->second;
}

void Ast::visit(AstVisitor* visitor)
{
    for (auto& object : m_topLevelObjects)
        object->visit(visitor);
}