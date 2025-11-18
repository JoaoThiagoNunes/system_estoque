#include <stdio.h>
#include <stdlib.h>
#include "../include/system.h"
#include "../include/utils.h"

typedef struct FornecedorNode {
    Fornecedor value;
    struct FornecedorNode *next;
} FornecedorNode;

static FornecedorNode *fornecedoresHead = NULL;
static int proximoFornecedorId = 1;

static void inserir_fornecedor(FornecedorNode *novo) {
    if (!fornecedoresHead) {
        fornecedoresHead = novo;
        return;
    }

    FornecedorNode *ponteiro = fornecedoresHead;
    while (ponteiro->next) {
        ponteiro = ponteiro->next;
    }
    ponteiro->next = novo;
}

static FornecedorNode *fornecedor_buscar_node(int id) {
    FornecedorNode *atual = fornecedoresHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void fornecedores_inicializar(void) {
    fornecedoresHead = NULL;
    proximoFornecedorId = 1;
}

void fornecedores_finalizar(void) {
    FornecedorNode *atual = fornecedoresHead;
    while (atual) {
        FornecedorNode *temp = atual->next;
        free(atual);
        atual = temp;
    }
    fornecedoresHead = NULL;
}

int fornecedores_vazios(void) {
    return fornecedoresHead == NULL;
}

const Fornecedor *fornecedores_buscar_por_id(int id) {
    FornecedorNode *node = fornecedor_buscar_node(id);
    return node ? &node->value : NULL;
}

void cadastrar_fornecedor(void) {
    Fornecedor fornecedor = {0};
    fornecedor.id = proximoFornecedorId++;

    ler_texto("Nome do fornecedor: ", fornecedor.nome, sizeof(fornecedor.nome));
    ler_texto("Telefone: ", fornecedor.telefone, sizeof(fornecedor.telefone));
    ler_texto("Endereco: ", fornecedor.endereco.rua, sizeof(fornecedor.endereco.rua));
    ler_texto("Cidade: ", fornecedor.endereco.cidade, sizeof(fornecedor.endereco.cidade));
    ler_texto("Estado (UF): ", fornecedor.endereco.estado, sizeof(fornecedor.endereco.estado));
    ler_texto("CEP: ", fornecedor.endereco.cep, sizeof(fornecedor.endereco.cep));

    FornecedorNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para fornecedor.\n");
        return;
    }

    novo->value = fornecedor;
    novo->next = NULL;

    inserir_fornecedor(novo);

    printf("Fornecedor cadastrado com ID %d.\n", fornecedor.id);
}

void listar_fornecedores(void) {
    printf("\n=== Fornecedores ===\n");
    if (!fornecedoresHead) {
        printf("Nenhum fornecedor cadastrado.\n");
        return;
    }

    FornecedorNode *ponteiro = fornecedoresHead;
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

