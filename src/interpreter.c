
#include "lexer.h"
#include "parser.h"
#include "symbol_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static SymbolTable symbolTable;

void execute(ASTNode *node);
void executeStatements(ASTNode *node);
void executeAssignment(ASTNode *node);
void executeIfStatement(ASTNode *node);
void executeReturnStatement(ASTNode *node);
void executeFunctionCall(ASTNode *node);
void executeBinaryOp(ASTNode *node);
void handleFunction(ASTNode *node);
void handleAddVariable(ASTNode* node);

int main() {
    const char *code = "runic soma { i am the u of 7; i am the v of 2; i am the w of u ascend v; redemption w; }"
                        "runic omega { revenge soma; redemption 0; }";

    initLexer(code);
    ASTNode *ast = parse();

    initSymbolTable(&symbolTable);
    printAST(ast, 0);
    if (ast) execute(ast);

    printSymbolTable(&symbolTable);

    return 0;
}

void execute(ASTNode *node) {
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
        case NODE_VARIABLE:
            break;
        case NODE_BINARY_OP:
            executeBinaryOp(node);
        break;
        default:
            break;
    }
    if (node->next) execute(node->next);
}
void handleFunction(ASTNode* node) {
    Function *existingFunction = getFunction(&symbolTable, node->value);

    if (existingFunction != NULL) {
        printf("Erro: runico '%s' já equipado.\n", node->value);
    } else {
        addFunction(&symbolTable, node->value, NULL);
        printf("Runico '%s' equipado com sucesso.\n", node->value);
    }
    if (node->left) execute(node->left);
    if (node->right) execute(node->right);
}

void handleAddVariable(ASTNode *node) {
}

void executeAssignment(ASTNode *node) {
    Variable *var = getVariable(&symbolTable, node->value);
    if (var) {
        printf("Erro: variável '%s' já existe.\n", node->value);
        exit(EXIT_FAILURE);
    }

    if (node->left) addVariable(&symbolTable, node->value, VAR_SCALAR, node->left->value);
        node->type = NODE_VARIABLE;
}


// Função para executar um bloco de declarações
void executeStatements(ASTNode *node) {
    while (node != NULL) {
        execute(node);
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
        printf("Tratando cahmada de funcao %s\n", node->value);
    }
}

// Função para executar operações binárias
void executeBinaryOp(ASTNode *node) {
    ASTNode *left = node->left;
    ASTNode *right = node->right;

    if (left && right) {
        int leftValue = atoi(left->value);
        int rightValue = atoi(right->value);

        if (strcmp(getOperator(AO_ADD), node->value) == 0) {
            setVariable(&symbolTable, node->value, (void*)(leftValue + rightValue));
        } else if (strcmp(getOperator(AO_MINUS), node->value) == 0) {
            setVariable(&symbolTable, node->value, (void*)(leftValue - rightValue));
        } else if (strcmp(getOperator(AO_TIMES), node->value) == 0) {
            setVariable(&symbolTable, node->value, (void*)(leftValue * rightValue));
        } else if (strcmp(getOperator(AO_DIVIDE), node->value) == 0) {
            if (rightValue != 0) {
                setVariable(&symbolTable, node->value, (void*)(leftValue / rightValue));
            }
        }
    }
}