#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/system.h"

typedef struct VendaNode {
    Venda value;
    struct VendaNode *next;
} VendaNode;

static VendaNode *vendasHead = NULL;
static int proximaVendaId = 1;

static void inserir_venda(VendaNode *novo) {
    novo->next = vendasHead;
    vendasHead = novo;
}

void vendas_inicializar(void) {
    vendasHead = NULL;
    proximaVendaId = 1;
}

void vendas_finalizar(void) {
    VendaNode *atual = vendasHead;
    while (atual) {
        VendaNode *tmp = atual->next;
        free(atual);
        atual = tmp;
    }
    vendasHead = NULL;
}

void registrar_venda(int produtoId, int clienteId, int funcionarioId, int quantidade) {
    if (quantidade <= 0) {
        printf("Quantidade inválida para venda.\n");
        return;
    }

    Produto *produto = produtos_buscar_por_id(produtoId);
    const Cliente *cliente = clientes_buscar_por_id(clienteId);
    const Funcionario *funcionario = funcionarios_buscar_por_id(funcionarioId);

    if (!produto) {
        printf("Produto %d não encontrado.\n", produtoId);
        return;
    }

    if (!cliente) {
        printf("Cliente %d não encontrado.\n", clienteId);
        return;
    }

    if (!funcionario) {
        printf("Funcionário %d não encontrado.\n", funcionarioId);
        return;
    }

    if (quantidade > produto->quantidade) {
        printf("Venda não registrada: estoque insuficiente.\n");
        return;
    }

    produto->quantidade -= quantidade;

    Venda venda = {
        .id = proximaVendaId++,
        .clienteId = clienteId,
        .funcionarioId = funcionarioId,
        .produtoId = produtoId,
        .quantidade = quantidade,
        .dataVenda = time(NULL),
        .total = quantidade * produto->precoVenda
    };

    VendaNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para venda.\n");
        return;
    }

    novo->value = venda;
    novo->next = NULL;
    inserir_venda(novo);

    printf("Venda registrada: %d unidade(s) de %s para %s. Total: R$ %.2f\n",
           quantidade,
           produto->nome,
           cliente->nome,
           venda.total);
}

