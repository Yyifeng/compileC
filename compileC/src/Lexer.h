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
        LBrace,
        RBrace,
        Identifier,
        Semicolon,
        Assign,
        Equal,
        PipeEqual,
        Greater,
        GreaterEqual,
        Lesser,
        LesserEqual,
        If,
        Else,
        Eof
    };

    struct sourceLocation {
        int row;
        int col;
    };

    class Token
    {
    public:
        TokenKind kind;
        int value;
        std::string_view content;
        sourceLocation location;
    };
    class Lexer {
    private:
        char curChar{' '};
        int cursor{0};
        int row{0};
        int rowHead{0};
    public:
        Lexer(const char *code){
            sourceCode = code;
        };
        void getNextToken();
        void getNextChar();
        void expectToken(TokenKind kind);
        const char *getTokenSimpleSpelling(TokenKind kind);

        std::shared_ptr<Token> currentToken;
        std::string_view sourceCode;
    private:
        bool isLetter() const;
        bool isDigit() const;
        bool isLetterOrDigit();
        char peekChar(int distance);
    };

}



#endif //COMPILEC_LEXER_H
