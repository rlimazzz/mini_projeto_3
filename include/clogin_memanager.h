#include <stdio.h>
#include <stdlib.h>

#define MAX_FIELD 255
#define MAX_BUFFER 10000

typedef struct {
    void **variables;
    int size;
} Cleaner;

Cleaner CleanerFactory(int space) {
    Cleaner cleaner;

    cleaner.variables = (void**) malloc(sizeof(void*) * space);
    if (cleaner.variables == NULL) {
        printf("Memory alloc error (Cleaner Factory)\n");
        exit(EXIT_FAILURE);
    }

    cleaner.size = 0;
    return cleaner;
}

void Clean(Cleaner * cleaner) {
    for (int i = 0; i < cleaner->size; i++) {
        free(cleaner->variables[i]);
    }
    free(cleaner->variables);
}

void FileClean(Cleaner * cleaner, FILE * file) {
    Clean(cleaner);
    fclose(file);
}

void CharAlloc(char ** ptr, Cleaner * cleaner) {
    *ptr = (char*) malloc(MAX_FIELD * sizeof(char));

    if (*ptr == NULL) {
        printf("Memory alloc error (CharAlloc)\n");
        exit(EXIT_FAILURE);
    }

    cleaner->variables[cleaner->size] = *ptr;
    cleaner->size++;
}

void FileCharAlloc(char ** ptr, Cleaner * cleaner, FILE * file) {
    *ptr = (char*) malloc(MAX_FIELD * sizeof(char));

    if (*ptr == NULL) {
        printf("Memory alloc error (FileCharAlloc)\n");
        Clean(cleaner);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    cleaner->variables[cleaner->size] = *ptr;
    cleaner->size++;
}