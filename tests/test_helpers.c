#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/system.h"
#include "test_helpers.h"

typedef struct CategoriaNode {
    Categoria value;
    struct CategoriaNode *next;
} CategoriaNode;

typedef struct FornecedorNode {
    Fornecedor value;
    struct FornecedorNode *next;
} FornecedorNode;

typedef struct ProdutoNode {
    Produto value;
    struct ProdutoNode *next;
} ProdutoNode;

typedef struct ClienteNode {
    Cliente value;
    struct ClienteNode *next;
} ClienteNode;

typedef struct FuncionarioNode {
    Funcionario value;
    struct FuncionarioNode *next;
} FuncionarioNode;

void criar_categoria_teste(int id, const char *nome, const char *descricao) {
    (void)id;
    (void)nome;
    (void)descricao;
}

void criar_fornecedor_teste(int id, const char *nome, const char *telefone) {
    (void)id;
    (void)nome;
    (void)telefone;
}

void criar_produto_teste(int id, const char *nome, int categoriaId, int fornecedorId, 
                         float precoCompra, float precoVenda, int quantidade) {
    (void)id;
    (void)nome;
    (void)categoriaId;
    (void)fornecedorId;
    (void)precoCompra;
    (void)precoVenda;
    (void)quantidade;
}

void criar_cliente_teste(int id, const char *nome, const char *telefone) {
    (void)id;
    (void)nome;
    (void)telefone;
}

void criar_funcionario_teste(int id, const char *nome, const char *cargo) {
    (void)id;
    (void)nome;
    (void)cargo;
}

