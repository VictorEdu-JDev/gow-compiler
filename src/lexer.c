#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../interfaces/lexer.h"

enum token_type {
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_CALL,
    TOKEN_IDENTIFIER,
    TOKEN_ASSIGN,
    TOKEN_COMMA,
    TOKEN_SEMICOLON,
    TOKEN_EOF,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_BOOLEAN
};

enum keyword {
    KEYWORD_FUNCTION = "runic",
    KEYWORD_RETURN = "redemption",
    KEYWORD_CALL = "revenge",
    KEYWORD_FOR = "cyclone of chaos",
    KEYWORD_BREAK = "the cycle ends here",
    KEYWORD_ASSIGN = "i am the",
    KEYWORD_OF = "of",
};

enum logical_operator {
    LO_EQUAL = "olympic ascension",
    LO_NOTEQUAL = "olympic fury",
    LO_GREATER = "rage of sparta",
    LO_GREATEREQUAL = "rage of the gods",
    LO_LESS = "blade of olympus",
    LO_LESSEQUAL = "blade of chaos"
};

enum arithmetic_operator {
    AO_ADD = "ascend",
    AO_MINUS = "fall",
    AO_TIMES = "wrath",
    AO_DIVIDE = "betrayal",
    AO_MODULUS = "remains",
    LO_PLUS_PLUS = "power up",
    LO_MINUS_MINUS = "power down",
};

struct token {
    TokenType type;
    char value[50];
};

void skipWhitespace();
void handleSpecialCharacter(char currentChar, Token* token, int *pos);
int matchIdentifier(Token *token);
int matchInteger(Token *token);
int matchFloat(Token *token);
int matchDouble(Token *token);
int matchBoolean(Token *token);
int matchString(Token *token);
int matchKeyword(const char *keyword, TokenType type, Token *token);
int matchNumber(Token *token);

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
    skipWhitespace();

    if (matchKeyword(KEYWORD_FUNCTION, TOKEN_FUNCTION, &token)) {
        return token;
    }

    handleSpecialCharacter(src[pos], &token, &pos);
    return token;
}

void skipWhitespace() {
    while (isspace(src[pos])) {
        pos++;
    }
}

int matchInteger(Token *token) {
    if (isdigit(src[pos])) {
        int start = pos;
        while (isdigit(src[pos])) pos++;
        int length = pos - start;
        strncpy(token->value, src + start, length);
        token->value[length] = '\0';
        token->type = TOKEN_NUMBER;
        return 1;
    }
    return 0;
}

int matchFloat(Token *token) {
    if (isdigit(src[pos])) {
        int start = pos;
        while (isdigit(src[pos])) pos++;
        if (src[pos] == '.') {
            pos++;
            while (isdigit(src[pos])) pos++;
            strncpy(token->value, src + start, pos - start);
            token->value[pos - start] = '\0';
            token->type = TOKEN_FLOAT;
            return 1;
        }
    }
    return 0;
}

int matchDouble(Token *token) {
    if (isdigit(src[pos])) {
        int start = pos;
        while (isdigit(src[pos])) pos++;
        if (src[pos] == '.') {
            pos++;
            while (isdigit(src[pos])) pos++;
            strncpy(token->value, src + start, pos - start);
            token->value[pos - start] = '\0';
            token->type = TOKEN_DOUBLE;
            return 1;
        }
    }
    return 0;
}

int matchBoolean(Token *token) {
    if (strncmp(src + pos, "yes", 3) == 0) {
        strncpy(token->value, "yes", 3);
        token->value[3] = '\0';
        token->type = TOKEN_BOOLEAN;
        pos += 3;
        return 1;
    }

    if (strncmp(src + pos, "no", 2) == 0) {
        strncpy(token->value, "no", 2);
        token->value[2] = '\0';
        token->type = TOKEN_BOOLEAN;
        pos += 2;
        return 1;
    }
    return 0;
}


int matchString(Token *token) {
    if (src[pos] == '"') {
        int start = ++pos;
        while (src[pos] != '"' && src[pos] != '\0') pos++;
        int length = pos - start;
        if (src[pos] == '"') {
            strncpy(token->value, src + start, length);
            token->value[length] = '\0';
            token->type = TOKEN_STRING;
            pos++;
            return 1;
        }
    }
    return 0;
}

int matchKeyword(const char *keyword, TokenType type, Token *token) {
    size_t keywordLength = strlen(keyword);

    if (strncmp(src + pos, keyword, keywordLength) == 0) {
        token->type = type;
        strncpy(token->value, keyword, keywordLength);
        token->value[keywordLength] = '\0';
        pos += (int) keywordLength;
        return 1;
    }

    return 0;
}

int matchIdentifier(Token *token) {
    if (isalpha(src[pos])) {
        int start = pos;
        while (isalnum(src[pos])) pos++;
        int length = pos - start;
        strncpy(token->value, src + start, length);
        token->value[length] = '\0';
        token->type = TOKEN_IDENTIFIER;
        return 1;
    }
    return 0;
}

int matchNumber(Token *token) {
    return matchInteger(token) || matchFloat(token) || matchDouble(token);
}

void handleSpecialCharacter(char currentChar, Token *token, int *pos) {
    switch (currentChar) {
        case '{':
            token->type = TOKEN_LBRACE;
        break;
        case '}':
            token->type = TOKEN_RBRACE;
        break;
        case ';':
            token->type = TOKEN_SEMICOLON;
        break;
        case ',':
            token->type = TOKEN_COMMA;
        break;
        default:
            printf("Lexer error: Unknown character '%c'\n", currentChar);
        break;
    }
    (*pos)++;
}
