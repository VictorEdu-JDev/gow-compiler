
#include "../interfaces/symbol_table.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

void initSymbolTable(SymbolTable *table) {
    table->var_count = 0;
    table->func_count = 0;
}

int addVariable(SymbolTable *table, const char *name, VarType type, const char *value) {
    if (table->var_count >= MAX_VARIABLES) {
        printf("Erro: limite de variáveis atingido.\n");
        return -1;
    }

    Variable *var = &table->variables[table->var_count];
    strncpy(var->name, name, MAX_NAME_LENGTH - 1);
    var->name[MAX_NAME_LENGTH - 1] = '\0';
    var->type = type;

    char *valStr = (char *)value;

    switch (type) {
        case VAR_SCALAR:
            if (value) {
                if (strchr(valStr, '.')) {
                    var->value.scalarValue = atof(valStr);
                    printf("Variavel '%s' armazenada como DOUBLE: %f\n", name, var->value.scalarValue);
                } else {
                    var->value.scalarValue = atoi(valStr);
                    printf("Variavel '%s' armazenada como INT: %d\n", name, (int)var->value.scalarValue);
                }
            }
            break;
        case VAR_STRING:
            strncpy(var->value.stringValue, (char *)value, MAX_NAME_LENGTH - 1);
            var->value.stringValue[MAX_NAME_LENGTH - 1] = '\0';
            break;
        case VAR_BOOLEAN:
            var->value.booleanValue = *(int *)value;
            break;
    }

    table->var_count++;
    return 0;
}

int addFunction(SymbolTable *table, ASTNode *node) {
    if (table->func_count >= MAX_FUNCTIONS) {
        printf("Erro: limite de funções atingido.\n");
        return -1;
    }

    Function *func = &table->functions[table->func_count];
    strncpy(func->name, node->value, MAX_NAME_LENGTH - 1);
    func->name[MAX_NAME_LENGTH - 1] = '\0';
    func->parameters = node->right;
    func->body = node->left;

    table->func_count++;
    return 0;
}

Variable* getVariable(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->var_count; i++) {
        if (strcmp(table->variables[i].name, name) == 0) {
            return &table->variables[i];
        }
    }
    return NULL;
}

Function* getFunction(SymbolTable *table, const char *name) {
    for (int i = 0; i < table->func_count; i++) {
        if (strcmp(table->functions[i].name, name) == 0) {
            return &table->functions[i];
        }
    }
    return NULL;
}

void setVariable(SymbolTable *table, const char *name, void *value) {
    Variable *var = getVariable(table, name);
    if (var == NULL) {
        printf("Erro: variavel '%s' nao encontrada.\n", name);
        return;
    }

    switch (var->type) {
        case VAR_SCALAR:
            var->value.scalarValue = *(double *)value;
            break;
        case VAR_STRING:
            strncpy(var->value.stringValue, (char *)value, MAX_NAME_LENGTH - 1);
            var->value.stringValue[MAX_NAME_LENGTH - 1] = '\0';
            break;
        case VAR_BOOLEAN:
            var->value.booleanValue = *(int *)value;
            break;
    }
}

void printVariable(Variable *var) {
    switch (var->type) {
        case VAR_BOOLEAN:
            printf("Var %s = %d (int)\n", var->name, var->value.booleanValue);
            break;
        case VAR_SCALAR:
            printf("Var %s = %f (scalar)\n", var->name, var->value.scalarValue);
            break;
        case VAR_STRING:
            printf("Var %s = %s (string)\n", var->name, var->value.stringValue);
            break;
    }
}

void printFunction(Function *func) {
    printf("Func %s\n", func->name);
}

void printSymbolTable(SymbolTable *table) {
    printf("=== Tabela de Simbolos ===\n");

    printf("\nVariaveis:\n");
    for (int i = 0; i < table->var_count; i++) {
        printVariable(&table->variables[i]);
    }

    printf("\nFuncoes:\n");
    for (int i = 0; i < table->func_count; i++) {
        printFunction(&table->functions[i]);
    }
}

void freeSymbolTable(SymbolTable *table) {
    SymbolTable *tablePtr = table;
    return;
}

void funcExample() {
    printf("Função chamada: funcExample\n");
}
