#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "PrintVisitor.h"
#include "CodeGen.h"

using namespace C100;

int main(int argc, char *argv[]) {

#if 1
    if (argc != 2) {
        printf("please input : ./C100 code\n");
        return 0;
    }

    const char *source = argv[1];

    Lexer lex(source);
    lex.getNextToken();

    Parser parser(lex);
    CodeGen codeGen;

    auto root = parser.parse();
    root->Accept(&codeGen);

#else
    const char *source = argv[1];
    Lexer lex(source);
    do {
        lex.getNextToken();
        std::cout << lex.currentToken->content << "("
        << lex.currentToken->location.row << ","
        << lex.currentToken->location.col << ")" << std::endl;
    } while (lex.currentToken->kind != TokenKind::Eof);
#endif

    return 0;
}
