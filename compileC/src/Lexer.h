//
// Created by yifeng on 2022/3/20.
//

#ifndef COMPILEC_LEXER_H
#define COMPILEC_LEXER_H

#include <string_view>

namespace C100
{
    enum class TokenKind
    {
        Add,
        Sub,
        Mul,
        Div,
        Num,
        LParent,
        RParent,
        Eof
    };
    class Token
    {
    public:
        TokenKind kind;
        int value;
        std::string_view content;
    };
    class Lexer {
    private:
        std::string_view sourceCode;
        char curChar{' '};
        int cursor{0};
    public:
        Lexer(const char *code){
            sourceCode = code;
        };
        void getNextToken();
        void getNextChar();

        std::shared_ptr<Token> currentToken;
    };

}



#endif //COMPILEC_LEXER_H
