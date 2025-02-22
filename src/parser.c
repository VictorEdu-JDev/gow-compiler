#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

typedef enum node_type {
    NODE_FUNCTION,
    NODE_CALL,
    NODE_IDENTIFIER,
    NODE_OPERATOR,
    NODE_LITERAL,
    NODE_TYPE_COUNT
} NodeType;

typedef struct ast_node {
    NodeType type;
    char value[256];
    struct ast_node *left;
    struct ast_node *right;
} Node;

Node* newAstNode(NodeType type, const char *value) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->type = type;
    strncpy(node->value, value, 255);
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeAstNode(Node* node) {
    if (node == NULL) return;
    freeAstNode(node->left);
    freeAstNode(node->right);
    free(node);
}

Node* parseFunctionDeclaration() {
    Token token = getNextToken();

    if (token.type != TOKEN_IDENTIFIER || strcmp(token.value, "runic") != 0) {
        return NULL;
    }

    Token funcNameToken = getNextToken();
    if (funcNameToken.type != TOKEN_IDENTIFIER) {
        return NULL;
    }

    Node* functionNode = newAstNode(NODE_FUNCTION, funcNameToken.value);

    token = getNextToken();

    if (token.type != TOKEN_LBRACE) {
        return NULL;
    }

    token = getNextToken();
    while (token.type != TOKEN_RBRACE) {
        token = getNextToken();
    }

    return functionNode;
}

Node* parseFunctionReturn() {
    Token token = getNextToken();
    if (token.type != TOKEN_IDENTIFIER || strcmp(token.value, "redemption") != 0) {
        return NULL;
    }

    Token returnValueToken = getNextToken();
    if (returnValueToken.type != TOKEN_NUMBER) {
        return NULL;
    }

    Node* returnNode = newAstNode(NODE_OPERATOR, returnValueToken.value);
    return returnNode;
}

void parse() {
    while (1) {
        Token token = getNextToken();
        if (token.type == TOKEN_EOF) break;

        Node* funcDecl = parseFunctionDeclaration();

        if (funcDecl != NULL) {
            printf("Função declarada: %s\n", funcDecl->value);
            freeAstNode(funcDecl);
            continue;
        }

        Node* funcReturn = parseFunctionReturn();
        if (funcReturn != NULL) {
            printf("Liberou memoria.\n");
            printf("Retorno: %s\n", funcReturn->value);
            freeAstNode(funcReturn);
            continue;
        }

    }
}

int main() {
    const char* sourceCode = "runic main { redemption 0; }";
    initLexer(sourceCode);
    parse();
    return 0;
}
