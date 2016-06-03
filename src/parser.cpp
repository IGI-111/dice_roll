#include "parser.h"
#include "lexer.h"
#include <random>
#include <stdexcept>
#include <map>

/*
 * S ::= P S'
 *
 * S' ::= + P S'
 * | epsilon
 *
 * P ::= T S'
 *
 * P' ::= * T S'
 * | epsilon
 *
 * T ::= Int
 * | ( S )
 * | Int d Int
 */

namespace {
    typedef std::vector<eval::Lexeme>::const_iterator LexemeIterator;

    unsigned parse_int(LexemeIterator &it, const LexemeIterator &end)
    {
        return (it++)->value;
    }

    unsigned parse_dice(LexemeIterator &it, const LexemeIterator &end)
    {
        static std::random_device rd;
        static std::mt19937 mt(rd());

        unsigned dice_count = parse_int(it, end);
        ++it;
        unsigned side_count = parse_int(it, end);
        std::uniform_int_distribution<unsigned> dist(1, side_count);
        unsigned ret = 0;
        for (unsigned i = 0; i < dice_count; ++i) {
            ret += dist(mt);
        }
        return ret;
    }

    unsigned parse_plus(LexemeIterator &it, const LexemeIterator &end);

    unsigned parse_paren(LexemeIterator &it, const LexemeIterator &end)
    {
            ++it;
            auto ret = parse_plus(it, end);
            if((++it)->type != eval::LexemeType::CloseParen){
                throw std::runtime_error("Brace not closed");
            }
            return ret;
    }

    unsigned parse_terminal(LexemeIterator &it, const LexemeIterator &end)
    {
        if(it != end && it->type == eval::LexemeType::Int
                && it+1 != end && (it+1)->type == eval::LexemeType::D
                && it+2 != end && (it+2)->type == eval::LexemeType::Int){
            return parse_dice(it, end);
        }

        if(it != end && it->type == eval::LexemeType::Int){
            return parse_int(it, end);
        }
        if(it != end && it->type == eval::LexemeType::OpenParen){
            return parse_paren(it,end);
        }

        throw std::runtime_error("Lexeme is not a terminal");
    }

    unsigned parse_product_p(LexemeIterator &it, const LexemeIterator &end)
    {
        if(it != end && it->type == eval::LexemeType::Times){
            ++it;
            unsigned before = parse_terminal(it, end);
            unsigned after = parse_product_p(it, end);
            return before * after;
        }
        return 1;
    }

    unsigned parse_product(LexemeIterator &it, const LexemeIterator &end)
    {
        unsigned before = parse_terminal(it, end);
        unsigned after = parse_product_p(it, end);
        return before * after;
    }

    unsigned parse_plus_p(LexemeIterator &it, const LexemeIterator &end)
    {
        if(it != end && it->type == eval::LexemeType::Plus){
            ++it;
            unsigned before = parse_product(it, end);
            unsigned after = parse_plus_p(it, end);
            return before + after;
        }
        return 0;
    }

    unsigned parse_plus(LexemeIterator &it, const LexemeIterator &end)
    {
        unsigned before = parse_product(it, end);
        unsigned after = parse_plus_p(it, end);
        return before + after;
    }
}

unsigned eval::parse(const std::vector<eval::Lexeme> &lexemes)
{
    auto it = lexemes.cbegin();
    const auto end = lexemes.cend();
    return parse_plus(it, end);
}
