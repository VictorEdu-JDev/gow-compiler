
#ifndef LEXER_H
#define LEXER_H

typedef enum keyword Keyword;
typedef enum logical_operator LogicalOperator;
typedef enum arithmetic_operator ArithmeticOperator;
typedef enum token_type TokenType;
typedef struct token Token;

void initLexer(const char *source);
Token getNextToken();

#endif //LEXER_H
