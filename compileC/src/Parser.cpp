//
// Created by yifeng on 2022/3/20.
//

#include "Parser.h"
#include "Diag.h"
#include <iostream>

using namespace C100;

std::shared_ptr<ProgramNode> Parser::parse() {
    auto node = std::make_shared<ProgramNode>();
    locals = &node->LocalVars;                  //add obj by node->localVars
    while (lexer.currentToken->kind != TokenKind::Eof) {
        node->Stmts.push_back(parseStmt());
    }
    return node;
}

std::shared_ptr<AstNode> Parser::parseStmt() {
    if (lexer.currentToken->kind == TokenKind::If) {
        auto node = std::make_shared<ifStmtNode>();
        lexer.getNextToken();
        lexer.expectToken(TokenKind::LParent);
        node->Cond = parseExpr();
        lexer.expectToken(TokenKind::RParent);
        node->Then = parseStmt();
        if (lexer.currentToken->kind == TokenKind::Else) {
            lexer.getNextToken();
            node->Else = parseStmt();
        }
        return node;
    } else if (lexer.currentToken->kind == TokenKind::LBrace) {
        auto node = std::make_shared<blockStmtNode>();
        lexer.getNextToken();
        while (lexer.currentToken->kind != TokenKind::RBrace) {
            node->Stmts.push_back(parseStmt());
        }
        lexer.expectToken(TokenKind::RBrace);
        return node;
    }
    else {
        auto node = std::make_shared<ExprStmtsNode>();
        node->Lhs = parseExpr();
        assert(lexer.currentToken->kind == TokenKind::Semicolon);
        lexer.getNextToken();
        return node;
    }
}

std::shared_ptr<AstNode> Parser::parseExpr() {
    return parseAssignExpr();
}

std::shared_ptr<AstNode> Parser::parseAssignExpr() {
    auto left = parseEqualExpr();

    if (lexer.currentToken->kind == TokenKind::Assign) {
        lexer.getNextToken();
        auto node = std::make_shared<AssignExprNode>();
        node->Lhs = left;
        node->Rhs = parseAssignExpr();
        return node;
    }
    return left;
}

std::shared_ptr<AstNode> Parser::parseEqualExpr() {
    auto left = parseRelationExpr();
    if (lexer.currentToken->kind == TokenKind::Equal ||
        lexer.currentToken->kind == TokenKind::PipeEqual)
    {
        BinaryOperator binaryOperator = BinaryOperator::Equal;
        if (lexer.currentToken->kind == TokenKind::PipeEqual)
            binaryOperator = BinaryOperator::PipeEqual;
        lexer.getNextToken();
        auto node = std::make_shared<BinaryNode>();
        node->binOp = binaryOperator;
        node->Lhs = left;
        node->Rhs = parseRelationExpr();
        left = node;
    }
    return left;
}

std::shared_ptr<AstNode> Parser::parseRelationExpr() {
    auto left = parseAddExpr();
    if (lexer.currentToken->kind == TokenKind::Greater ||
        lexer.currentToken->kind == TokenKind::GreaterEqual ||
        lexer.currentToken->kind == TokenKind::Lesser ||
        lexer.currentToken->kind == TokenKind::LesserEqual)
    {
        BinaryOperator binaryOperator = BinaryOperator::Greater;
        if (lexer.currentToken->kind == TokenKind::GreaterEqual)
            binaryOperator = BinaryOperator::GreaterEqual;
        else if (lexer.currentToken->kind == TokenKind::Lesser)
            binaryOperator = BinaryOperator::Lesser;
        else if (lexer.currentToken->kind == TokenKind::LesserEqual)
            binaryOperator = BinaryOperator::LesserEqual;
        lexer.getNextToken();
        auto node = std::make_shared<BinaryNode>();
        node->binOp = binaryOperator;
        node->Lhs = left;
        node->Rhs = parseAddExpr();
        left = node;
    }
    return left;
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
        lexer.expectToken(TokenKind::RParent);
        return node;
    } else if (lexer.currentToken->kind == TokenKind::Num) {
        auto node = std::make_shared<ConstantNode>();
        node->value = lexer.currentToken->value;
        lexer.getNextToken();
        return node;
    } else if (lexer.currentToken->kind == TokenKind::Identifier) {
        auto node = std::make_shared<VarExprNode>();

        auto obj = findLocalVar(lexer.currentToken->content);
        if (!obj) {
            obj = makeLocalVar(lexer.currentToken->content);
        }
        node->varObj = obj;
        lexer.getNextToken();
        return node;
    } else {
        DiagError(lexer.sourceCode, lexer.currentToken->location, " not support node! ");
    }
    return nullptr;
}

std::shared_ptr<Var> Parser::makeLocalVar(std::string_view name) {
    auto obj = std::make_shared<Var>();
    obj->name = name;
    obj->offset = 0;
    locals->push_front(obj);
    localsMap[name] = obj;
    return obj;
}

std::shared_ptr<Var> Parser::findLocalVar(std::string_view name) {
    if (localsMap.find(name) != localsMap.end()) {
        return localsMap[name];
    }
    return nullptr;
}