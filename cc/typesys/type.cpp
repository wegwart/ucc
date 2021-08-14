#include <typesys/type.h>

using namespace typesys;

IntegerType::IntegerType(size_t byteSize, bool isSigned)
    : m_byteSize(byteSize)
    , m_isSigned(isSigned)
{ }

AliasType::AliasType(ast::Typename ref)
    : m_reference(ref)
{ }