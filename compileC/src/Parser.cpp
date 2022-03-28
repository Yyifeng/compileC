//
// Created by yifeng on 2022/3/20.
//

#include "Parser.h"

using namespace C100;

std::shared_ptr<ProgramNode> Parser::parse() {
    auto node = std::make_shared<ProgramNode>();
    node->Lhs = parseExpr();
    return node;
}

std::shared_ptr<AstNode> Parser::parseExpr() {
    return parseAddExpr();
}

std::shared_ptr<AstNode> Parser::parseAddExpr() {
    std::shared_ptr<AstNode> left = parseMultiExpr();       ///first judge Mul and Div, then judge Add and Sub
    while (lexer.currentToken->kind == TokenKind::Add
           || lexer.currentToken->kind == TokenKind::Sub) {
        BinaryOperator binaryOperator = BinaryOperator::Add;
        if (lexer.currentToken->kind == TokenKind::Sub)
            binaryOperator = BinaryOperator::Sub;
        lexer.getNextToken();
        auto node = std::make_shared<BinaryNode>();
        node->binOp = binaryOperator;
        node->Lhs = left;
        node->Rhs = parseMultiExpr();
        left = node;
    }
    return left;
}

std::shared_ptr<AstNode> Parser::parseMultiExpr() {
    std::shared_ptr<AstNode> left = parsePrimaryExpr();
    while (lexer.currentToken->kind == TokenKind::Mul
            || lexer.currentToken->kind == TokenKind::Div) {
        BinaryOperator binaryOperator = BinaryOperator::Mul;
        if (lexer.currentToken->kind == TokenKind::Div)
            binaryOperator = BinaryOperator::Div;
        lexer.getNextToken();
        auto node = std::make_shared<BinaryNode>();
        node->binOp = binaryOperator;
        node->Lhs = left;
        node->Rhs = parsePrimaryExpr();
        left = node;
    }
    return left;
}

std::shared_ptr<AstNode> Parser::parsePrimaryExpr() {
    if (lexer.currentToken->kind == TokenKind::LParent) {
        lexer.getNextToken();
        auto node = parseExpr();
        lexer.getNextToken();
        return node;
    } else {
        auto node = std::make_shared<ConstantNode>();
        node->value = lexer.currentToken->value;
        lexer.getNextToken();
        return node;
    }
}
