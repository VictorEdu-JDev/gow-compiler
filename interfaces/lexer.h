
#ifndef LEXER_H
#define LEXER_H

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

enum operator_type {
    LO_EQUAL,
    LO_NOTEQUAL,
    LO_GREATER,
    LO_GREATEREQUAL,
    LO_LESS,
    LO_LESSEQUAL,
    LO_AND,
    LO_OR,
    LO_XOR,
    AO_ADD,
    AO_MINUS,
    AO_TIMES,
    AO_DIVIDE,
    AO_MODULUS,
    AO_PLUS_PLUS,
    AO_MINUS_MINUS,
    OPERATOR_COUNT
};

typedef struct operator {
    OperatorType type;
    const char *name;
} Operator;

const char* getOperator(OperatorType type);
const char *getKeywordStr(Keyword key);
void initLexer(const char *source);
Token getNextToken();

#endif //LEXER_H
