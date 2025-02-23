
#ifndef LEXER_H
#define LEXER_H

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

typedef enum operator_type {
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
} OperatorType;

typedef struct operator {
    OperatorType type;
    const char *name;
} Operator;

typedef enum keyword {
    KEYWORD_FUNCTION,
    KEYWORD_RETURN,
    KEYWORD_CALL,
    KEYWORD_FOR,
    KEYWORD_BREAK,
    KEYWORD_ASSIGN,
    KEYWORD_OF,
    KEYWORD_IF,
    KEYWORD_ELSE,
    KEYWORD_ELSEIF,
    KEYWORD_TRUE,
    KEYWORD_FALSE,
    KEYWORD_WHILE,
    KEYWORD_DO_WHILE,
    KEYWORD_SWITCH,
    KEYWORD_CASE,
    KEYWORD_COUNT
} Keyword;

const char* getOperator(OperatorType type);
const char *getKeywordStr(Keyword key);
void initLexer(const char *source);
Token getNextToken();

#endif //LEXER_H
