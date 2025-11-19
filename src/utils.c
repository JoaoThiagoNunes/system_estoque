#include <stdio.h>
#include <string.h>
#include "../include/utils.h"

void limpar_buffer(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

void ler_texto(const char *msg, char *buffer, size_t tamanho) {
    if (!buffer || tamanho == 0) return;
    printf("%s", msg ? msg : "");
    if (fgets(buffer, tamanho, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    } else {
        limpar_buffer();
    }
}
