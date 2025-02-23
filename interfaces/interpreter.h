
#ifndef INTERPRETER_H
#define INTERPRETER_H
#include "lexer.h"

#define MAX_VARIABLES 1000
#define MAX_FUNCTIONS 1000

#define MAX_IDENTIFIER_LENGTH 100
#define MAX_TOKENS 100


typedef struct variable Variable;
typedef struct function Function;
typedef struct environment Environment;

void callFunction(const char *name);
void executeFunction(Function *function);
void addVariable(const char *name, void *value, TokenType type);

#endif //INTERPRETER_H
