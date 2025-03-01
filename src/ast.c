//
// Created by Victor on 28/02/2025.
//

#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode* createNode(ASTNodeType type,
    const char *value,
    ASTNode *left, ASTNode *right, ASTNode *next) {
    ASTNode *node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = type;
    strncpy(node->value, value, MAX_STRING_LENGTH - 1);
    node->left = left;
    node->right = right;
    node->next = next;
    return node;
}

void freeAST(ASTNode *node) {
    if (node == NULL) return;
    freeAST(node->left);
    freeAST(node->right);
    freeAST(node->next);
    free(node);
}


void printAST(ASTNode *node, int level) {
    if (!node) return;

    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    printf("Node Type: %d, Value: %s\n", node->type, node->value);

    if (node->left) {
        for (int i = 0; i < level + 1; i++) {
            printf("  ");
        }
        printf("Left -> ");
        printAST(node->left, level + 1);
    }

    if (node->right) {
        for (int i = 0; i < level + 1; i++) {
            printf("  ");
        }
        printf("Right -> ");
        printAST(node->right, level + 1);
    }

    if (node->next) {
        for (int i = 0; i < level + 1; i++) {
            printf("  ");
        }
        printf("Next -> ");
        printAST(node->next, level + 1);
    }
}
