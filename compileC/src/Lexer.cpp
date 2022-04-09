//
// Created by yifeng on 2022/3/20.
//

#include "Lexer.h"
#include "Diag.h"
#include <string>

using namespace C100;

void Lexer::getNextToken() {
    while (isspace(curChar)) {      //skip pace
        if (curChar == '\n') {
            row++;
            rowHead =  cursor;
        }
        getNextChar();
    }

    TokenKind kind;
    sourceLocation location;
    location.row = row;
    location.col = cursor - rowHead - 1;
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
    } else if (curChar == ';') {
        kind = TokenKind::Semicolon;
        getNextChar();
    } else if (curChar == '=') {
        kind = TokenKind::Assign;
        getNextChar();
    } else if (isdigit(curChar)) {
        kind = TokenKind::Num;
        value = 0;
        do {
            value = value * 10 + curChar - '0';
            getNextChar();
        } while (isdigit(curChar));
    } else if (isLetter()) {
        kind = TokenKind::Identifier;
        while (isLetterOrDigit()) {
            getNextChar();
        }
    }
    else {
        DiagError(sourceCode, location.row, location.col, "current '%c' is illegal", curChar);
    }

    currentToken = std::make_shared<Token>();
    currentToken->kind = kind;
    currentToken->value = value;
    currentToken->location = location;
    currentToken->content = sourceCode.substr(start_pos, cursor-1-start_pos);
}

void Lexer::getNextChar() {
    if (cursor == sourceCode.size()) {
        curChar = '\0';
        cursor++;
    } else {
        curChar = sourceCode[cursor++];
    }
}

bool Lexer::isLetter() const {
    return (curChar >= 'a' && curChar <= 'z') || (curChar >= 'A' && curChar <= 'Z') || curChar == '_';
}

bool Lexer::isDigit() const {
    return curChar >= '0' && curChar <= '9' ;
}

bool Lexer::isLetterOrDigit() {
    return isLetter() || isDigit();
}

void Lexer::expectToken(TokenKind kind) {
    if (currentToken->kind == kind) {
        getNextToken();
    } else {
        DiagError(sourceCode, currentToken->location.row, currentToken->location.col, " '%s' is expected! ",
                  getTokenSimpleSpelling(kind));
    }
}

const char *Lexer::getTokenSimpleSpelling(TokenKind kind) {
    switch (kind) {
        case TokenKind::Add : return "+";
        case TokenKind::Sub : return "-";
        case TokenKind::Mul : return "*";
        case TokenKind::Div : return "/";
        case TokenKind::Semicolon : return ";";
        case TokenKind::Assign : return "=";
        case TokenKind::LParent  : return "(";
        case TokenKind::RParent : return ")";
        case TokenKind::Eof  : return "eof";
        default: break;
    }
    return nullptr;
}
