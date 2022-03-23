//
// Created by yifeng on 2022/3/21.
//

#include "PrintVisitor.h"

using namespace C100;

void PrintVisitor::visitorProgramNode(ProgramNode *node) {
    printf("Program: ");
    node->Lhs->Accept(this);
    printf("\n");
}

void PrintVisitor::VisitorBinaryNode(BinaryNode *node) {
    node->Rhs->Accept(this);
    node->Lhs->Accept(this);
    switch (node->binOp) {
        case BinaryOperator::Add:
            printf(" + ");
            break;
        case BinaryOperator::Sub:
            printf(" - ");
            break;
        case BinaryOperator::Mul:
            printf(" * ");
            break;
        case BinaryOperator::Div:
            printf(" / ");
            break;
        default:
            printf("error operator\n");
            assert(0);
    }
}

void PrintVisitor::VisitorConstantNode(ConstantNode *node) {
    printf(" %d ", node->value);
}
