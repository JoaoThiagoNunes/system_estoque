#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"

typedef struct EntradaEstoqueNode {
    EntradaEstoque value;
    struct EntradaEstoqueNode *next;
} EntradaEstoqueNode;

typedef struct SaidaEstoqueNode {
    SaidaEstoque value;
    struct SaidaEstoqueNode *next;
} SaidaEstoqueNode;

static EntradaEstoqueNode *entradasHead = NULL;
static SaidaEstoqueNode *saidasHead = NULL;
static int proximaEntradaId = 1;
static int proximaSaidaId = 1;

static void inserir_entrada(EntradaEstoqueNode *novo) {
    novo->next = entradasHead;
    entradasHead = novo;
}

static void inserir_saida(SaidaEstoqueNode *novo) {
    novo->next = saidasHead;
    saidasHead = novo;
}

void estoque_inicializar(void) {
    entradasHead = NULL;
    saidasHead = NULL;
    proximaEntradaId = 1;
    proximaSaidaId = 1;
}

void estoque_finalizar(void) {
    EntradaEstoqueNode *entradaAtual = entradasHead;
    while (entradaAtual) {
        EntradaEstoqueNode *tmp = entradaAtual->next;
        free(entradaAtual);
        entradaAtual = tmp;
    }
    entradasHead = NULL;

    SaidaEstoqueNode *saidaAtual = saidasHead;
    while (saidaAtual) {
        SaidaEstoqueNode *tmp = saidaAtual->next;
        free(saidaAtual);
        saidaAtual = tmp;
    }
    saidasHead = NULL;
}

void registrar_entrada(int produtoId, int quantidade) {
    if (quantidade <= 0) {
        printf("Quantidade invalida para entrada.\n");
        return;
    }

    Produto *produto = produtos_buscar_por_id(produtoId);
    if (!produto) {
        printf("Produto %d nao encontrado. Cadastre o produto primeiro.\n", produtoId);
        return;
    }

    produto->quantidade += quantidade;

    EntradaEstoque entrada = {
        .id = proximaEntradaId++,
        .produtoId = produtoId,
        .quantidade = quantidade,
        .data = time(NULL),
        .fornecedorId = produto->fornecedorId
    };

    EntradaEstoqueNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para entrada de estoque.\n");
        return;
    }

    novo->value = entrada;
    novo->next = NULL;
    inserir_entrada(novo);

    printf("Entrada registrada: %d unidade(s) adicionadas ao produto %s. Estoque atual: %d\n",
           quantidade,
           produto->nome,
           produto->quantidade);
}

void registrar_saida(int produtoId, int quantidade, const char *motivo) {
    if (quantidade <= 0) {
        printf("Quantidade invalida para saida.\n");
        return;
    }

    Produto *produto = produtos_buscar_por_id(produtoId);
    if (!produto) {
        printf("Produto %d nao encontrado.\n", produtoId);
        return;
    }

    if (quantidade > produto->quantidade) {
        printf("Saida nao registrada: quantidade solicitada excede o estoque.\n");
        return;
    }

    produto->quantidade -= quantidade;

    SaidaEstoque saida = {
        .id = proximaSaidaId++,
        .produtoId = produtoId,
        .quantidade = quantidade,
        .data = time(NULL)
    };

    if (motivo) {
        strncpy(saida.motivo, motivo, sizeof(saida.motivo) - 1);
        saida.motivo[sizeof(saida.motivo) - 1] = '\0';
    } else {
        saida.motivo[0] = '\0';
    }

    SaidaEstoqueNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para saida de estoque.\n");
        return;
    }

    novo->value = saida;
    novo->next = NULL;
    inserir_saida(novo);

    printf("Saida registrada: %d unidade(s) removidas do produto %s. Estoque atual: %d\n",
           quantidade,
           produto->nome,
           produto->quantidade);
}

