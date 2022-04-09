//
// Created by yifeng on 2022/3/20.
//

#include "Parser.h"
#include "Diag.h"

using namespace C100;

std::shared_ptr<ProgramNode> Parser::parse() {
    auto node = std::make_shared<ProgramNode>();
    locals = &node->LocalVars;                  //add obj by node->localVars
    while (lexer.currentToken->kind != TokenKind::Eof) {
        node->Stmts.push_back(parseStmt());
    }

    return node;
}

std::shared_ptr<AstNode> Parser::parseExpr() {
    return parseAssignExpr();
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
        DiagError(lexer.sourceCode, lexer.currentToken->location.row, lexer.currentToken->location.col, " not support node! ");
    }
    return nullptr;
}

std::shared_ptr<AstNode> Parser::parseStmt() {
    auto node = std::make_shared<ExprStmtsNode>();
    node->Lhs = parseExpr();
    assert(lexer.currentToken->kind == TokenKind::Semicolon);
    lexer.getNextToken();
    return node;
}

std::shared_ptr<AstNode> Parser::parseAssignExpr() {
    auto left = parseAddExpr();

    if (lexer.currentToken->kind == TokenKind::Assign) {
        lexer.getNextToken();
        auto node = std::make_shared<AssignExprNode>();
        node->Lhs = left;
        node->Rhs = parseAssignExpr();
        return node;
    }
    return left;
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
