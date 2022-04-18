#include "catch.hh"
#include "../src/Lexer.h"
#include "../src/Parser.h"
#include "../src/PrintVisitor.h"

using namespace C100;
TEST_CASE("compileC_testLexer1", "lexer1") {
    const char *code = "5  +ab_c233de + (1 - 3)*4 /  2;" ;
    Lexer lexer(code);
    lexer.getNextToken();
    REQUIRE("5" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("+" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("ab_c233de" == lexer.currentToken->content);
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
    REQUIRE(";" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(TokenKind::Eof == lexer.currentToken->kind);
}

TEST_CASE("compileC_testLexer2", "lexer2") {
    const char *code = "a==3;a!=3;a>3;a>=3;a<3;a<=3;" ;
    Lexer lexer(code);
    lexer.getNextToken();
    REQUIRE("a" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("==" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(";" == lexer.currentToken->content);

    lexer.getNextToken();
    REQUIRE("a" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("!=" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(";" == lexer.currentToken->content);

    lexer.getNextToken();
    REQUIRE("a" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(">" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(";" == lexer.currentToken->content);

    lexer.getNextToken();
    REQUIRE("a" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(">=" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(";" == lexer.currentToken->content);

    lexer.getNextToken();
    REQUIRE("a" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("<" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(";" == lexer.currentToken->content);

    lexer.getNextToken();
    REQUIRE("a" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("<=" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE("3" == lexer.currentToken->content);
    lexer.getNextToken();
    REQUIRE(";" == lexer.currentToken->content);

    lexer.getNextToken();
    REQUIRE(TokenKind::Eof == lexer.currentToken->kind);
}

TEST_CASE("compileC_testLexer3", "lexer3") {
    const char *code = "a=3;if (a!=3) a=3; else a=a*a;" ;
    Lexer lexer(code);

    std::vector<std::string> res = {
            "a","=","3",";","if","(","a","!=","3",")", "a","=","3",";", "else", "a","=","a","*","a",";","\0"
    };

    int i = 0;
    do {
        lexer.getNextToken();
        REQUIRE(res[i++] == lexer.currentToken->content);
    } while (lexer.currentToken->kind != TokenKind::Eof);
}

TEST_CASE("compileC_testLexer4", "lexer4") {
    const char *code = "a=3;if (a!=3) { a=3 }; else { a=a*a"
                       "};" ;
    Lexer lexer(code);

    std::vector<std::string> res = {
            "a","=","3",";","if","(","a","!=","3",")","{", "a","=","3","}",";", "else","{", "a","=","a","*","a","}",";","\0"
    };

    int i = 0;
    do {
        lexer.getNextToken();
        REQUIRE(res[i++] == lexer.currentToken->content);
    } while (lexer.currentToken->kind != TokenKind::Eof);
}

TEST_CASE("compileC_testParse1", "parser1") {
    const char *code = "5  + (1 - 3)*4 /  2;abc12+2;" ;
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);

    REQUIRE("5+1-3*4/2;abc12+2;" == printVisitor.content);
}

TEST_CASE("compileC_testParse2", "parser2") {
    const char *code = " a = 3; a; a+5+ (1 - 3)*4 /  2;bc;" ;
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);

    REQUIRE("a=3;a;a+5+1-3*4/2;bc;" == printVisitor.content);
}

TEST_CASE("compileC_testParse3", "parser3") {
    const char *code = " a==3;" ;
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);

    REQUIRE("a==3;" == printVisitor.content);
}

TEST_CASE("compileC_testParse4", "parser4") {
    const char *code = "a=3;if (a!=3) a=3; else a=a*a;" ;
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);

    REQUIRE("a=3;if(a!=3)a=3;else a=a*a;" == printVisitor.content);
}

TEST_CASE("compileC_testParse5", "parser5") {
    const char *code = "a=3;if (a!=3) { a=3; } else {a=a*a; "
                       "a = a;}" ;
    Lexer lex(code);
    lex.getNextToken();

    Parser parser(lex);
    PrintVisitor printVisitor;

    auto root = parser.parse();
    root->Accept(&printVisitor);

    REQUIRE("a=3;if(a!=3){a=3;}else {a=a*a;a=a;}" == printVisitor.content);
}