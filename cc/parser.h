#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include <ast/object.h>
#include <ast/type.h>
#include <ast/function.h>
#include <ast/literals.h>
#include <ast/statement.h>

#define AST_ADD(t, ...) \
    ast::Ast::get().add(std::make_shared<ast::t>(__VA_ARGS__))
#define AST_ADD_TOP(t, ...) \
    ast::Ast::get().add(std::make_shared<ast::t>(__VA_ARGS__), true)
#define AST_FIND(t, id) \
    (std::dynamic_pointer_cast<ast::t>(ast::Ast::get().find(id)))

void parse(FILE* f);