#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parseExpression();
ASTNode *parseStatement();
ASTNode *parseBlock();
ASTNode *parseFunction();
ASTNode *parseAssignment();
ASTNode *parseIfStatement();
ASTNode *parseReturnStatement();
ASTNode *parseExpression();
ASTNode *createExpressionNode();
NodeType getNodeTypeForToken(TokenType type);
ASTNode *createNode(NodeType type, const char *value, ASTNode *left, ASTNode *right);
ASTNode *parseStatements();
void errorMessage(Token token);
void advance();

static Token currentToken;

ASTNode *parse() {
    advance();
    return parseStatement();
}

void advance() {
    currentToken = getNextToken();
}

void errorMessage(Token tp) {
    fprintf(stderr, "Erro: token inesperado '%s'\n", tp.value);
    exit(1);
}

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

void checkSemicolon() {
    if (currentToken.type == TOKEN_SEMICOLON) {
        advance();
    } else {
        fprintf(stderr, "Erro: esperado ';' antes de '%s'.\n", currentToken.value);
        exit(EXIT_FAILURE);
    }
}

ASTNode *parseExpression() {
    ASTNode *left = createExpressionNode();
    if (left == NULL) return NULL;

    if (currentToken.type == TOKEN_OPERATOR) {
        printf("%s\n", currentToken.value);
        char op[255];
        strncpy(op, currentToken.value, sizeof(op) - 1);
        op[sizeof(op) - 1] = '\0';
        advance();
        ASTNode *right = parseExpression();
        return createNode(NODE_OPERATOR, op, left, right);
    }

    return left;
}

ASTNode *createExpressionNode() {
    if (currentToken.type == TOKEN_CALL ||
        currentToken.type == TOKEN_NUMBER ||
        currentToken.type == TOKEN_STRING ||
        currentToken.type == TOKEN_FLOAT ||
        currentToken.type == TOKEN_DOUBLE ||
        currentToken.type == TOKEN_BOOLEAN ||
        currentToken.type == TOKEN_IDENTIFIER) {

        NodeType nodeType = getNodeTypeForToken(currentToken.type);
        ASTNode *node = createNode(nodeType, currentToken.value, NULL, NULL);
        advance();
        return node;
        }
    errorMessage(currentToken);
    return NULL;
}

NodeType getNodeTypeForToken(TokenType type) {
    switch (type) {
        case TOKEN_IDENTIFIER: return NODE_IDENTIFIER;
        case TOKEN_FLOAT: return NODE_FLOAT;
        case TOKEN_DOUBLE: return NODE_DOUBLE;
        case TOKEN_BOOLEAN: return NODE_BOOLEAN;
        case TOKEN_CALL: return NODE_CALL;
        default: return NODE_NUMBER;
    }
}

ASTNode *parseStatement() {
    switch (currentToken.type) {
        case TOKEN_FUNCTION:
            return parseFunction();
        case TOKEN_ASSIGN:
            return parseAssignment();
        case TOKEN_IF:
            return parseIfStatement();
        case TOKEN_RETURN:
            return parseReturnStatement();
        default:
            return NULL;
    }
}

ASTNode *parseFunction() {
    advance();

    if (currentToken.type != TOKEN_IDENTIFIER)
        errorMessage(currentToken);

    char funcName[255];
    strncpy(funcName, currentToken.value, sizeof(funcName) - 1);
    funcName[sizeof(funcName) - 1] = '\0';
    advance();

    if (currentToken.type != TOKEN_LBRACE)
        errorMessage(currentToken);

    ASTNode *body = parseBlock();

    return createNode(NODE_FUNCTION, funcName, body, NULL);
}

ASTNode *parseAssignment() {
    advance();
    if (currentToken.type != TOKEN_IDENTIFIER)
        errorMessage(currentToken);

    char varName[255];
    strncpy(varName, currentToken.value, sizeof(varName) - 1);
    varName[sizeof(varName) - 1] = '\0';
    advance();

    if (currentToken.type != TOKEN_ASSIGN_SIGNAL)
        errorMessage(currentToken);

    advance();
    ASTNode *expr = parseExpression();
    checkSemicolon();
    return createNode(NODE_ASSIGN, varName, expr, NULL);
}

ASTNode *parseIfStatement() {
    advance();
    ASTNode *condition = parseExpression();
    ASTNode *body = parseBlock();
    return createNode(NODE_IF, getKeywordStr(KEYWORD_IF), condition, body);
}

ASTNode *parseReturnStatement() {
    advance();
    ASTNode *expr = parseExpression();
    checkSemicolon();
    return createNode(NODE_RETURN, getKeywordStr(KEYWORD_RETURN), expr, NULL);
}

ASTNode *parseBlock() {
    if (currentToken.type != TOKEN_LBRACE) return NULL;
    advance();

    ASTNode *block = parseStatements();

    if (currentToken.type == TOKEN_RBRACE) {
        advance();
    } else {
        errorMessage(currentToken);
    }

    return block;
}

ASTNode *parseStatements() {
    ASTNode *firstStmt = NULL;
    ASTNode *lastStmt = NULL;

    while (currentToken.type != TOKEN_RBRACE &&
        currentToken.type != TOKEN_EOF) {
        ASTNode *stmt = parseStatement();
        if (stmt) {
            if (!firstStmt) firstStmt = stmt;
            else lastStmt->right = stmt;
            lastStmt = stmt;
        }
    }

    return firstStmt;
}
