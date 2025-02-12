#include "interfaces/lexer.h"
#include "interfaces/parser.h"
#include <stdio.h>
#include <stdlib.h>

char *readFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open file '%s'\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    fread(buffer, 1, length, file);
    fclose(file);

    buffer[length] = '\0';
    return buffer;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file.gow>\n", argv[0]);
        return 1;
    }

    char *source = readFile(argv[1]);
    initLexer(source);
    parse();
    free(source);
    return 0;
}
