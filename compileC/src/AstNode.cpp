//
// Created by yifeng on 2022/3/20.
//

#include "AstNode.h"

using namespace C100;

void BinaryNode::Accept(AstVisitor *visitor) {
    visitor->VisitorBinaryNode(this);
}

void ConstantNode::Accept(C100::AstVisitor *visitor) {
    visitor->VisitorConstantNode(this);
}

void ProgramNode::Accept(AstVisitor *visitor) {
    visitor->visitorProgramNode(this);
}



