//
// Created by yifeng on 2022/3/21.
//

#include "PrintVisitor.h"
#include <iostream>

using namespace C100;

void PrintVisitor::VisitorProgramNode(ProgramNode *node) {
    for(auto &a : node->Stmts) {
        a->Accept(this);
    }
}

void PrintVisitor::VisitorBinaryNode(BinaryNode *node) {

    node->Lhs->Accept(this);
    switch (node->binOp) {
        case BinaryOperator::Add:
            content += "+" ;
            break;
        case BinaryOperator::Sub:
            content += "-";
            break;
        case BinaryOperator::Mul:
            content += "*";
            break;
        case BinaryOperator::Div:
            content += "/";
            break;
        case BinaryOperator::Equal:
            content += "==" ;
            break;
        case BinaryOperator::PipeEqual:
            content += "!=";
            break;
        case BinaryOperator::Greater:
            content += ">";
            break;
        case BinaryOperator::GreaterEqual:
            content += ">=";
            break;
        case BinaryOperator::Lesser:
            content += "<";
            break;
        case BinaryOperator::LesserEqual:
            content += "<=";
            break;
        default:
            printf("error operator\n");
            assert(0);
    }
    node->Rhs->Accept(this);
}

void PrintVisitor::VisitorConstantNode(ConstantNode *node) {
    content += std::to_string(node->value);
}

void PrintVisitor::VisitorStmtsNode(ExprStmtsNode *node) {
    node->Lhs->Accept(this);
    content += ";";
}

void PrintVisitor::VisitorVarExprNode(VarExprNode *node) {
    content += std::string(node->varObj->name);
}

void PrintVisitor::VisitorAssignExprNode(AssignExprNode *node) {
    node->Lhs->Accept(this);
    content += "=";
    node->Rhs->Accept(this);
}

void PrintVisitor::VisitorIfStmtsNode(ifStmtNode *node) {
    content += "if";
    content += "(";
    node->Cond->Accept(this);
    content += ")";
    node->Then->Accept(this);
    if (node->Else) {
        content += "else ";
        node->Else->Accept(this);
    }
}

void PrintVisitor::VisitorBlockStmtsNode(blockStmtNode *node) {
    content += "{";
    for (auto &s : node->Stmts) {
        s->Accept(this);
    }
    content += "}";
}
