//
// Created by yifeng on 2022/3/20.
//

#ifndef COMPILEC_PARSER_H
#define COMPILEC_PARSER_H

#include "Lexer.h"
#include "AstNode.h"

namespace C100
{
    class Parser {
    private:
        Lexer& lexer;
    public:
        Parser(Lexer& lex):lexer(lex){};
        std::shared_ptr<ProgramNode> parse();

    private:
        std::shared_ptr<AstNode> parseExpr();
        std::shared_ptr<AstNode> parseAddExpr();
        std::shared_ptr<AstNode> parseMultiExpr();
        std::shared_ptr<AstNode> parseParentExpr();
        std::shared_ptr<AstNode> parsePrimaryExpr();
    };
}


#endif //COMPILEC_PARSER_H
