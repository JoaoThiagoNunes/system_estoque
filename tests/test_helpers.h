#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H
#include "../include/system.h"

void criar_categoria_teste(int id, const char *nome, const char *descricao);

void criar_fornecedor_teste(int id, const char *nome, const char *telefone);
void criar_produto_teste(int id, const char *nome, int categoriaId, int fornecedorId, 
                         float precoCompra, float precoVenda, int quantidade);

void criar_cliente_teste(int id, const char *nome, const char *telefone);

void criar_funcionario_teste(int id, const char *nome, const char *cargo);

#endif

