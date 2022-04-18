//
// Created by yifeng on 2022/3/20.
//

#ifndef COMPILEC_PARSER_H
#define COMPILEC_PARSER_H

#include "Lexer.h"
#include "AstNode.h"
#include <unordered_map>

namespace C100
{
    class Parser {
    private:
        Lexer& lexer;
        std::list<std::shared_ptr<Var> > *locals{nullptr};
        std::unordered_map<std::string_view, std::shared_ptr<Var> > localsMap;
    public:
        Parser(Lexer& lex):lexer(lex){};
        std::shared_ptr<ProgramNode> parse();

    private:
        std::shared_ptr<AstNode> parseStmt();
        std::shared_ptr<AstNode> parseExpr();
        std::shared_ptr<AstNode> parseAssignExpr();
        std::shared_ptr<AstNode> parseEqualExpr();
        std::shared_ptr<AstNode> parseRelationExpr();
        std::shared_ptr<AstNode> parseAddExpr();
        std::shared_ptr<AstNode> parseMultiExpr();
        std::shared_ptr<AstNode> parsePrimaryExpr();

        std::shared_ptr<Var> findLocalVar(std::string_view name);
        std::shared_ptr<Var> makeLocalVar(std::string_view name);
    };
}


#endif //COMPILEC_PARSER_H
