#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "../include/utils.h"

typedef struct ClienteNode {
    Cliente value;
    struct ClienteNode *next;
} ClienteNode;

static ClienteNode *clientesHead = NULL;
static int proximoClienteId = 1;

static void inserir_cliente(ClienteNode *novo) {
    if (!clientesHead) {
        clientesHead = novo;
        return;
    }

    ClienteNode *ponteiro = clientesHead;
    while (ponteiro->next) {
        ponteiro = ponteiro->next;
    }
    ponteiro->next = novo;
}

static ClienteNode *cliente_buscar_node(int id) {
    ClienteNode *atual = clientesHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void clientes_inicializar(void) {
    clientesHead = NULL;
    proximoClienteId = 1;
}

void clientes_finalizar(void) {
    ClienteNode *atual = clientesHead;
    while (atual) {
        ClienteNode *temp = atual->next;
        free(atual);
        atual = temp;
    }
    clientesHead = NULL;
}

int clientes_vazios(void) {
    return clientesHead == NULL;
}

const Cliente *clientes_buscar_por_id(int id) {
    ClienteNode *node = cliente_buscar_node(id);
    return node ? &node->value : NULL;
}

void cadastrar_cliente(void) {
    Cliente cliente = {0};
    cliente.id = proximoClienteId++;

    ler_texto("Nome do cliente: ", cliente.nome, sizeof(cliente.nome));
    ler_texto("Telefone: ", cliente.telefone, sizeof(cliente.telefone));
    ler_texto("Endereco: ", cliente.endereco.rua, sizeof(cliente.endereco.rua));
    ler_texto("Cidade: ", cliente.endereco.cidade, sizeof(cliente.endereco.cidade));
    ler_texto("Estado (UF): ", cliente.endereco.estado, sizeof(cliente.endereco.estado));
    ler_texto("CEP: ", cliente.endereco.cep, sizeof(cliente.endereco.cep));

    ClienteNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para cliente.\n");
        return;
    }

    novo->value = cliente;
    novo->next = NULL;

    inserir_cliente(novo);

    printf("Cliente cadastrado com ID %d.\n", cliente.id);
}

void listar_clientes(void) {
    printf("\n=== Clientes ===\n");
    if (!clientesHead) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    ClienteNode *ponteiro = clientesHead;
    while (ponteiro) {
        printf("ID: %d | Nome: %s | Telefone: %s | Cidade: %s | Estado: %s | CEP: %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.telefone,
               ponteiro->value.endereco.cidade,
               ponteiro->value.endereco.estado,
               ponteiro->value.endereco.cep);
        ponteiro = ponteiro->next;
    }
}

