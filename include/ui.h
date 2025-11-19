#ifndef UI_H
#define UI_H

#define ANSI_RESET   "\033[0m"
#define ANSI_BOLD    "\033[1m"
#define ANSI_DIM     "\033[2m"
#define ANSI_BLACK   "\033[30m"
#define ANSI_RED     "\033[31m"
#define ANSI_GREEN   "\033[32m"
#define ANSI_YELLOW  "\033[33m"
#define ANSI_BLUE    "\033[34m"
#define ANSI_MAGENTA "\033[35m"
#define ANSI_CYAN    "\033[36m"
#define ANSI_WHITE   "\033[37m"
#define ANSI_BG_BLACK   "\033[40m"
#define ANSI_BG_RED     "\033[41m"
#define ANSI_BG_GREEN   "\033[42m"
#define ANSI_BG_YELLOW  "\033[43m"
#define ANSI_BG_BLUE    "\033[44m"
#define ANSI_BG_MAGENTA "\033[45m"
#define ANSI_BG_CYAN    "\033[46m"
#define ANSI_BG_WHITE   "\033[47m"

void limpar_tela(void);
void desenhar_separador(int largura);
void centralizar_texto(const char *texto, int largura);
void imprimir_titulo(const char *titulo);
void imprimir_menu_item(int numero, const char *descricao);
void imprimir_sucesso(const char *mensagem, ...);
void imprimir_erro(const char *mensagem, ...);
void imprimir_info(const char *mensagem, ...);
void desenhar_box_titulo(const char *titulo, int largura);
void desenhar_box_fim(int largura);
void pausar_para_continuar(void);
void pausar_para_continuar_custom(const char *mensagem);

#endif
