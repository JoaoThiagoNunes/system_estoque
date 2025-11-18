#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "../include/utils.h"

typedef struct ProdutoNode {
    Produto value;
    struct ProdutoNode *next;
} ProdutoNode;

static ProdutoNode *produtosHead = NULL;
static int proximoProdutoId = 1;

static void inserir_produto(ProdutoNode *novo) {
    if (!produtosHead) {
        produtosHead = novo;
        return;
    }

    ProdutoNode *ponteiro = produtosHead;
    while (ponteiro->next) {
        ponteiro = ponteiro->next;
    }
    ponteiro->next = novo;
}

static ProdutoNode *produto_buscar_node(int id) {
    ProdutoNode *atual = produtosHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void produtos_inicializar(void) {
    produtosHead = NULL;
    proximoProdutoId = 1;
}

void produtos_finalizar(void) {
    ProdutoNode *atual = produtosHead;
    while (atual) {
        ProdutoNode *temp = atual->next;
        free(atual);
        atual = temp;
    }
    produtosHead = NULL;
}

int produtos_vazios(void) {
    return produtosHead == NULL;
}

Produto *produtos_buscar_por_id(int id) {
    ProdutoNode *node = produto_buscar_node(id);
    return node ? &node->value : NULL;
}

void cadastrar_produto(void) {
    if (categorias_vazias()) {
        printf("Nenhuma categoria cadastrada. Cadastre uma categoria primeiro.\n");
        return;
    }

    if (fornecedores_vazios()) {
        printf("Nenhum fornecedor cadastrado. Cadastre um fornecedor primeiro.\n");
        return;
    }

    Produto produto = {0};
    produto.id = proximoProdutoId++;

    ler_texto("Nome do produto: ", produto.nome, sizeof(produto.nome));

    printf("ID da categoria: ");
    if (scanf("%d", &produto.categoriaId) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (!categorias_buscar_por_id(produto.categoriaId)) {
        printf("Categoria %d nao encontrada.\n", produto.categoriaId);
        return;
    }

    printf("ID do fornecedor: ");
    if (scanf("%d", &produto.fornecedorId) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (!fornecedores_buscar_por_id(produto.fornecedorId)) {
        printf("Fornecedor %d nao encontrado.\n", produto.fornecedorId);
        return;
    }

    printf("Preco de compra: ");
    if (scanf("%f", &produto.precoCompra) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("Preco de venda: ");
    if (scanf("%f", &produto.precoVenda) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("Quantidade inicial em estoque: ");
    if (scanf("%d", &produto.quantidade) != 1) {
        printf("Entrada invalida. Produto nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    ProdutoNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para produto.\n");
        return;
    }

    novo->value = produto;
    novo->next = NULL;

    inserir_produto(novo);

    printf("Produto cadastrado com ID %d.\n", produto.id);
}

void listar_produtos(void) {
    printf("\n=== Produtos ===\n");
    if (!produtosHead) {
        printf("Nenhum produto cadastrado.\n");
        return;
    }

    ProdutoNode *ponteiro = produtosHead;
    while (ponteiro) {
        const Categoria *categoria = categorias_buscar_por_id(ponteiro->value.categoriaId);
        const Fornecedor *fornecedor = fornecedores_buscar_por_id(ponteiro->value.fornecedorId);
        printf("ID: %d | Nome: %s | Estoque: %d | Preco venda: %.2f | Categoria: %s | Fornecedor: %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.quantidade,
               ponteiro->value.precoVenda,
               categoria ? categoria->nome : "N/D",
               fornecedor ? fornecedor->nome : "N/D");
        ponteiro = ponteiro->next;
    }
}

float calcular_valor_investido(void) {
    float valor_investido = 0;
    ProdutoNode *atual = produtosHead;
    while (atual) {
        valor_investido += atual->value.precoCompra * atual->value.quantidade;
        atual = atual->next;
    }
    return valor_investido;
}