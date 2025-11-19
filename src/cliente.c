#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    cliente.dataCadastro = time(NULL);
    cliente.ativo = 1;

    ler_texto("Nome do cliente: ", cliente.nome, sizeof(cliente.nome));
    ler_texto("Telefone: ", cliente.telefone, sizeof(cliente.telefone));
    ler_texto("Email: ", cliente.email, sizeof(cliente.email));
    ler_texto("CPF: ", cliente.cpf, sizeof(cliente.cpf));
    ler_texto("Data de nascimento (DD/MM/AAAA): ", cliente.dataNascimento, sizeof(cliente.dataNascimento));
    printf("Ativo (0=Inativo, 1=Ativo) [padrao: 1]: ");
    if (scanf("%d", &cliente.ativo) != 1) {
        cliente.ativo = 1;
        limpar_buffer();
    } else {
        limpar_buffer();
    }
    ler_texto("Endereco (rua): ", cliente.endereco.rua, sizeof(cliente.endereco.rua));
    ler_texto("Numero: ", cliente.endereco.numero, sizeof(cliente.endereco.numero));
    ler_texto("Complemento: ", cliente.endereco.complemento, sizeof(cliente.endereco.complemento));
    ler_texto("Bairro: ", cliente.endereco.bairro, sizeof(cliente.endereco.bairro));
    ler_texto("Cidade: ", cliente.endereco.cidade, sizeof(cliente.endereco.cidade));
    ler_texto("Estado (UF): ", cliente.endereco.estado, sizeof(cliente.endereco.estado));
    ler_texto("CEP: ", cliente.endereco.cep, sizeof(cliente.endereco.cep));
    ler_texto("Pais: ", cliente.endereco.pais, sizeof(cliente.endereco.pais));
    ler_texto("Ponto de referencia: ", cliente.endereco.pontoReferencia, sizeof(cliente.endereco.pontoReferencia));
    printf("Tipo de endereco (0=Residencial, 1=Comercial, 2=Outro): ");
    if (scanf("%d", &cliente.endereco.tipoEndereco) != 1) {
        cliente.endereco.tipoEndereco = 0;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

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
        const char *status = ponteiro->value.ativo ? "Ativo" : "Inativo";
        printf("ID: %d | Nome: %s | CPF: %s | Email: %s | %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.cpf,
               ponteiro->value.email,
               status);
        ponteiro = ponteiro->next;
    }
}

void listar_clientes_limitado(int limite) {
    printf("\n=== Clientes ===\n");
    if (!clientesHead) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    ClienteNode *ponteiro = clientesHead;
    int contador = 0;
    while (ponteiro && contador < limite) {
        const char *status = ponteiro->value.ativo ? "Ativo" : "Inativo";
        printf("ID: %d | Nome: %s | CPF: %s | Email: %s | %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.cpf,
               ponteiro->value.email,
               status);
        ponteiro = ponteiro->next;
        contador++;
    }
}

