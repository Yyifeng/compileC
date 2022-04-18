//
// Created by yifeng on 2022/3/21.
//

#ifndef COMPILEC_PRINTVISITOR_H
#define COMPILEC_PRINTVISITOR_H

#include "AstNode.h"
#include <string>

namespace C100 {

    class PrintVisitor : public AstVisitor{
    public:
        std::string content;
        void VisitorProgramNode(ProgramNode *node) override;

    private:
        void VisitorStmtsNode(ExprStmtsNode *node) override;
        void VisitorIfStmtsNode(ifStmtNode *node) override ;
        void VisitorBlockStmtsNode(blockStmtNode *node) override;
        void VisitorVarExprNode(VarExprNode *node) override;
        void VisitorAssignExprNode(AssignExprNode *node) override;
        void VisitorBinaryNode(BinaryNode *node) override;
        void VisitorConstantNode(ConstantNode *node) override;
    };

}

#endif //COMPILEC_PRINTVISITOR_H
