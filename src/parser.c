#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *parseStatement();
ASTNode *parseBlock();
ASTNode *parseFunction();
ASTNode *parseAssignment();
ASTNode *parseIfStatement();
ASTNode *parseReturnStatement();
ASTNode *parseExpression();
ASTNode *parseStatements();
ASTNode *parseFunctionCall();
ASTNode *parseFactor();
ASTNode *parseTerm();
void errorMessage(Token token);
void advance();
void checkSemicolon();

static Token currentToken;

ASTNode *parse() {
    advance();
    return parseStatements();
}

void advance() {
    currentToken = getNextToken();
}

void errorMessage(Token tp) {
    fprintf(stderr, "Garoto! Nao conheco essa língua! Nao compreendo esta runa: '%s'\n", tp.value);
    exit(1);
}

void checkSemicolon() {
    if (currentToken.type == TOKEN_SEMICOLON) {
        advance();
    } else {
        fprintf(stderr, "Garoto! Escreva esta runa ';' antes de '%s'.\n", currentToken.value);
        exit(EXIT_FAILURE);
    }
}

ASTNode *parseStatements() {
    ASTNode *firstStmt = NULL;
    ASTNode *lastStmt = NULL;

    while (currentToken.type != TOKEN_RBRACE && currentToken.type != TOKEN_EOF) {
        ASTNode *stmt = parseStatement();
        if (stmt != NULL) {
            if (!firstStmt) {
                firstStmt = stmt;
            } else {
                if (lastStmt) lastStmt->next = stmt;
            }
            lastStmt = stmt;
        }
    }
    return firstStmt;
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
        case TOKEN_CALL:
            return parseFunctionCall();
        default:
            errorMessage(currentToken);
            return NULL;
    }
}

ASTNode *parseFunction() {
    advance();
    if (currentToken.type != TOKEN_IDENTIFIER)
        errorMessage(currentToken);

    char funcName[MAX_STRING_LENGTH];
    strncpy(funcName, currentToken.value, MAX_STRING_LENGTH - 1);
    advance();

    ASTNode *body = parseBlock();
    return createNode(NODE_FUNCTION, funcName, body, NULL, NULL);
}

ASTNode *parseAssignment() {
    advance();
    if (currentToken.type != TOKEN_IDENTIFIER)
        errorMessage(currentToken);

    char varName[MAX_STRING_LENGTH];
    strncpy(varName, currentToken.value, MAX_STRING_LENGTH - 1);
    advance();

    if (currentToken.type != TOKEN_ASSIGN_SIGNAL)
        errorMessage(currentToken);

    advance();
    ASTNode *expr = parseExpression();
    checkSemicolon();
    return createNode(NODE_ASSIGNMENT, varName, expr, NULL, NULL);
}

ASTNode *parseIfStatement() {
    advance();
    ASTNode *condition = parseExpression();
    ASTNode *body = parseBlock();
    return createNode(NODE_IF, getKeywordStr(KEYWORD_IF), condition, body, NULL);
}

ASTNode *parseReturnStatement() {
    advance();
    ASTNode *expr = parseExpression();
    checkSemicolon();
    return createNode(NODE_RETURN, getKeywordStr(KEYWORD_RETURN), expr, NULL, NULL);
}

ASTNode *parseBlock() {
    if (currentToken.type != TOKEN_LBRACE) return NULL;
    advance();
    ASTNode *block = parseStatements();
    if (currentToken.type == TOKEN_RBRACE) advance();
    else errorMessage(currentToken);
    return block;
}

ASTNode *parseExpression() {
    ASTNode *left = parseTerm();
    while (currentToken.type == TOKEN_OPERATOR) {
        char op[MAX_STRING_LENGTH];
        strncpy(op, currentToken.value, MAX_STRING_LENGTH - 1);
        advance();
        ASTNode *right = parseTerm();
        left = createNode(NODE_BINARY_OP, op, left, right, NULL);
    }
    return left;
}

ASTNode *parseTerm() {
    ASTNode *left = parseFactor();
    while (currentToken.type == TOKEN_OPERATOR) {
        char op[MAX_STRING_LENGTH];
        strncpy(op, currentToken.value, MAX_STRING_LENGTH - 1);
        advance();
        ASTNode *right = parseFactor();
        left = createNode(NODE_BINARY_OP, op, left, right, NULL);
    }
    return left;
}

ASTNode *parseFactor() {
    if (currentToken.type == TOKEN_NUMBER) {
        ASTNode *node = createNode(NODE_LITERAL, currentToken.value, NULL, NULL, NULL);
        advance();
        return node;
    }
    if (currentToken.type == TOKEN_IDENTIFIER) {
        ASTNode *node = createNode(NODE_VARIABLE, currentToken.value, NULL, NULL, NULL);
        advance();
        return node;
    }
    errorMessage(currentToken);
    return NULL;
}

ASTNode *parseFunctionCall() {
    advance();
    char funcName[MAX_STRING_LENGTH];
    strncpy(funcName, currentToken.value, MAX_STRING_LENGTH - 1);
    advance();

    ASTNode *args = NULL;
    ASTNode *lastArg = NULL;
    while (currentToken.type != TOKEN_SEMICOLON) {
        ASTNode *arg = parseExpression();
        if (!arg) break;
        if (!args) args = arg;
        else if (lastArg) lastArg->next = arg;
        lastArg = arg;
    }
    checkSemicolon();
    return createNode(NODE_FUNCTION_CALL, funcName, args, NULL, NULL);
}