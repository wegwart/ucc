#include <ast/type.h>

using namespace ast;

Typename::Typename()
    : m_typename("void")
{ }

Typename::Typename(const std::string& basetype)
    : m_typename(basetype)
{ }