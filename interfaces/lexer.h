
#ifndef LEXER_H
#define LEXER_H

typedef struct operator Operator;

typedef enum keyword Keyword;
typedef enum operator_type OperatorType;

typedef enum token_type {
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_CALL,
    TOKEN_FOR,
    TOKEN_BREAK,
    TOKEN_ASSIGN,
    TOKEN_ASSIGN_SIGNAL,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_ELSEIF,

    TOKEN_IDENTIFIER,
    TOKEN_PARAM,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_BOOLEAN,
    TOKEN_OPERATOR
} TokenType;

typedef struct token {
    TokenType type;
    char value[255];
} Token;

void initLexer(const char *source);
Token getNextToken();

#endif //LEXER_H
