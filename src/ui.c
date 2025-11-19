#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "../include/ui.h"
#include "../include/utils.h"

void limpar_tela(void) {
    printf("\033[2J\033[H");
}

void desenhar_separador(int largura) {
    printf(ANSI_DIM);
    for (int i = 0; i < largura; i++) {
        printf("─");
    }
    printf(ANSI_RESET "\n");
}

void centralizar_texto(const char *texto, int largura) {
    int len = (int)strlen(texto);
    int padding = (largura - len) / 2;
    if (padding < 0) padding = 0;
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", texto);
    for (int i = 0; i < (largura - len - padding); i++) printf(" ");
}

void imprimir_titulo(const char *titulo) {
    printf("\n" ANSI_BOLD ANSI_CYAN);
    printf("═══════════════════════════════════════════════════════\n");
    centralizar_texto(titulo, 55);
    printf("\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf(ANSI_RESET "\n");
}

void imprimir_menu_item(int numero, const char *descricao) {
    printf(ANSI_YELLOW "[%02d]" ANSI_RESET " %s\n", numero, descricao);
}

void imprimir_sucesso(const char *mensagem, ...) {
    va_list args;
    va_start(args, mensagem);
    printf(ANSI_GREEN "✓ " ANSI_RESET);
    vprintf(mensagem, args);
    printf("\n");
    va_end(args);
}

void imprimir_erro(const char *mensagem, ...) {
    va_list args;
    va_start(args, mensagem);
    printf(ANSI_RED "✗ Erro: " ANSI_RESET);
    vprintf(mensagem, args);
    printf("\n");
    va_end(args);
}

void imprimir_info(const char *mensagem, ...) {
    va_list args;
    va_start(args, mensagem);
    printf(ANSI_BLUE "ℹ " ANSI_RESET);
    vprintf(mensagem, args);
    printf("\n");
    va_end(args);
}

void desenhar_box_titulo(const char *titulo, int largura) {
    printf(ANSI_CYAN "┌");
    for (int i = 0; i < largura - 2; i++) printf("─");
    printf("┐\n│");
    centralizar_texto(titulo, largura - 2);
    printf("│\n├");
    for (int i = 0; i < largura - 2; i++) printf("─");
    printf("┤\n" ANSI_RESET);
}

void desenhar_box_fim(int largura) {
    printf(ANSI_CYAN "└");
    for (int i = 0; i < largura - 2; i++) printf("─");
    printf("┘\n" ANSI_RESET);
}

void pausar_para_continuar(void) {
    printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
    limpar_buffer();
    getchar();
}

void pausar_para_continuar_custom(const char *mensagem) {
    printf("\n" ANSI_YELLOW "%s" ANSI_RESET, mensagem);
    limpar_buffer();
    getchar();
}