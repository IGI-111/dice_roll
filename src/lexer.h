#ifndef LEXER_H_SWFT145U
#define LEXER_H_SWFT145U

#include <vector>
#include <string>

namespace eval {
    enum LexemeType {
        Plus,
        Times,
        Int,
        D,
        OpenParen,
        CloseParen
    };

    struct Lexeme {
        Lexeme(LexemeType type) :
            type(type), value(0) {}
        Lexeme(LexemeType type, unsigned value) :
            type(type), value(value) {}

        LexemeType type;
        unsigned value;
    };

    std::vector<Lexeme> lex(const std::string &expr);
}

#endif /* end of include guard: LEXER_H_SWFT145U */
