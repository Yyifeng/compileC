#include "catch.hh"
#include "../src/Lexer.h"
#include "../src/Parser.h"
#include "../src/PrintVisitor.h"

using namespace C100;
TEST_CASE("compileC_testLexer", "5  + (1 - 3)*4 /  2") {
    const char *code = "5  + (1 - 3)*4 /  2" ;
    Lexer lexer(code);
    lexer.getNextToken();
    REQUIRE("5" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("+" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("(" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("1" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("-" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(")" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("*" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("4" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("/" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("2" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(TokenKind::Eof == lexer.currentToken->kind);
}

TEST_CASE("compileC_testParse", "5  + (1 - 3)*4 /  2") {
    const char *code = "5  + (1 - 3)*4 /  2" ;
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);

    REQUIRE("2431-*/5+" == printVisitor.content);
}