#include "lexer.h"
#include <sstream>
#include <stdexcept>

using namespace eval;

std::vector<Lexeme> eval::lex(const std::string &expr)
{
    std::vector<Lexeme> res;
    std::istringstream ss(expr);
    while(ss.good()){
        auto c = ss.peek();
        switch(c){
            case '+':
                ss.get();
                res.emplace_back(LexemeType::Plus);
                break;
            case '*':
                ss.get();
                res.emplace_back(LexemeType::Times);
                break;
            case 'D':
            case 'd':
                ss.get();
                res.emplace_back(LexemeType::D);
                break;
            case '(':
                ss.get();
                res.emplace_back(LexemeType::OpenParen);
                break;
            case ')':
                ss.get();
                res.emplace_back(LexemeType::CloseParen);
                break;
            case ' ':
                ss.get();
                break;
            default:
            if(c >= '0' && c <= '9'){
                unsigned val;
                ss >> val;
                res.emplace_back(LexemeType::Int, val);
            } else {
                throw std::runtime_error(std::string("Illegal character '") + static_cast<char>(c) + "'");
            }
        }
    }
    return res;
}
