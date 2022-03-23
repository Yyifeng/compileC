//
// Created by yifeng on 2022/3/20.
//

#include "CodeGen.h"

using namespace C100;

void CodeGen::visitorProgramNode(ProgramNode *node) {
    printf("\t.text\n");
#ifdef __linux__
    printf("\t.global prog\n");
    printf("prog:\n");
#else
    ///macos
    printf("\t.global _prog\n");
    printf("_prog:\n");
#endif

    printf("\tpush %%rbp\n");
    printf("\tmov %%rsp, %%rbp\n");
    printf("\tsub $32, %%rsp\n");

    node->Lhs->Accept(this);
    assert(stackLevel == 0);

    printf("\tmov %%rbp, %%rsp\n");
    printf("\ttop %%rbp\n");
    printf("\tret\n");

}

void CodeGen::VisitorBinaryNode(BinaryNode *node) {
    node->Rhs->Accept(this);
    Push();
    node->Lhs->Accept(this);
    Pop("%rdi");

    switch (node->binOp) {
        case BinaryOperator::Add:
            printf("\tadd %%rdi, %%rax\n");
            break;
        case BinaryOperator::Sub:
            printf("\tsub %%rdi, %%rax\n");
            break;
        case BinaryOperator::Mul:
            printf("\timul %%rdi, %%rax\n");
            break;
        case BinaryOperator::Div:
            printf("\tcqo \n");
            printf("\tidiv %%rdi, %%rax\n");
            break;
        default:
            assert(0);
            break;
    }
}

void CodeGen::VisitorConstantNode(ConstantNode *node) {
    printf("\tmov $%d, %%rax\n", node->value);
}

void CodeGen::Push() {
    printf("\tpush %%rax\n");
    stackLevel++;
}

void CodeGen::Pop(const char *reg) {
    printf("\tpop %s\n", reg);
    stackLevel--;
}
