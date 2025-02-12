#include "../interfaces/lexer.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

static const char *src;
static int pos = 0;

void initLexer(const char *source) {
    src = source;
    pos = 0;
}

Token getNextToken() {
    Token token;
    token.type = TOKEN_EOF;
    token.value[0] = '\0';

    while (isspace(src[pos])) pos++;

    if (src[pos] == '\0') {
        return token;
    }

    if (strncmp(src + pos, "i am the", 8) == 0) {
        token.type = TOKEN_ASSIGN;
        pos += 8;
        return token;
    }

    if (strncmp(src + pos, "of", 2) == 0) {
        token.type = TOKEN_OF;
        pos += 2;
        return token;
    }

    if (strncmp(src + pos, "face me", 7) == 0) {
        token.type = TOKEN_PRINT;
        pos += 7;
        return token;
    }

    // Busca palavras (identificadores)
    if (isalpha(src[pos])) {
        int start = pos;
        while (isalnum(src[pos])) pos++;
        int length = pos - start;
        strncpy(token.value, src + start, length);
        token.value[length] = '\0';
        token.type = TOKEN_IDENTIFIER;
        return token;
    }

    // Busca números
    if (isdigit(src[pos])) {
        int start = pos;
        while (isdigit(src[pos])) pos++;
        int length = pos - start;
        strncpy(token.value, src + start, length);
        token.value[length] = '\0';
        token.type = TOKEN_NUMBER;
        return token;
    }

    switch (src[pos]) {
    case '(':
        token.type = TOKEN_LPAREN;
        pos++;
        break;
    case ')':
        token.type = TOKEN_RPAREN;
        pos++;
        break;
    case ';':
        token.type = TOKEN_SEMICOLON;
        pos++;
        break;
    default:
        printf("Lexer error: Unknown character '%c'\n", src[pos]);
        pos++;
        break;
    }

    return token;
}
