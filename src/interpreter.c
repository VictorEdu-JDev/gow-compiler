#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct variable {
    char name[255];
    char value[255];
};

struct function {
    char name[255];
    ASTNode *body;
};

struct environment {
    Variable variables[MAX_VARIABLES];
    Function functions[MAX_FUNCTIONS];
    int var_count;
    int func_count;
};

void executeAST(ASTNode *node);

static struct environment env;

void errorMessageInterp(const char *message) {
    fprintf(stderr, "Erro: %s\n", message);
    exit(1);
}

Variable* getVariable(const char *name) {
    for (int i = 0; i < env.var_count; i++) {
        if (strcmp(env.variables[i].name, name) == 0) {
            return &env.variables[i];
        }
    }
    return NULL;
}

Function* getFunction(const char *name) {
    for (int i = 0; i < env.func_count; i++) {
        if (strcmp(env.functions[i].name, name) == 0) {
            return &env.functions[i];
        }
    }
    return NULL;
}

void setVariable(const char *name, const char *value) {
    struct variable *var = getVariable(name);
    if (var) {
        strncpy(var->value, value, sizeof(var->value) - 1);
        var->value[sizeof(var->value) - 1] = '\0';
    } else {
        if (env.var_count >= MAX_VARIABLES) {
            errorMessageInterp("Limite de variáveis atingido.");
        }
        strncpy(env.variables[env.var_count].name,
            name, sizeof(env.variables[env.var_count].name) - 1);
        strncpy(env.variables[env.var_count].value,
            value, sizeof(env.variables[env.var_count].value) - 1);
        env.var_count++;
    }
}

void callFunction(const char *name) {
    struct function *func = getFunction(name);
    if (!func) {
        errorMessageInterp("Funcao nao encontrada.");
    }
    executeAST(func->body);
}

void executeAST(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_ASSIGN: {
            setVariable(node->value, node->left->value);
            break;
        }
        case NODE_OPERATOR: {
            break;
        }
        case NODE_IF: {
            break;
        }
        case NODE_FUNCTION: {
            if (env.func_count >= MAX_FUNCTIONS) {
                errorMessageInterp("Limite de funcoes atingido.");
            }
            struct function new_func;
            strncpy(new_func.name, node->value, sizeof(new_func.name) - 1);
            new_func.body = node->left;
            env.functions[env.func_count++] = new_func;
            break;
        }
        case NODE_CALL: {
            callFunction(node->value);
            break;
        }
        case NODE_RETURN: {
            break;
        }
        default:
            break;
    }

    executeAST(node->left);
    executeAST(node->right);
}

void initInterpreter() {
    env.var_count = 0;
    env.func_count = 0;
}

void executeProgram(ASTNode *program) {
    for (int i = 0; i < env.func_count; i++) {
        if (strcmp(env.functions[i].name, "omega") == 0) {
            executeAST(env.functions[i].body);
            return;
        }
    }
    errorMessageInterp("Funcao principal 'omega' nao encontrada.");
}

int main() {
    const char *code = "runic omega { i am the x of 10; redemption 0; }";
    initLexer(code);
    initInterpreter();

    ASTNode *ast = parse();

    executeProgram(ast);

    return 0;
}
