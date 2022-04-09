//
// Created by yifeng on 2022/3/20.
//

#ifndef COMPILEC_CODEGEN_H
#define COMPILEC_CODEGEN_H

#include "AstNode.h"

namespace C100 {
    class CodeGen : public AstVisitor
    {
    private:
        int stackLevel{0};

    public:
        CodeGen() {};
        void VisitorProgramNode(ProgramNode *node) override;

    private:
        void VisitorBinaryNode(BinaryNode *node) override;
        void VisitorConstantNode(ConstantNode *node) override ;

        void Push();
        void Pop(const char *reg );
    };

}


#endif //COMPILEC_CODEGEN_H
