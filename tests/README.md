# Testes do Sistema de Estoque

Testes simples para validar o funcionamento do sistema.

## Como Compilar

**Windows PowerShell:**
```powershell
gcc -o tests.exe tests/main.c tests/test_runner.c tests/test_categoria.c tests/test_produto.c tests/test_estoque.c tests/test_integracao.c src/categoria.c src/fornecedor.c src/produto.c src/cliente.c src/funcionario.c src/estoque.c src/venda.c src/pedido.c src/system.c src/utils.c -I include
```

## Como Executar

```powershell
.\tests.exe
```

## Testes Implementados

### Testes de Categoria (3 testes)
- Verifica se lista está vazia após inicialização
- Verifica busca de categoria inexistente
- Verifica busca após inicialização

### Testes de Produto (3 testes)
- Verifica se lista está vazia após inicialização
- Verifica busca de produto inexistente
- Verifica busca após inicialização

### Testes de Estoque (4 testes)
- Testa entrada com produto inexistente
- Testa entrada com quantidade inválida (0 e negativa)
- Testa saída com produto inexistente
- Testa saída com quantidade inválida (0 e negativa)

### Testes de Integração (3 testes)
- Testa fluxo completo de estoque
- Testa fluxo completo de venda
- Testa busca após inicialização de todos os módulos

## Total: 13 testes

Todos os testes são simples e focam em validar comportamentos básicos do sistema.
