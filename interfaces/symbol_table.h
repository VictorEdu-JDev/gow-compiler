
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#define MAX_VARIABLES 100
#define MAX_FUNCTIONS 50
#define MAX_NAME_LENGTH 255

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
    void (*funcPointer)();
} Function;

typedef struct {
    Variable variables[MAX_VARIABLES];
    Function functions[MAX_FUNCTIONS];
    int var_count;
    int func_count;
} SymbolTable;

void initSymbolTable(SymbolTable *table);
int addVariable(SymbolTable *table, const char *name, VarType type, void *value);
int addFunction(SymbolTable *table, const char *name, void (*funcPointer)());
Variable* getVariable(SymbolTable *table, const char *name);
Function* getFunction(SymbolTable *table, const char *name);
void setVariable(SymbolTable *table, const char *name, void *value);
void printVariable(Variable *var);
void printFunction(Function *func);
void printSymbolTable(SymbolTable *table);
void freeSymbolTable(SymbolTable *table);

#endif //SYMBOL_TABLE_H
