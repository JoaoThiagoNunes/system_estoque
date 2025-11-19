#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

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
    fornecedor.dataCadastro = time(NULL);
    fornecedor.ativo = 1;

    ler_texto("Nome do fornecedor: ", fornecedor.nome, sizeof(fornecedor.nome));
    ler_texto("Telefone: ", fornecedor.telefone, sizeof(fornecedor.telefone));
    ler_texto("Email: ", fornecedor.email, sizeof(fornecedor.email));
    ler_texto("CNPJ: ", fornecedor.cnpj, sizeof(fornecedor.cnpj));
    printf("Ativo (0=Inativo, 1=Ativo) [padrao: 1]: ");
    if (scanf("%d", &fornecedor.ativo) != 1) {
        fornecedor.ativo = 1;
        limpar_buffer();
    } else {
        limpar_buffer();
    }
    ler_texto("Rua/Avenida: ", fornecedor.endereco.rua, sizeof(fornecedor.endereco.rua));
    ler_texto("Numero: ", fornecedor.endereco.numero, sizeof(fornecedor.endereco.numero));
    ler_texto("Complemento: ", fornecedor.endereco.complemento, sizeof(fornecedor.endereco.complemento));
    ler_texto("Bairro: ", fornecedor.endereco.bairro, sizeof(fornecedor.endereco.bairro));
    ler_texto("Cidade: ", fornecedor.endereco.cidade, sizeof(fornecedor.endereco.cidade));
    ler_texto("Estado (UF): ", fornecedor.endereco.estado, sizeof(fornecedor.endereco.estado));
    ler_texto("CEP: ", fornecedor.endereco.cep, sizeof(fornecedor.endereco.cep));
    ler_texto("Pais: ", fornecedor.endereco.pais, sizeof(fornecedor.endereco.pais));
    ler_texto("Ponto de referencia: ", fornecedor.endereco.pontoReferencia, sizeof(fornecedor.endereco.pontoReferencia));
    printf("Tipo de endereco (0=Residencial, 1=Comercial, 2=Outro): ");
    if (scanf("%d", &fornecedor.endereco.tipoEndereco) != 1) {
        fornecedor.endereco.tipoEndereco = 1;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

    FornecedorNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memória para fornecedor.\n");
        return;
    }

    novo->value = fornecedor;
    novo->next = NULL;

    inserir_fornecedor(novo);

    printf("\n");
    desenhar_box_titulo("CADASTRO REALIZADO COM SUCESSO", 50);
    imprimir_sucesso("Fornecedor cadastrado!");
    printf("\n");
    printf("ID: %d\n", fornecedor.id);
    printf("Nome: %s\n", fornecedor.nome);
    printf("CNPJ: %s\n", fornecedor.cnpj);
    printf("Email: %s\n", fornecedor.email);
    printf("Telefone: %s\n", fornecedor.telefone);
    printf("Status: %s\n", fornecedor.ativo ? ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET);
    desenhar_box_fim(50);
    pausar_para_continuar();
}

void listar_fornecedores(void) {
    limpar_tela();
    imprimir_titulo("FORNECEDORES");
    
    if (!fornecedoresHead) {
        imprimir_info("Nenhum fornecedor cadastrado.");
        printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
        limpar_buffer();
        getchar();
        return;
    }

    desenhar_box_titulo("LISTA DE FORNECEDORES", 90);
    printf(ANSI_BOLD "%-4s | %-30s | %-18s | %-30s | %-8s\n" ANSI_RESET,
           "ID", "Nome", "CNPJ", "Email", "Status");
    desenhar_separador(88);
    
    FornecedorNode *ponteiro = fornecedoresHead;
    while (ponteiro) {
        const char *status = ponteiro->value.ativo ? 
            ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET;
        printf("%-4d | %-30s | %-18s | %-30s | %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.cnpj,
               ponteiro->value.email,
               status);
        ponteiro = ponteiro->next;
    }
    
    desenhar_box_fim(90);
    printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
    limpar_buffer();
    getchar();
}

void listar_fornecedores_limitado(int limite) {
    limpar_tela();
    imprimir_titulo("FORNECEDORES (PRIMEIROS 5)");
    
    if (!fornecedoresHead) {
        imprimir_info("Nenhum fornecedor cadastrado.");
        printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
        limpar_buffer();
        getchar();
        return;
    }

    desenhar_box_titulo("LISTA DE FORNECEDORES", 90);
    printf(ANSI_BOLD "%-4s | %-30s | %-18s | %-30s | %-8s\n" ANSI_RESET,
           "ID", "Nome", "CNPJ", "Email", "Status");
    desenhar_separador(88);
    
    FornecedorNode *ponteiro = fornecedoresHead;
    int contador = 0;
    while (ponteiro && contador < limite) {
        const char *status = ponteiro->value.ativo ? 
            ANSI_GREEN "Ativo" ANSI_RESET : ANSI_RED "Inativo" ANSI_RESET;
        printf("%-4d | %-30s | %-18s | %-30s | %s\n",
               ponteiro->value.id,
               ponteiro->value.nome,
               ponteiro->value.cnpj,
               ponteiro->value.email,
               status);
        ponteiro = ponteiro->next;
        contador++;
    }
    
    desenhar_box_fim(90);
    printf("\n" ANSI_YELLOW "Pressione Enter para continuar..." ANSI_RESET);
    limpar_buffer();
    getchar();
}

