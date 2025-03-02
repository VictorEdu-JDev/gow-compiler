
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast.h"
#include "interpreter.h"

#define MAX_NAME_LENGTH 255
#define MAX_PARAMS 5

typedef void* (*FunctionPointer)(void* params);

typedef enum {
    VAR_SCALAR,
    VAR_STRING,
    VAR_BOOLEAN
} VarType;

typedef struct {
    char name[MAX_NAME_LENGTH];
    VarType type;
    union {
        int booleanValue;
        double scalarValue;
        char stringValue[MAX_NAME_LENGTH];
    } value;
} Variable;

typedef struct {
    char name[MAX_NAME_LENGTH];
    int param_count;
    ASTNode *parameters;
    ASTNode *body;
    void (*funcPointer)();
} Function;

typedef struct {
    Variable variables[MAX_VARIABLES];
    Function functions[MAX_FUNCTIONS];
    int var_count;
    int func_count;
} SymbolTable;

void initSymbolTable(SymbolTable *table);
int addVariable(SymbolTable *table, const char *name, VarType type, const char *value);
int addFunction(SymbolTable *table, ASTNode *node);
Variable* getVariable(SymbolTable *table, const char *name);
Function* getFunction(SymbolTable *table, const char *name);
void setVariable(SymbolTable *table, const char *name, void *value);
void printVariable(Variable *var);
void printFunction(Function *func);
void printSymbolTable(SymbolTable *table);
void freeSymbolTable(SymbolTable *table);

#endif //SYMBOL_TABLE_H
