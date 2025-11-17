#include <stdlib.h>

#include "../include/system.h"

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

