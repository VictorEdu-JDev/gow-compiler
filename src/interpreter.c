#include "../interfaces/interpreter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VARIABLES 100

typedef struct {
    char name[50];
    int value;
} Variable;

Variable variables[MAX_VARIABLES];
int varCount = 0;

void addVariable(const char *name, int value) {
    if (varCount >= MAX_VARIABLES) {
        printf("Runtime error: Too many variables.\n");
        exit(1);
    }
    strcpy(variables[varCount].name, name);
    variables[varCount].value = value;
    varCount++;
}

void printVariable(const char *name) {
    for (int i = 0; i < varCount; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            printf("%d\n", variables[i].value);
            return;
        }
    }
    printf("Runtime error: Undefined variable '%s'.\n", name);
    exit(1);
}
