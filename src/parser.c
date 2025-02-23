#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum node_type {
    NODE_FUNCTION,
    NODE_RETURN,
    NODE_CALL,
    NODE_ASSIGN,
    NODE_IF,
    NODE_ELSE,
    NODE_ELSEIF,
    NODE_FOR,
    NODE_BREAK,
    NODE_OPERATOR,
    NODE_IDENTIFIER,
    NODE_NUMBER,
    NODE_FLOAT,
    NODE_DOUBLE,
    NODE_BOOLEAN,
    NODE_STRING
};

struct ast_node {
    NodeType type;
    ASTNode *left;
    ASTNode *right;
    char value[255];
};

ASTNode *createNode(NodeType type, const char *value, ASTNode *left, ASTNode *right) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    node->type = type;

    if (value) {
        strncpy(node->value, value, sizeof(node->value) - 1);
        node->value[sizeof(node->value) - 1] = '\0';
    } else {
        node->value[0] = '\0';
    }
    node->left = left;
    node->right = right;
    return node;
}

static Token currentToken;
void errorMessage(Token token);

void advance() {
    currentToken = getNextToken();
}

void errorMessage(Token tp) {
    fprintf(stderr, "Erro: token inesperado '%s'\n", tp.value);
    exit(1);
}

void checkSemicolon() {
    if (currentToken.type == TOKEN_SEMICOLON) {
        advance();
    } else {
        fprintf(stderr, "Semicolon expected.\n");
        exit(EXIT_FAILURE);
    }
}


ASTNode *parseExpression();
ASTNode *parseStatement();
ASTNode *parseBlock();

ASTNode *parseExpression() {
    ASTNode *left = NULL;
    if (currentToken.type == TOKEN_CALL ||
        currentToken.type == TOKEN_NUMBER ||
        currentToken.type == TOKEN_STRING ||
        currentToken.type == TOKEN_FLOAT ||
        currentToken.type == TOKEN_DOUBLE ||
        currentToken.type == TOKEN_BOOLEAN ||
        currentToken.type == TOKEN_IDENTIFIER) {

        NodeType nodeType = (currentToken.type == TOKEN_IDENTIFIER) ? NODE_IDENTIFIER :
                            (currentToken.type == TOKEN_FLOAT) ? NODE_FLOAT :
                            (currentToken.type == TOKEN_DOUBLE) ? NODE_DOUBLE :
                            (currentToken.type == TOKEN_BOOLEAN) ? NODE_BOOLEAN :
                            (currentToken.type == TOKEN_CALL) ? NODE_CALL :
                            NODE_NUMBER;

        left = createNode(nodeType, currentToken.value, NULL, NULL);
        advance();
    } else {
        printf("Ero aqui\n");
        errorMessage(currentToken);
    }

    if (currentToken.type == TOKEN_OPERATOR) {
        char op[255];
        strncpy(op, currentToken.value, sizeof(op) - 1);
        op[sizeof(op) - 1] = '\0';
        advance();
        ASTNode *right = parseExpression();
        return createNode(NODE_OPERATOR, op, left, right);
    }

    return left;
}

ASTNode *parseStatement() {

    if (currentToken.type == TOKEN_FUNCTION) {
        advance();
        if (currentToken.type == TOKEN_IDENTIFIER) {
            char funcName[255];
            strncpy(funcName, currentToken.value, sizeof(funcName) - 1);
            funcName[sizeof(funcName) - 1] = '\0';
            advance();
            if (currentToken.type == TOKEN_LBRACE) {
                ASTNode *body = parseBlock();
                return createNode(NODE_FUNCTION, funcName, body, NULL);
            }
            errorMessage(currentToken);
        }
        errorMessage(currentToken);
    }

    if (currentToken.type == TOKEN_ASSIGN) {
        advance();
        if (currentToken.type == TOKEN_IDENTIFIER) {
            char varName[255];
            strncpy(varName, currentToken.value, sizeof(varName) - 1);
            varName[sizeof(varName) - 1] = '\0';
            advance();

            if (currentToken.type == TOKEN_ASSIGN_SIGNAL) {
                advance();
                ASTNode *expr = parseExpression();
                checkSemicolon();
                return createNode(NODE_ASSIGN, varName, expr, NULL);
            }
            errorMessage(currentToken);
        }
        errorMessage(currentToken);
    }

    if (currentToken.type == TOKEN_IF) {
        advance();
        ASTNode *condition = parseExpression();
        ASTNode *body = parseBlock();
        return createNode(NODE_IF, getKeywordStr(KEYWORD_IF), condition, body);
    }

    if (currentToken.type == TOKEN_RETURN) {
        advance();
        ASTNode *expr = parseExpression();
        checkSemicolon();
        return createNode(NODE_RETURN, getKeywordStr(KEYWORD_RETURN), expr, NULL);
    }
    return NULL;
}

ASTNode *parseBlock() {
    if (currentToken.type == TOKEN_LBRACE) {
        advance();
        ASTNode *block = NULL;
        ASTNode *lastStmt = NULL;

        while (currentToken.type != TOKEN_RBRACE &&
            currentToken.type != TOKEN_EOF) {
            ASTNode *stmt = parseStatement();
            if (stmt) {
                if (!block) {
                    block = stmt;
                } else {
                    lastStmt->right = stmt;
                }
                lastStmt = stmt;
            }
            advance();
        }
        return block;
    }
    return NULL;
}

ASTNode *parse() {
    advance();
    return parseStatement();
}

void printAST(ASTNode *node, int level) {
    if (!node) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("%s\n", node->value);
    printAST(node->left, level + 1);
    printAST(node->right, level + 1);
}

int main() {
    const char *code = "runic omega { i am the x of _no; redemption 0; }";
    initLexer(code);
    ASTNode *ast = parse();
    printAST(ast, 0);
    return 0;
}
