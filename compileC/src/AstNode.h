//
// Created by yifeng on 2022/3/20.
//

#ifndef COMPILEC_ASTNODE_H
#define COMPILEC_ASTNODE_H

#include <memory>
#include <list>
#include <string_view>

namespace C100 {

    class AstVisitor;
    class AstNode {
    public:
        virtual ~AstNode() {};
        virtual void Accept(AstVisitor *visitor) {} ;
    };

    class Var {
    public:
        std::string_view name;
        int offset;
    };

    class ProgramNode : public AstNode{
    public:
        std::list<std::shared_ptr<AstNode> > Stmts;
        std::list<std::shared_ptr<Var> > LocalVars;
        virtual void Accept(AstVisitor *visitor) override;
    };

    class ExprStmtsNode : public AstNode {
    public:
        std::shared_ptr<AstNode> Lhs;
        virtual void Accept(AstVisitor *visitor) override;
    };

    class ifStmtNode : public AstNode {
    public:
        std::shared_ptr<AstNode> Cond{nullptr};
        std::shared_ptr<AstNode> Then{nullptr};
        std::shared_ptr<AstNode> Else{nullptr};

        virtual void Accept(AstVisitor *visitor) override;
    };

    class blockStmtNode : public AstNode {
    public:
        std::list<std::shared_ptr<AstNode> > Stmts;
        virtual void Accept(AstVisitor *visitor) override;
    };

    enum class BinaryOperator {
        Add,
        Sub,
        Mul,
        Div,
        Equal,
        PipeEqual,
        Greater,
        GreaterEqual,
        Lesser,
        LesserEqual,
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

    class VarExprNode : public AstNode {
    public:
        std::shared_ptr<Var> varObj;
        virtual void Accept(AstVisitor *visitor) override;
    };

    class AssignExprNode : public AstNode {
    public:
        std::shared_ptr<AstNode> Lhs;
        std::shared_ptr<AstNode> Rhs;
        virtual void Accept(AstVisitor *visitor) override;
    };

    class AstVisitor {
    public:
        virtual ~AstVisitor() {};       ///base class need virtual deconstruct, default deconstruct is not virtual

        virtual void VisitorProgramNode(ProgramNode *node) {};
        virtual void VisitorVarExprNode(VarExprNode *node) {};
        virtual void VisitorAssignExprNode(AssignExprNode *node) {};
        virtual void VisitorStmtsNode(ExprStmtsNode *node) {};
        virtual void VisitorIfStmtsNode(ifStmtNode *node) {};
        virtual void VisitorBlockStmtsNode(blockStmtNode *node) {};
        virtual void VisitorBinaryNode(BinaryNode *node) {};
        virtual void VisitorConstantNode(ConstantNode *node) {};
    };

}


#endif //COMPILEC_ASTNODE_H
