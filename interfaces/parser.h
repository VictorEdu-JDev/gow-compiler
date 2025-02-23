
#ifndef PARSER_H
#define PARSER_H

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

typedef enum node_type NodeType;
typedef struct ast_node ASTNode;

struct ast_node {
    NodeType type;
    ASTNode *left;
    ASTNode *right;
    char value[255];
};

ASTNode *parse();

#endif //PARSER_H
