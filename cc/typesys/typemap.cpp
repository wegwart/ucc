#include <typesys/typemap.h>
#include <typesys/type.h>

using namespace typesys;

TypeMap::TypeMap()
{
    insertType(ast::Typename("char"), std::make_shared<IntegerType>(1));
    insertType(ast::Typename("short"), std::make_shared<IntegerType>(2));
    insertType(ast::Typename("int"), std::make_shared<IntegerType>(4));
    insertType(ast::Typename("long"), std::make_shared<IntegerType>(8));
}

std::shared_ptr<const Type> TypeMap::findType(const ast::Typename& type)
{
    auto searchName = type.toString();
    for (;;) {
        auto it = m_knownTypes.find(searchName);;
        if (it == m_knownTypes.end())
            return nullptr;
        if (it->second->isAlias())
            continue;
        return it->second;
    }
}

void TypeMap::insertType(const ast::Typename& name, std::shared_ptr<const Type> type)
{
    assert(m_knownTypes.find(name.toString()) == m_knownTypes.end());
    m_knownTypes[name.toString()] = type;
}