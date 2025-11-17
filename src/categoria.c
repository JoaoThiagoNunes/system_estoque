#include <stdio.h>
#include <stdlib.h>

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

    ler_texto("Nome da categoria: ", categoria.nome, sizeof(categoria.nome));
    ler_texto("Descrição: ", categoria.descricao, sizeof(categoria.descricao));

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
        printf("ID: %d | Nome: %s | Descrição: %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.descricao);
        ponteiro = ponteiro->next;
    }
}

