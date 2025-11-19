#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"

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
    if (scanf("%d", &categoria.ativo) != 1) {
        categoria.ativo = 1;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

    CategoriaNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para categoria.\n");
        return;
    }

    novo->value = categoria;
    novo->next = NULL;

    inserir_categoria(novo);

    printf("Categoria cadastrada com ID %d.\n", categoria.id);
}

void listar_categorias(void) {
    printf("\n=== Categorias ===\n");
    if (!categoriasHead) {
        printf("Nenhuma categoria cadastrada.\n");
        return;
    }

    CategoriaNode *ponteiro = categoriasHead;
    while (ponteiro) {
        const char *status = ponteiro->value.ativo ? "Ativo" : "Inativo";
        printf("ID: %d | Codigo: %s | Nome: %s | %s | Tags: %s\n",
               ponteiro->value.id,
               ponteiro->value.codigo,
               ponteiro->value.nome,
               status,
               ponteiro->value.tags);
        ponteiro = ponteiro->next;
    }
}

