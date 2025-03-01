//
// Created by Victor on 28/02/2025.
//

#ifndef AST_H
#define AST_H

#define MAX_STRING_LENGTH 255

typedef enum {
    NODE_BINARY_OP,
    NODE_UNARY_OP,
    NODE_LITERAL,
    NODE_VARIABLE,
    NODE_ASSIGNMENT,
    NODE_IF,
    NODE_WHILE,
    NODE_FOR,
    NODE_FUNCTION,
    NODE_FUNCTION_CALL,
    NODE_RETURN,
    NODE_BLOCK
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    char value[MAX_STRING_LENGTH];
    struct ASTNode *left;
    struct ASTNode *right;
    struct ASTNode *next;
} ASTNode;

ASTNode* createNode(ASTNodeType type,
    const char *value,
    ASTNode *left, ASTNode *right, ASTNode *next);
void freeAST(ASTNode *node);
void printAST(ASTNode *node, int level);

#endif //AST_H
