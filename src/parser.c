#include "../interfaces/parser.h"
#include "../interfaces/lexer.h"
#include "../interfaces/interpreter.h"
#include <stdio.h>
#include <stdlib.h>

void parse() {
    Token token = getNextToken();

    while (token.type != TOKEN_EOF) {
        if (token.type == TOKEN_ASSIGN) {
            Token varToken = getNextToken();
            if (varToken.type != TOKEN_IDENTIFIER) {
                printf("Parser error: Expected variable name.\n");
                exit(1);
            }

            Token assignToken = getNextToken();
            if (assignToken.type != TOKEN_NUMBER) {
                printf("Parser error: Expected a number.\n");
                exit(1);
            }

            addVariable(varToken.value, atoi(assignToken.value));

            Token semicolon = getNextToken();
            if (semicolon.type != TOKEN_SEMICOLON) {
                printf("Parser error: Expected ';' at end of statement.\n");
                exit(1);
            }
        } else if (token.type == TOKEN_PRINT) {
            Token lparen = getNextToken();
            if (lparen.type != TOKEN_LPAREN) {
                printf("Parser error: Expected '('.\n");
                exit(1);
            }

            Token varToken = getNextToken();
            if (varToken.type != TOKEN_IDENTIFIER) {
                printf("Parser error: Expected variable name.\n");
                exit(1);
            }

            Token rparen = getNextToken();
            if (rparen.type != TOKEN_RPAREN) {
                printf("Parser error: Expected ')'.\n");
                exit(1);
            }

            printVariable(varToken.value);

            Token semicolon = getNextToken();
            if (semicolon.type != TOKEN_SEMICOLON) {
                printf("Parser error: Expected ';' at end of statement.\n");
                exit(1);
            }
        } else {
            printf("Parser error: Unexpected token '%s'.\n", token.value);
            exit(1);
        }

        token = getNextToken();
    }
}
