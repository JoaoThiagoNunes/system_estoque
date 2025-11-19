#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

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
    funcionario.dataAdmissao = time(NULL);
    funcionario.ativo = 1;

    ler_texto("Nome do funcionario: ", funcionario.nome, sizeof(funcionario.nome));
    ler_texto("Cargo: ", funcionario.cargo, sizeof(funcionario.cargo));
    ler_texto("Login: ", funcionario.login, sizeof(funcionario.login));
    ler_texto("Senha: ", funcionario.senha, sizeof(funcionario.senha));
    ler_texto("Email: ", funcionario.email, sizeof(funcionario.email));
    ler_texto("CPF: ", funcionario.cpf, sizeof(funcionario.cpf));
    ler_texto("Telefone: ", funcionario.telefone, sizeof(funcionario.telefone));
    printf("Ativo (0=Inativo, 1=Ativo) [padrao: 1]: ");
    if (scanf("%d", &funcionario.ativo) != 1) {
        funcionario.ativo = 1;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

    FuncionarioNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para funcionario.\n");
        return;
    }

    novo->value = funcionario;
    novo->next = NULL;

    inserir_funcionario(novo);

    printf("\n");
    desenhar_box_titulo("CADASTRO REALIZADO COM SUCESSO", 50);
    imprimir_sucesso("Funcionario cadastrado!");
    printf("\n");
    printf("ID: %d\n", funcionario.id);
    printf("Nome: %s\n", funcionario.nome);
    printf("Cargo: %s\n", funcionario.cargo);
    printf("Email: %s\n", funcionario.email);
    printf("Login: %s\n", funcionario.login);
    printf("Status: %s\n", funcionario.ativo ? ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET);
    desenhar_box_fim(50);
    pausar_para_continuar();
}

void listar_funcionarios(void) {
    limpar_tela();
    imprimir_titulo("FUNCIONARIOS");
    
    if (!funcionariosHead) {
        imprimir_info("Nenhum funcionario cadastrado.");
        printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
        limpar_buffer();
        getchar();
        return;
    }

    desenhar_box_titulo("LISTA DE FUNCIONARIOS", 90);
    printf(ANSI_BOLD "%-4s | %-30s | %-20s | %-30s | %-8s\n" ANSI_RESET,
           "ID", "Nome", "Cargo", "Email", "Status");
    desenhar_separador(88);
    
    FuncionarioNode *ponteiro = funcionariosHead;
    while (ponteiro) {
        const char *status = ponteiro->value.ativo ? 
            ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET;
        printf("%-4d | %-30s | %-20s | %-30s | %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.cargo,
               ponteiro->value.email,
               status);
        ponteiro = ponteiro->next;
    }
    
    desenhar_box_fim(90);
    printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
    limpar_buffer();
    getchar();
}

