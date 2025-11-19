#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

typedef struct CategoriaNode {
    Categoria value;
    struct CategoriaNode *next;
} CategoriaNode;

static CategoriaNode *categoriasHead = NULL;
static int proximaCategoriaId = 1;

static void inserir_categoria(CategoriaNode *novo) {
    if (!categoriasHead) {
        categoriasHead = novo;
        return;
    }

    CategoriaNode *ponteiro = categoriasHead;
    while (ponteiro->next) {
        ponteiro = ponteiro->next;
    }
    ponteiro->next = novo;
}

static CategoriaNode *categoria_buscar_node(int id) {
    CategoriaNode *atual = categoriasHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void categorias_inicializar(void) {
    categoriasHead = NULL;
    proximaCategoriaId = 1;
}

void categorias_finalizar(void) {
    CategoriaNode *atual = categoriasHead;
    while (atual) {
        CategoriaNode *temp = atual->next;
        free(atual);
        atual = temp;
    }
    categoriasHead = NULL;
}

int categorias_vazias(void) {
    return categoriasHead == NULL;
}

const Categoria *categorias_buscar_por_id(int id) {
    CategoriaNode *node = categoria_buscar_node(id);
    return node ? &node->value : NULL;
}

void cadastrar_categoria(void) {
    Categoria categoria = {0};
    categoria.id = proximaCategoriaId++;
    categoria.dataCriacao = time(NULL);
    categoria.dataAtualizacao = time(NULL);
    categoria.ativo = 1;

    ler_texto("Nome da categoria: ", categoria.nome, sizeof(categoria.nome));
    ler_texto("Descricao: ", categoria.descricao, sizeof(categoria.descricao));
    ler_texto("Codigo: ", categoria.codigo, sizeof(categoria.codigo));
    ler_texto("Tags (separadas por virgula): ", categoria.tags, sizeof(categoria.tags));
    printf("Ativo (0=Inativo, 1=Ativo) [padrao: 1]: ");
    if (scanf("%d", &categoria.ativo) != 1) categoria.ativo = 1;
    limpar_buffer();

    CategoriaNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para categoria.\n");
        return;
    }

    novo->value = categoria;
    novo->next = NULL;

    inserir_categoria(novo);

    printf("\n");
    desenhar_box_titulo("CADASTRO REALIZADO COM SUCESSO", 50);
    imprimir_sucesso("Categoria cadastrada!");
    printf("\nID: %d\n", categoria.id);
    printf("Nome: %s\n", categoria.nome);
    printf("Codigo: %s\n", categoria.codigo);
    printf("Status: %s\n", categoria.ativo ? ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET);
    if (strlen(categoria.tags) > 0) printf("Tags: %s\n", categoria.tags);
    desenhar_box_fim(50);
    pausar_para_continuar();
}

void listar_categorias(void) {
    limpar_tela();
    imprimir_titulo("CATEGORIAS");
    if (!categoriasHead) {
        imprimir_info("Nenhuma categoria cadastrada.");
        printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
        limpar_buffer();
        getchar();
        return;
    }
    desenhar_box_titulo("LISTA DE CATEGORIAS", 80);
    printf(ANSI_BOLD "%-4s | %-10s | %-25s | %-8s | %-30s\n" ANSI_RESET,
           "ID", "Codigo", "Nome", "Status", "Tags");
    desenhar_separador(78);
    CategoriaNode *ponteiro = categoriasHead;
    while (ponteiro) {
        const char *status = ponteiro->value.ativo ?
            ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET;
        printf("%-4d | %-10s | %-25s | %s | %-30s\n",
               ponteiro->value.id,
               ponteiro->value.codigo,
               ponteiro->value.nome,
               status,
               ponteiro->value.tags);
        ponteiro = ponteiro->next;
    }
    desenhar_box_fim(80);
    printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
    limpar_buffer();
    getchar();
}