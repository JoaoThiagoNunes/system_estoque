#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

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
        imprimir_erro("Quantidade invalida para entrada.");
        return;
    }

    Produto *produto = produtos_buscar_por_id(produtoId);
    if (!produto) {
        imprimir_erro("Produto %d nao encontrado. Cadastre o produto primeiro.", produtoId);
        return;
    }

    printf("\n=== Dados da Entrada ===\n");
    char numeroNotaFiscal[30];
    ler_texto("Numero da nota fiscal: ", numeroNotaFiscal, sizeof(numeroNotaFiscal));
    
    printf("ID do funcionario responsavel: ");
    int funcionarioId;
    if (scanf("%d", &funcionarioId) != 1) {
        funcionarioId = 0;
        limpar_buffer();
    } else {
        limpar_buffer();
    }
    
    char observacoes[200];
    ler_texto("Observacoes: ", observacoes, sizeof(observacoes));

    produto->quantidade += quantidade;

    float valorTotal = quantidade * produto->precoCompra;

    EntradaEstoque entrada = {
        .id = proximaEntradaId++,
        .produtoId = produtoId,
        .quantidade = quantidade,
        .data = time(NULL),
        .fornecedorId = produto->fornecedorId,
        .valorTotal = valorTotal,
        .funcionarioId = funcionarioId
    };
    strncpy(entrada.numeroNotaFiscal, numeroNotaFiscal, sizeof(entrada.numeroNotaFiscal) - 1);
    entrada.numeroNotaFiscal[sizeof(entrada.numeroNotaFiscal) - 1] = '\0';
    strncpy(entrada.observacoes, observacoes, sizeof(entrada.observacoes) - 1);
    entrada.observacoes[sizeof(entrada.observacoes) - 1] = '\0';

    EntradaEstoqueNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para entrada de estoque.\n");
        return;
    }

    novo->value = entrada;
    novo->next = NULL;
    inserir_entrada(novo);

    int estoque_anterior = produto->quantidade - quantidade;
    
    printf("\n");
    desenhar_box_titulo("ENTRADA REGISTRADA COM SUCESSO", 60);
    imprimir_sucesso("Entrada de estoque registrada!");
    printf("\n");
    printf("Produto: %s\n", produto->nome);
    printf("Quantidade adicionada: %d %s\n", quantidade, produto->unidadeMedida);
    printf("Estoque anterior: %d %s\n", estoque_anterior, produto->unidadeMedida);
    printf("Estoque atual: %d %s\n", produto->quantidade, produto->unidadeMedida);
    printf("Valor total: R$ %.2f\n", valorTotal);
    if (strlen(numeroNotaFiscal) > 0) {
        printf("Nota Fiscal: %s\n", numeroNotaFiscal);
    }
    desenhar_box_fim(60);
    pausar_para_continuar();
}

void registrar_saida(int produtoId, int quantidade) {
    if (quantidade <= 0) {
        imprimir_erro("Quantidade invalida para saida.");
        return;
    }

    Produto *produto = produtos_buscar_por_id(produtoId);
    if (!produto) {
        imprimir_erro("Produto %d nao encontrado.", produtoId);
        return;
    }

    if (quantidade > produto->quantidade) {
        imprimir_erro("Saida nao registrada: quantidade solicitada excede o estoque.");
        return;
    }

    printf("\n=== Dados da Saida ===\n");
    printf("ID do funcionario responsavel: ");
    int funcionarioId;
    if (scanf("%d", &funcionarioId) != 1) {
        funcionarioId = 0;
        limpar_buffer();
    } else {
        limpar_buffer();
    }
    
    printf("Tipo de saida (0=Perda, 1=Avaria, 2=Vencimento, 3=Outro): ");
    int tipoSaida;
    if (scanf("%d", &tipoSaida) != 1) {
        tipoSaida = 3;
        limpar_buffer();
    } else {
        limpar_buffer();
    }
    
    char observacoes[200];
    ler_texto("Observacoes: ", observacoes, sizeof(observacoes));

    produto->quantidade -= quantidade;

    float valorTotal = quantidade * produto->precoCompra;

    SaidaEstoque saida = {
        .id = proximaSaidaId++,
        .produtoId = produtoId,
        .quantidade = quantidade,
        .data = time(NULL),
        .funcionarioId = funcionarioId,
        .valorTotal = valorTotal,
        .tipoSaida = tipoSaida
    };
    strncpy(saida.observacoes, observacoes, sizeof(saida.observacoes) - 1);
    saida.observacoes[sizeof(saida.observacoes) - 1] = '\0';

    SaidaEstoqueNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para saida de estoque.\n");
        return;
    }

    novo->value = saida;
    novo->next = NULL;
    inserir_saida(novo);

    int estoque_anterior = produto->quantidade + quantidade;
    const char *tipo_saida_str;
    switch (tipoSaida) {
        case 0: tipo_saida_str = "Perda"; break;
        case 1: tipo_saida_str = "Avaria"; break;
        case 2: tipo_saida_str = "Vencimento"; break;
        case 3: tipo_saida_str = "Outro"; break;
        default: tipo_saida_str = "Desconhecido"; break;
    }
    
    printf("\n");
    desenhar_box_titulo("SAIDA REGISTRADA COM SUCESSO", 60);
    imprimir_sucesso("Saida de estoque registrada!");
    printf("\n");
    printf("Produto: %s\n", produto->nome);
    printf("Quantidade removida: %d %s\n", quantidade, produto->unidadeMedida);
    printf("Tipo de saida: %s\n", tipo_saida_str);
    printf("Estoque anterior: %d %s\n", estoque_anterior, produto->unidadeMedida);
    printf("Estoque atual: %d %s\n", produto->quantidade, produto->unidadeMedida);
    printf("Valor total: R$ %.2f\n", valorTotal);
    desenhar_box_fim(60);
    pausar_para_continuar();
}

float calcular_valor_investido_por_entradas(void) {
    float valor_investido = 0;
    
    EntradaEstoqueNode *atual = entradasHead;
    while (atual) {
        Produto *produto = produtos_buscar_por_id(atual->value.produtoId);
        if (produto) {
            valor_investido += atual->value.quantidade * produto->precoCompra;
        }
        atual = atual->next;
    }
    
    return valor_investido;
}

float calcular_custo_total_saidas(void) {
    float custo_total = 0;
    
    SaidaEstoqueNode *atual = saidasHead;
    while (atual) {
        Produto *produto = produtos_buscar_por_id(atual->value.produtoId);
        if (produto) {
            custo_total += atual->value.quantidade * produto->precoCompra;
        }
        atual = atual->next;
    }
    
    return custo_total;
}

