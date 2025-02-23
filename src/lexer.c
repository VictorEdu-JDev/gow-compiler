#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../interfaces/lexer.h"

const char *keywordStrings[] = {
    "runic",                // KEYWORD_FUNCTION
    "redemption",           // KEYWORD_RETURN
    "revenge",              // KEYWORD_CALL
    "cyclone of chaos",     // KEYWORD_FOR
    "the cycle ends here",  // KEYWORD_BREAK
    "i am the",             // KEYWORD_ASSIGN
    "of",                   // KEYWORD_OF
    "trial",                // KEYWORD_IF
    "fate",                 // KEYWORD_ELSE
    "fate else",            // KEYWORD_ELSEIF
    "yes",                  // KEYWORD_TRUE
    "no",                   // KEYWORD_FALSE
    "hyperion ram",         // KEYWORD_WHILE
    "spartan charge",       // KEYWORD_DO_WHILE
    "rapid switch",         // KEYWORD_SWITCH
    "destiny"               // KEYWORD_CASE
};

const Operator operators[] = {
    { LO_EQUAL, "olympic ascension" },
    { LO_NOTEQUAL, "olympic fury" },
    { LO_GREATER, "rage of sparta" },
    { LO_GREATEREQUAL, "rage of the gods" },
    { LO_LESS, "blade of olympus" },
    { LO_LESSEQUAL, "blade of chaos" },
    { LO_AND, "axe" },
    { LO_OR, "blade" },
    { LO_XOR, "death" },
    { AO_ADD, "ascend" },
    { AO_MINUS, "fall" },
    { AO_TIMES, "wrath" },
    { AO_DIVIDE, "betrayal" },
    { AO_MODULUS, "remains" },
    { AO_PLUS_PLUS, "power up" },
    { AO_MINUS_MINUS, "power down" }
};

const char* getOperator(OperatorType type);
const char *getKeywordStr(Keyword key);

void skipWhitespace();
void skipComments();

int matchKeyword(Token *token);
int matchIdentifier(Token *token);

int matchInteger(Token *token);
int matchFloatOrDouble(Token *token);
int matchBoolean(Token *token);
int matchString(Token *token);
int matchNumber(Token *token);

int matchOperator(Token *token);

int handleSpecialCharacter(char currentChar, Token *token, int *pos);

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

    while (src[pos] != '\0') {
        skipWhitespace();
        skipComments();

        if (matchKeyword(&token)) return token;
        if (matchIdentifier(&token)) return token;

        if (matchNumber(&token)) return token;
        if (matchString(&token)) return token;
        if (matchBoolean(&token)) return token;

        if (handleSpecialCharacter(src[pos], &token, &pos)) return token;
    }
    return token;
}

void skipWhitespace() {
    while (isspace(src[pos])) {
        pos++;
    }
}

int matchKeyword(Token *token) {
    for (int i = 0; i < KEYWORD_COUNT; i++) {
        const char *keywordStr = getKeywordStr(i);
        const size_t keywordLength = strlen(keywordStr);

        if (strncmp(src + pos, keywordStr, keywordLength) == 0) {
            token->type = (TokenType)i;
            strncpy(token->value, keywordStr, keywordLength);
            token->value[keywordLength] = '\0';
            pos += (int) keywordLength;
            return 1;
        }
    }
    return 0;
}

int matchIdentifier(Token *token) {
    if (pos >= strlen(src)) return 0;

    if (isalpha(src[pos]) || src[pos] == '_') {
        const int start = pos;

        while (pos < strlen(src) &&
               (isalnum(src[pos]) ||
                src[pos] == '_')) {
            pos++;
                }

        const int length = pos - start;
        if (length >= sizeof(token->value)) {
            printf("Comprimento de identificador superior ao limite de 255 caracteres.\n");
            return 0;
        }

        strncpy(token->value, src + start, length);
        token->value[length] = '\0';
        token->type = TOKEN_IDENTIFIER;
        return 1;
    }
    return 0;
}



int matchInteger(Token *token) {
    if (isdigit(src[pos])) {
        const int start = pos;
        while (isdigit(src[pos])) pos++;
        const int length = pos - start;
        strncpy(token->value, src + start, length);
        token->value[length] = '\0';
        token->type = TOKEN_NUMBER;
        return 1;
    }
    return 0;
}

int matchFloatOrDouble(Token *token) {
    if (isdigit(src[pos])) {
        const int start = pos;
        while (isdigit(src[pos])) pos++;

        if (src[pos] == '.') {
            pos++;
            int digitsAfterDot = 0;
            while (isdigit(src[pos])) {
                pos++;
                digitsAfterDot++;
            }

            const int length = pos - start;
            strncpy(token->value, src + start, length);
            token->value[length] = '\0';

            if (digitsAfterDot > 7) {
                token->type = TOKEN_DOUBLE;
            } else {
                token->type = TOKEN_FLOAT;
            }

            return 1;
        }
    }
    return 0;
}

int matchBoolean(Token *token) {
    if (strncmp(src + pos, getKeywordStr(KEYWORD_TRUE), 3) == 0) {
        strncpy(token->value, getKeywordStr(KEYWORD_TRUE), 3);
        token->value[3] = '\0';
        token->type = TOKEN_BOOLEAN;
        pos += 3;
        return 1;
    }

    if (strncmp(src + pos, getKeywordStr(KEYWORD_FALSE), 2) == 0) {
        strncpy(token->value, getKeywordStr(KEYWORD_FALSE), 2);
        token->value[2] = '\0';
        token->type = TOKEN_BOOLEAN;
        pos += 2;
        return 1;
    }
    return 0;
}

int matchString(Token *token) {
    if (src[pos] == '"') {
        const int start = ++pos;
        while (src[pos] != '"' && src[pos] != '\0') pos++;
        const int length = pos - start;
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

int matchNumber(Token *token) {
    return matchInteger(token) || matchFloatOrDouble(token);
}

int matchOperator(Token *token) {
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        const int length = (int) strlen(operators[i].name);
        if (strncmp(src + pos, operators[i].name, length) == 0) {
            token->type = TOKEN_OPERATOR;
            strncpy(token->value, operators[i].name, length);
            token->value[length] = '\0';
            pos += length;
            return 1;
        }
    }
    return 0;
}


int handleSpecialCharacter(const char currentChar, Token *token, int *pos) {
    int length = 0;
    switch (currentChar) {
        case '{':
            token->type = TOKEN_LBRACE;
            token->value[0] = '{';
            length = (int) strlen(token->value);
            token->value[length] = '\0';
        break;
        case '}':
            token->type = TOKEN_RBRACE;
            token->value[0] = '}';
            length = (int) strlen(token->value);
            token->value[length] = '\0';
        break;
        case ';':
            token->type = TOKEN_SEMICOLON;
            token->value[0] = ';';
            length = (int) strlen(token->value);
            token->value[length] = '\0';
        break;
        default:
            printf("Lexer error: Unknown character '%c'\n", currentChar);
        return 0;
    }
    (*pos)++;
    return 1;
}

void skipComments() {
    while (src[pos] != '\0') {
        if (strncmp(src + pos, "spartan", 7) == 0) {
            pos += 7;
            while (src[pos] != '\n' && src[pos] != '\0') {
                pos++;
            }
        }
        else if (strncmp(src + pos, "athena", 6) == 0) {
            pos += 6;
            if (src[pos] == ' ' || src[pos] == '\n') {
                if (strncmp(src + pos, "begin", 5) == 0) {
                    pos += 5;
                    while (src[pos] != '\0') {
                        if (strncmp(src + pos, "end", 3) == 0) {
                            pos += 3;
                            break;
                        }
                        pos++;
                    }
                    if (src[pos] == '\0') {
                        printf("You fool: Missing 'end' after 'begin' in athena block.\n");
                        exit(1);
                    }
                } else {
                    printf("You fool: Missing 'begin' after 'athena'.\n");
                    exit(1);
                }
            }
        }
        else {
            break;
        }
    }
}


const char* getOperator(const OperatorType type) {
    if (type >= OPERATOR_COUNT) {
        return "Unknown operator";
    }
    return operators[type].name;
}

const char *getKeywordStr(const Keyword key) {
    return keywordStrings[key];
}