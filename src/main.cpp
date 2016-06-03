#include <iostream>
#include <map>
#include "lexer.h"
#include "parser.h"

int main(int argc, char *argv[])
{
    try{
        if(argc < 1){
            throw std::runtime_error("No arguments");
        }
        for (auto i = 1; i < argc; ++i) {
            auto lexemes = eval::lex(argv[i]);
            auto value = eval::parse(lexemes);
            std::cout << value << std::endl;
        }
    } catch(std::exception &e){
        std::cerr << e.what() << std::endl;
    }
}
