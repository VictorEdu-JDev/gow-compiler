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

void handleReturn(ASTNode* node);
void addFunction(const char *name, ASTNode *body);
void executeAST(ASTNode *node);
void setVariable(const char *name, const char *value);

ASTNode *findFunctionNode(ASTNode *node, const char *name);

static Environment env;
int returnFlag = 0;

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
            addFunction(node->value, node->right);
            break;
        }
        case NODE_CALL: {
            callFunction(node->value);
            break;
        }
        case NODE_RETURN: {
            handleReturn(node);
            break;
        }
        default:
            break;
    }

    executeAST(node->left);
    executeAST(node->right);
}

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
    Variable *var = getVariable(name);
    if (var) {
        strncpy(var->value, value, sizeof(var->value) - 1);
        var->value[sizeof(var->value) - 1] = '\0';
    } else {
        if (env.var_count >= MAX_VARIABLES) {
            errorMessageInterp("Limite de variáveis atingido.");
        }

        Variable *newVar = &env.variables[env.var_count];

        strncpy(newVar->name, name, sizeof(newVar->name) - 1);
        newVar->name[sizeof(newVar->name) - 1] = '\0';

        strncpy(newVar->value, value, sizeof(newVar->value) - 1);
        newVar->value[sizeof(newVar->value) - 1] = '\0';

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

void handleReturn(ASTNode *node) {
    if (node->left) {
        setVariable("return_value", node->left->value);
    }
    returnFlag = 1;
}

void addFunction(const char *name, ASTNode *body) {
    if (env.func_count >= MAX_FUNCTIONS) {
        errorMessageInterp("Limite de funções atingido.");
    }

    strncpy(env.functions[env.func_count].name, name, sizeof(env.functions[env.func_count].name) - 1);
    env.functions[env.func_count].name[sizeof(env.functions[env.func_count].name) - 1] = '\0'; // Garantir que o nome termine com '\0'

    env.functions[env.func_count].body = body;
    env.func_count++;
}

void initInterpreter() {
    env.var_count = 0;
    env.func_count = 0;
}

void executeProgram(ASTNode *program) {
    ASTNode *omegaFunc = findFunctionNode(program, MAIN);

    if (omegaFunc) {
        if (omegaFunc->left) executeAST(omegaFunc->left);
        if (omegaFunc->right) executeAST(omegaFunc->right);
    } else errorMessageInterp("Funcao principal 'omega' nao encontrada.");
}

ASTNode *findFunctionNode(ASTNode *node, const char *name) {
    if (!node) return NULL;

    if (node->type == NODE_FUNCTION &&
        strcmp(node->value, name) == 0) return node;

    ASTNode *found = findFunctionNode(node->left, name);
    if (found) return found;

    return findFunctionNode(node->right, name);
}


int main() {
    const char *code = "runic soma { i am the u of 7; i am the v of 2; i am the w of u ascend v; redemption w; }"
    "runic omega { revenge soma; redemption 0; }";
    initLexer(code);
    initInterpreter();

    ASTNode *ast = parse();
    printAST(ast, 0);
    executeProgram(ast);

    return 0;
}
