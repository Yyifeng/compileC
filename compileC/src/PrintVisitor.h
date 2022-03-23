//
// Created by yifeng on 2022/3/21.
//

#ifndef COMPILEC_PRINTVISITOR_H
#define COMPILEC_PRINTVISITOR_H

#include "AstNode.h"

namespace C100 {

    class PrintVisitor : public AstVisitor{
    public:
        void visitorProgramNode(ProgramNode *node) override;

    private:
        void VisitorBinaryNode(BinaryNode *node) override;
        void VisitorConstantNode(ConstantNode *node) override;
    };

}

#endif //COMPILEC_PRINTVISITOR_H
