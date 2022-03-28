//
// Created by yifeng on 2022/3/20.
//

#include "Lexer.h"
#include <cstring>

void C100::Lexer::getNextToken() {
    while (isspace(curChar)) {      //skip pace
        getNextChar();
    }

    TokenKind kind;
    int start_pos = cursor-1;
    int value = 0;
    if (curChar == '\0') {
        kind = TokenKind::Eof;
    } else if (curChar == '+') {
        kind = TokenKind::Add;
        getNextChar();
    } else if (curChar == '-') {
        kind = TokenKind::Sub;
        getNextChar();
    } else if (curChar == '*') {
        kind = TokenKind::Mul;
        getNextChar();
    } else if (curChar == '/') {
        kind = TokenKind::Div;
        getNextChar();
    } else if (curChar == '(') {
        kind = TokenKind::LParent;
        getNextChar();
    } else if (curChar == ')') {
        kind = TokenKind::RParent;
        getNextChar();
    } else if (isdigit(curChar)) {
        kind = TokenKind::Num;
        value = 0;
        do {
            value = value * 10 + curChar - '0';
            getNextChar();
        } while (isdigit(curChar));
    } else {
        printf("not support char %c \n", curChar);
    }

    currentToken = std::make_shared<Token>();
    currentToken->kind = kind;
    currentToken->value = value;
    currentToken->content = sourceCode.substr(start_pos, cursor-1-start_pos);
}

void C100::Lexer::getNextChar() {
    if (cursor == sourceCode.size()) {
        curChar = '\0';
        cursor++;
    } else {
        curChar = sourceCode[cursor++];
    }
}
