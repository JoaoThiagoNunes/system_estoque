#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"

typedef struct PedidoCompraNode {
    PedidoCompra value;
    struct PedidoCompraNode *next;
} PedidoCompraNode;

static PedidoCompraNode *pedidosHead = NULL;
static int proximoPedidoId = 1;

static PedidoCompraNode *pedido_buscar_node(int id) {
    PedidoCompraNode *atual = pedidosHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void pedidos_inicializar(void) {
    pedidosHead = NULL;
    proximoPedidoId = 1;
}

void pedidos_finalizar(void) {
    PedidoCompraNode *atual = pedidosHead;
    while (atual) {
        PedidoCompraNode *tmp = atual->next;
        free(atual);
        atual = tmp;
    }
    pedidosHead = NULL;
}

PedidoCompra *pedidos_buscar_por_id(int id) {
    PedidoCompraNode *node = pedido_buscar_node(id);
    return node ? &node->value : NULL;
}

int pedidos_proximo_id(void) {
    return proximoPedidoId++;
}

static void inserir_pedido(PedidoCompraNode *novo) {
    novo->next = pedidosHead;
    pedidosHead = novo;
}

void cadastrar_pedido(void) {
    if (fornecedores_vazios()) {
        printf("Nenhum fornecedor cadastrado. Cadastre um fornecedor primeiro.\n");
        return;
    }

    if (produtos_vazios()) {
        printf("Nenhum produto cadastrado. Cadastre um produto primeiro.\n");
        return;
    }

    PedidoCompra pedido = {0};
    pedido.id = proximoPedidoId++;
    pedido.dataPedido = time(NULL);
    pedido.status = 0; // 0=Pendente

    printf("ID do fornecedor: ");
    if (scanf("%d", &pedido.fornecedorId) != 1) {
        printf("Entrada invalida. Pedido nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (!fornecedores_buscar_por_id(pedido.fornecedorId)) {
        printf("Fornecedor %d nao encontrado.\n", pedido.fornecedorId);
        return;
    }

    printf("ID do produto: ");
    if (scanf("%d", &pedido.produtoId) != 1) {
        printf("Entrada invalida. Pedido nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();
    if (!produtos_buscar_por_id(pedido.produtoId)) {
        printf("Produto %d nao encontrado.\n", pedido.produtoId);
        return;
    }

    printf("Quantidade: ");
    if (scanf("%d", &pedido.quantidade) != 1) {
        printf("Entrada invalida. Pedido nao cadastrado.\n");
        limpar_buffer();
        return;
    }
    limpar_buffer();

    printf("Preco unitario: ");
    if (scanf("%f", &pedido.precoUnitario) != 1) {
        Produto *produto = produtos_buscar_por_id(pedido.produtoId);
        pedido.precoUnitario = produto ? produto->precoCompra : 0.0f;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

    pedido.valorTotal = pedido.quantidade * pedido.precoUnitario;

    printf("Data de entrega prevista (timestamp, 0 para hoje): ");
    time_t dataEntrega;
    if (scanf("%ld", &dataEntrega) != 1 || dataEntrega == 0) {
        dataEntrega = time(NULL);
        limpar_buffer();
    } else {
        limpar_buffer();
    }
    pedido.dataEntregaPrevista = dataEntrega;

    printf("Status (0=Pendente, 1=Aprovado, 2=Recebido, 3=Cancelado): ");
    if (scanf("%d", &pedido.status) != 1) {
        pedido.status = 0;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

    ler_texto("Observacoes: ", pedido.observacoes, sizeof(pedido.observacoes));

    PedidoCompraNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para pedido.\n");
        return;
    }

    novo->value = pedido;
    novo->next = NULL;
    inserir_pedido(novo);

    printf("Pedido cadastrado com ID %d. Valor total: R$ %.2f\n", pedido.id, pedido.valorTotal);
}

