#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "PrintVisitor.h"
#include "CodeGen.h"

using namespace C100;

const char *code = "  5  + 1 - 3*4 /  2";
void testLexer() {
    Lexer lexer(code);

    do {
        lexer.getNextToken();
        std::cout << lexer.currentToken->content << std::endl;
    } while (lexer.currentToken->kind != TokenKind::Eof);

}

void testParser() {
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);
}

int main(int argc, char *argv[]) {

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

    return 0;
}
