#include <stdio.h>
#include <stdlib.h>

#include "../include/system.h"
#include "../include/utils.h"

typedef struct FuncionarioNode {
    Funcionario value;
    struct FuncionarioNode *next;
} FuncionarioNode;

static FuncionarioNode *funcionariosHead = NULL;
static int proximoFuncionarioId = 1;

static void inserir_funcionario(FuncionarioNode *novo) {
    if (!funcionariosHead) {
        funcionariosHead = novo;
        return;
    }

    FuncionarioNode *ponteiro = funcionariosHead;
    while (ponteiro->next) {
        ponteiro = ponteiro->next;
    }
    ponteiro->next = novo;
}

static FuncionarioNode *funcionario_buscar_node(int id) {
    FuncionarioNode *atual = funcionariosHead;
    while (atual) {
        if (atual->value.id == id) {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

void funcionarios_inicializar(void) {
    funcionariosHead = NULL;
    proximoFuncionarioId = 1;
}

void funcionarios_finalizar(void) {
    FuncionarioNode *atual = funcionariosHead;
    while (atual) {
        FuncionarioNode *temp = atual->next;
        free(atual);
        atual = temp;
    }
    funcionariosHead = NULL;
}

const Funcionario *funcionarios_buscar_por_id(int id) {
    FuncionarioNode *node = funcionario_buscar_node(id);
    return node ? &node->value : NULL;
}

void cadastrar_funcionario(void) {
    Funcionario funcionario = {0};
    funcionario.id = proximoFuncionarioId++;

    ler_texto("Nome do funcionário: ", funcionario.nome, sizeof(funcionario.nome));
    ler_texto("Cargo: ", funcionario.cargo, sizeof(funcionario.cargo));
    ler_texto("Login: ", funcionario.login, sizeof(funcionario.login));
    ler_texto("Senha: ", funcionario.senha, sizeof(funcionario.senha));

    FuncionarioNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para funcionário.\n");
        return;
    }

    novo->value = funcionario;
    novo->next = NULL;

    inserir_funcionario(novo);

    printf("Funcionário cadastrado com ID %d.\n", funcionario.id);
}

void listar_funcionarios(void) {
    printf("\n=== Funcionários ===\n");
    if (!funcionariosHead) {
        printf("Nenhum funcionário cadastrado.\n");
        return;
    }

    FuncionarioNode *ponteiro = funcionariosHead;
    while (ponteiro) {
        printf("ID: %d | Nome: %s | Cargo: %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.cargo);
        ponteiro = ponteiro->next;
    }
}

