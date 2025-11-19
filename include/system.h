#ifndef SYSTEM_H
#define SYSTEM_H
#include <time.h>

typedef struct {
    char rua[80];
    char cidade[45];
    char estado[3];
    char cep[10];
    char numero[10];
    char complemento[40];   
    char bairro[40];
    char pais[40];
    char pontoReferencia[100];
    int tipoEndereco;
} Endereco;


typedef struct {
    int id;
    char nome[40];
    char descricao[120];
    char codigo[20];
    int ativo;
    time_t dataCriacao;
    time_t dataAtualizacao;
    char tags[100];
} Categoria;


typedef struct {
    int id;
    char nome[60];
    char telefone[20];
    Endereco endereco;
    char email[100];
    char cnpj[18];
    int ativo;
    time_t dataCadastro;
} Fornecedor;


typedef struct {
    int id;
    char nome[60];
    int categoriaId;
    int fornecedorId;
    float precoCompra;
    float precoVenda;
    int quantidade;
    char codigoBarras[20];
    char unidadeMedida[10];
} Produto;


typedef struct {
    int id;
    char nome[60];
    char telefone[20];
    Endereco endereco;
    char email[100];
    char cpf[14];
    char dataNascimento[10];
    int ativo;
    time_t dataCadastro;
} Cliente;


typedef struct {
    int id;
    char nome[60];
    char cargo[30];
    char login[20];
    char senha[20];
    char email[100];
    char cpf[14];
    char telefone[20];
    time_t dataAdmissao;
    int ativo;
} Funcionario;


typedef struct {
    int id;
    int produtoId;
    int quantidade;
    time_t data;
    int fornecedorId;
    char numeroNotaFiscal[30];
    float valorTotal;
    int funcionarioId;
    char observacoes[200];
} EntradaEstoque;


typedef struct {
    int id;
    int produtoId;
    int quantidade;
    time_t data;
    int funcionarioId;
    float valorTotal;
    int tipoSaida;
    char observacoes[200];
} SaidaEstoque;


typedef struct {
    int id;
    int fornecedorId;
    int produtoId;
    int quantidade;
    time_t dataPedido;
    int status;
    float precoUnitario;
    float valorTotal;
    time_t dataEntregaPrevista;
    char observacoes[200];
} PedidoCompra;


typedef struct {
    int id;
    int clienteId;
    int funcionarioId;
    int produtoId;
    int quantidade;
    time_t dataVenda;
    float total;
    float desconto;
    char formaPagamento[20];
    char observacoes[200];
} Venda;

void categorias_inicializar(void);
void categorias_finalizar(void);
int categorias_vazias(void);
const Categoria *categorias_buscar_por_id(int id);

void fornecedores_inicializar(void);
void fornecedores_finalizar(void);
int fornecedores_vazios(void);
const Fornecedor *fornecedores_buscar_por_id(int id);

void produtos_inicializar(void);
void produtos_finalizar(void);
int produtos_vazios(void);
Produto *produtos_buscar_por_id(int id);

void clientes_inicializar(void);
void clientes_finalizar(void);
int clientes_vazios(void);
const Cliente *clientes_buscar_por_id(int id);

void funcionarios_inicializar(void);
void funcionarios_finalizar(void);
const Funcionario *funcionarios_buscar_por_id(int id);

void estoque_inicializar(void);
void estoque_finalizar(void);
float calcular_valor_investido_por_entradas(void);
float calcular_custo_total_saidas(void);

void pedidos_inicializar(void);
void pedidos_finalizar(void);
PedidoCompra *pedidos_buscar_por_id(int id);
int pedidos_proximo_id(void);
void cadastrar_pedido(void);

void vendas_inicializar(void);
void vendas_finalizar(void);

void inicializar_dados(void);
void finalizar_sistema(void);

void cadastrar_categoria(void);
void cadastrar_fornecedor(void);
void cadastrar_produto(void);
void cadastrar_cliente(void);
void cadastrar_funcionario(void);

void listar_categorias(void);
void listar_produtos(void);
void listar_clientes(void);
void listar_fornecedores(void);
void listar_funcionarios(void);

void registrar_entrada(int produtoId, int quantidade);
void registrar_saida(int produtoId, int quantidade);
void registrar_venda(int produtoId, int clienteId, int funcionarioId, int quantidade);

float calcular_valor_investido(void);
float calcular_valor_total_vendas(void);
float calcular_custo_total_vendas(void);
void gerar_relatorio_vendas(void);

#endif 
