#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../include/system.h"
#include "../include/utils.h"
#include "../include/ui.h"

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
        imprimir_erro("Quantidade invalida para venda.");
        return;
    }

    Produto *produto = produtos_buscar_por_id(produtoId);
    const Cliente *cliente = clientes_buscar_por_id(clienteId);
    const Funcionario *funcionario = funcionarios_buscar_por_id(funcionarioId);

    if (!produto) {
        imprimir_erro("Produto %d nao encontrado.", produtoId);
        return;
    }

    if (!cliente) {
        imprimir_erro("Cliente %d nao encontrado.", clienteId);
        return;
    }

    if (!funcionario) {
        imprimir_erro("Funcionario %d nao encontrado.", funcionarioId);
        return;
    }

    if (quantidade > produto->quantidade) {
        imprimir_erro("Venda nao registrada: estoque insuficiente.");
        return;
    }

    printf("\n=== Dados da Venda ===\n");
    printf("Desconto (R$): ");
    float desconto = 0.0f;
    if (scanf("%f", &desconto) != 1) {
        desconto = 0.0f;
        limpar_buffer();
    } else {
        limpar_buffer();
    }

    char formaPagamento[20];
    ler_texto("Forma de pagamento: ", formaPagamento, sizeof(formaPagamento));

    char observacoes[200];
    ler_texto("Observacoes: ", observacoes, sizeof(observacoes));

    produto->quantidade -= quantidade;

    float subtotal = quantidade * produto->precoVenda;
    float total = subtotal - desconto;
    if (total < 0) total = 0;

    Venda venda = {
        .id = proximaVendaId++,
        .clienteId = clienteId,
        .funcionarioId = funcionarioId,
        .produtoId = produtoId,
        .quantidade = quantidade,
        .dataVenda = time(NULL),
        .total = total,
        .desconto = desconto
    };
    strncpy(venda.formaPagamento, formaPagamento, sizeof(venda.formaPagamento) - 1);
    venda.formaPagamento[sizeof(venda.formaPagamento) - 1] = '\0';
    strncpy(venda.observacoes, observacoes, sizeof(venda.observacoes) - 1);
    venda.observacoes[sizeof(venda.observacoes) - 1] = '\0';

    VendaNode *novo = malloc(sizeof(*novo));
    if (!novo) {
        fprintf(stderr, "Falha ao alocar memoria para venda.\n");
        return;
    }

    novo->value = venda;
    novo->next = NULL;
    inserir_venda(novo);
    
    printf("\n");
    desenhar_box_titulo("VENDA REGISTRADA COM SUCESSO", 60);
    imprimir_sucesso("Venda concluida!");
    printf("\n");
    printf("Produto: %s\n", produto->nome);
    printf("Cliente: %s\n", cliente->nome);
    printf("Funcionario: %s\n", funcionario->nome);
    printf("Quantidade: %d %s\n", quantidade, produto->unidadeMedida);
    printf("Preco unitario: R$ %.2f\n", produto->precoVenda);
    printf("Subtotal: R$ %.2f\n", subtotal);
    if (desconto > 0) {
        printf("Desconto: R$ %.2f\n", desconto);
    }
    printf("Total: R$ %.2f\n", venda.total);
    printf("Forma de pagamento: %s\n", formaPagamento);
    desenhar_box_fim(60);
    pausar_para_continuar();
}

float calcular_valor_total_vendas(void) {
    float total = 0;
    VendaNode *atual = vendasHead;
    while (atual) {
        total += atual->value.total;
        atual = atual->next;
    }
    return total;
}

int calcular_quantidade_total_vendas(void) {
    int quantidade = 0;
    VendaNode *atual = vendasHead;
    while (atual) {
        quantidade += atual->value.quantidade;
        atual = atual->next;
    }
    return quantidade;
}

float calcular_custo_total_vendas(void) {
    float custo_total = 0;
    VendaNode *atual = vendasHead;
    while (atual) {
        Produto *produto = produtos_buscar_por_id(atual->value.produtoId);
        if (produto) {
            custo_total += atual->value.quantidade * produto->precoCompra;
        }
        atual = atual->next;
    }
    return custo_total;
}

void gerar_relatorio_vendas(void) {
    FILE *arquivo = fopen("relatorio_vendas.txt", "w");
    if (!arquivo) {
        fprintf(stderr, "Erro ao criar arquivo de relatorio.\n");
        return;
    }

    time_t agora = time(NULL);
    char *data_str = ctime(&agora);
    if (data_str) {
        data_str[strlen(data_str) - 1] = '\0';
    }

    fprintf(arquivo, "===================================\n    RELATORIO DE VENDAS\n");
    fprintf(arquivo, "Data: %s\n\n", data_str ? data_str : "N/A");

    float valor_investido = calcular_valor_investido();
    float total_vendas = calcular_valor_total_vendas();
    int quantidade_vendas = calcular_quantidade_total_vendas();
    float lucro = total_vendas - valor_investido;

    fprintf(arquivo, "RESUMO GERAL\n");
    fprintf(arquivo, "-----------\n");
    fprintf(arquivo, "Valor Investido: R$ %.2f\n", valor_investido);
    fprintf(arquivo, "Total de Vendas: R$ %.2f\n", total_vendas);
    fprintf(arquivo, "Quantidade de Vendas: %d unidades\n", quantidade_vendas);
    fprintf(arquivo, "Lucro: R$ %.2f\n\n", lucro);

    fprintf(arquivo, "DETALHES DAS VENDAS\n");
    fprintf(arquivo, "-------------------\n");
    
    if (!vendasHead) {
        fprintf(arquivo, "Nenhuma venda registrada.\n");
    } else {
        fprintf(arquivo, "%-4s | %-30s | %-30s | %-30s | %-10s | %-12s | %-12s | %-15s | %s\n",
                "ID", "Produto", "Cliente", "Funcionario", "Quantidade", "Desconto", "Total", "Pagamento", "Data");
        fprintf(arquivo, "-----|--------------------------------|--------------------------------|--------------------------------|------------|--------------|--------------|-----------------|-------------------\n");

        VendaNode *atual = vendasHead;
        while (atual) {
            const Venda *v = &atual->value;
            
            Produto *produto = produtos_buscar_por_id(v->produtoId);
            const Cliente *cliente = clientes_buscar_por_id(v->clienteId);
            const Funcionario *funcionario = funcionarios_buscar_por_id(v->funcionarioId);
            
            const char *nome_produto = produto ? produto->nome : "N/A";
            const char *nome_cliente = cliente ? cliente->nome : "N/A";
            const char *nome_funcionario = funcionario ? funcionario->nome : "N/A";
            
            char data_formatada[30];
            struct tm *info = localtime(&v->dataVenda);
            if (info) {
                strftime(data_formatada, sizeof(data_formatada), "%d/%m/%Y %H:%M:%S", info);
            } else {
                strcpy(data_formatada, "N/A");
            }
            
            fprintf(arquivo, "%-4d | %-30s | %-30s | %-30s | %-10d | R$ %9.2f | R$ %9.2f | %-15s | %s\n",
                    v->id,
                    nome_produto,
                    nome_cliente,
                    nome_funcionario,
                    v->quantidade,
                    v->desconto,
                    v->total,
                    v->formaPagamento,
                    data_formatada);
            
            atual = atual->next;
        }
    }

    fclose(arquivo);
    printf("Relatorio salvo em: relatorio_vendas.txt\n");
}

