//
// Created by yifeng on 2022/3/21.
//

#include "PrintVisitor.h"

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
