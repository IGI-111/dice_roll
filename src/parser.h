#ifndef PARSER_H_SAFT145U
#define PARSER_H_SAFT145U

#include <vector>
#include "lexer.h"

namespace eval {
    unsigned parse(const std::vector<Lexeme> &lexemes);
}

#endif /* end of include guard: PARSER_H_SAFT145U */