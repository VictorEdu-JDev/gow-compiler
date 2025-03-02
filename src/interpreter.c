
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"
#include "interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static SymbolTable symbolTable;

void execute(ASTNode *node, SymbolTable* table);
void executeStatements(ASTNode *node);
void executeAssignment(ASTNode *node);
void executeIfStatement(ASTNode *node);
void executeReturnStatement(ASTNode *node);
void executeFunctionCall(ASTNode *node);
void executeBinaryOp(ASTNode *node, SymbolTable *table);
void handleFunction(ASTNode *node);
void handleAddVariable(ASTNode* node);
void executeGlobal(ASTNode *program);
ASTNode *findFunction(ASTNode *node, const char *name);
void registerFunctions(ASTNode *node);

int main() {
    const char *code = "runic testeFuncao { i am the var1 of 300; i am the var2 of 187; i am the var3 of var1 betrayal var2; redemption var3; }"
                        "runic omega { revenge testeFuncao; redemption 0; }";

    initLexer(code);
    ASTNode *ast = parse();

    initSymbolTable(&symbolTable);
    printAST(ast, 0);
    if (ast) executeGlobal(ast);

    printSymbolTable(&symbolTable);

    return 0;
}

void execute(ASTNode *node, SymbolTable *table) {
    switch (node->type) {
        case NODE_FUNCTION:
            handleFunction(node);
            break;
        case NODE_ASSIGNMENT:
            executeAssignment(node);
        break;
        case NODE_IF:
            executeIfStatement(node);
        break;
        case NODE_RETURN:
            executeReturnStatement(node);
        break;
        case NODE_FUNCTION_CALL:
            executeFunctionCall(node);
        break;
        case NODE_BINARY_OP:
            executeBinaryOp(node, table);
        break;
        default:
            break;
    }
    if (node->next) execute(node->next, table);
}

void registerFunctions(ASTNode *node) {
    if (!node) return;

    if (node->type == NODE_FUNCTION) {
        addFunction(&symbolTable, node);
    }

    registerFunctions(node->next);
}

ASTNode *findFunction(ASTNode *node, const char *name) {
    if (!node) return NULL;
    if (node->type == NODE_FUNCTION && strcmp(node->value, name) == 0) {
        return node;
    }
    return findFunction(node->next, name);
}

void executeGlobal(ASTNode *program) {
    registerFunctions(program);
    ASTNode *omegaFunc = findFunction(program, MAIN);
    if (!omegaFunc) {
        printf("Erro: Funcao omega nao encontrada!\n");
        exit(EXIT_FAILURE);
    }
    execute(omegaFunc->left, &symbolTable);
}


void handleFunction(ASTNode* node) {
    Function *existingFunction = getFunction(&symbolTable, node->value);

    if (existingFunction != NULL) {
        printf("Erro: runico '%s' já equipado.\n", node->value);
    } else {
        addFunction(&symbolTable, node);
        printf("Runico '%s' equipado com sucesso.\n", node->value);
    }
}

void handleAddVariable(ASTNode *node) {
}

void executeAssignment(ASTNode *node) {
    Variable *var = getVariable(&symbolTable, node->value);
    if (var) {
        printf("Erro: variavel '%s' ja existe.\n", node->value);
        exit(EXIT_FAILURE);
    }

    if (node->left != NULL &&
        node->left->type != NODE_BINARY_OP) {
        addVariable(&symbolTable, node->value, VAR_SCALAR, node->left->value);
    } else {
        const char *op = 0;
        addVariable(&symbolTable, node->value, VAR_SCALAR, op);
        executeBinaryOp(node, &symbolTable);
    }

    node->type = NODE_VARIABLE;
}


// Função para executar um bloco de declarações
void executeStatements(ASTNode *node) {
    while (node != NULL) {
        execute(node, &symbolTable);
        node = node->next;
    }
}

// Função para executar uma declaração "if"
void executeIfStatement(ASTNode *node) {
    ASTNode *condition = node->left;
    if (condition) {
        int conditionValue = atoi(condition->value);
        if (conditionValue) {
            executeStatements(node->right);
        }
    }
}

// Função para executar uma declaração "return"
void executeReturnStatement(ASTNode *node) {
    if (node->left) {
        // Retorna o valor, sem imprimir
    }
}

// Função para executar a chamada de função
void executeFunctionCall(ASTNode *node) {
    Function *func = getFunction(&symbolTable, node->value);
    if (func) {
        ASTNode *paramNode = func->parameters;
        ASTNode *argNode = node->right;

        while (paramNode && argNode) {
            Variable var;
            strcpy(var.name, paramNode->value);
            addVariable(&symbolTable, var.name, node->type, node->value);
            paramNode = paramNode->next;
            argNode = argNode->next;
        }

        execute(func->body, &symbolTable);
    }
}

// Função para executar operações binárias
void executeBinaryOp(ASTNode *nodePrev, SymbolTable *table) {
    const ASTNode* node = nodePrev->left;
    const ASTNode *left = node->left;
    const ASTNode *right = node->right;


    if (left && right) {
        const Variable* vLeft = getVariable(table, left->value);
        const Variable* vRight = getVariable(table, right->value);

        if (strcmp(getOperator(AO_ADD), node->value) == 0) {
            double value = (vLeft->value.scalarValue + vRight->value.scalarValue);
            setVariable(&symbolTable, nodePrev->value, &value);
        } else if (strcmp(getOperator(AO_MINUS), node->value) == 0) {
            double value = (vLeft->value.scalarValue - vRight->value.scalarValue);
            setVariable(&symbolTable, nodePrev->value, &value);
        } else if (strcmp(getOperator(AO_TIMES), node->value) == 0) {
            double value = (vLeft->value.scalarValue * vRight->value.scalarValue);
            setVariable(&symbolTable, nodePrev->value, &value);
        } else if (strcmp(getOperator(AO_DIVIDE), node->value) == 0) {
            if (vRight->value.scalarValue != 0) {
                double value = (vLeft->value.scalarValue / vRight->value.scalarValue);
                setVariable(&symbolTable, nodePrev->value, &value);
            }
        }
    }
}