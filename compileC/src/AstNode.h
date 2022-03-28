//
// Created by yifeng on 2022/3/20.
//

#ifndef COMPILEC_ASTNODE_H
#define COMPILEC_ASTNODE_H

#include <memory>

namespace C100 {

    class AstVisitor;
    class AstNode {
    public:
        virtual ~AstNode() {};
        virtual void Accept(AstVisitor *visitor) {} ;
    };

    class ProgramNode : public AstNode{
    public:
        std::shared_ptr<AstNode> Lhs;
        virtual void Accept(AstVisitor *visitor) override;
    };

    enum class BinaryOperator {
        Add,
        Sub,
        Mul,
        Div,
        LParent,
        RParent
    };

    class BinaryNode : public AstNode {
    public:
        BinaryOperator binOp;
        std::shared_ptr<AstNode> Lhs;
        std::shared_ptr<AstNode> Rhs;
        virtual void Accept(AstVisitor *visitor) override;
    };

    class ConstantNode : public AstNode {
    public:
        int value;
        virtual void Accept(AstVisitor *visitor) override;
    };

    class AstVisitor {
    public:
        virtual ~AstVisitor() {};       ///base class need virtual deconstruct, default deconstruct is not virtual

        virtual void visitorProgramNode(ProgramNode *node) {};
        virtual void VisitorBinaryNode(BinaryNode *node) {};
        virtual void VisitorConstantNode(ConstantNode *node) {};
    };

}


#endif //COMPILEC_ASTNODE_H
