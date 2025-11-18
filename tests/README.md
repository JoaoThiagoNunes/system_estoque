# Sistema de Testes - Sistema de Estoque

Este documento explica como o sistema de testes funciona internamente e como utilizá-lo.

## Visão Geral

O sistema de testes foi criado do zero, sem dependências externas, usando apenas macros C e funções padrão. Ele fornece um framework simples mas eficaz para testar o código do sistema de estoque.

## Arquitetura do Sistema de Testes

### Estrutura de Arquivos

```
tests/
├── test_runner.h          # Framework de testes (macros e declarações)
├── test_runner.c          # Implementação do framework
├── test_helpers.h         # Declarações de funções auxiliares
├── test_helpers.c         # Funções auxiliares para criar dados de teste
├── test_categoria.c       # Testes unitários para categorias
├── test_produto.c         # Testes unitários para produtos
├── test_estoque.c         # Testes para funções de estoque
├── test_integracao.c      # Testes de integração
├── main.c                 # Ponto de entrada - executa todos os testes
└── README.md              # Este arquivo
```

## Como Funciona Internamente

### 1. Variáveis Globais de Controle

O sistema usa três variáveis globais para rastrear o estado dos testes:

```c
extern int tests_run;      // Total de testes executados
extern int tests_passed;   // Testes que passaram
extern int tests_failed;   // Testes que falharam
```

Essas variáveis são definidas em `test_runner.c` e declaradas como `extern` no header para uso em todos os arquivos de teste.

### 2. Sistema de Macros de Assertion

As macros de assertion são o coração do framework. Elas funcionam da seguinte forma:

#### Estrutura Básica

Todas as macros seguem o mesmo padrão:

```c
#define ASSERT_EQ(a, b) \
    do { \
        if ((a) != (b)) { \
            printf("  [FALHOU] %s:%d: Esperado %d, obtido %d\n", \
                   __FILE__, __LINE__, (int)(b), (int)(a)); \
            tests_failed++; \
            return; \
        } \
    } while (0)
```

**Como funciona:**

1. **`do { ... } while (0)`**: Esta construção permite que a macro seja usada como uma única instrução, mesmo após um `if` ou `else`. É uma técnica padrão em C para criar macros seguras.

2. **Verificação da condição**: A macro verifica se a condição esperada é verdadeira. Se não for:
   - Imprime uma mensagem de erro com `__FILE__` e `__LINE__` (macros do pré-processador que indicam onde o erro ocorreu)
   - Incrementa `tests_failed`
   - Executa `return` para sair da função de teste imediatamente

3. **Se a condição for verdadeira**: A macro não faz nada e a execução continua normalmente.

#### Macros Disponíveis

| Macro | Descrição | Exemplo |
|-------|-----------|---------|
| `ASSERT_EQ(a, b)` | Verifica se `a == b` (inteiros) | `ASSERT_EQ(5, resultado)` |
| `ASSERT_NE(a, b)` | Verifica se `a != b` | `ASSERT_NE(0, valor)` |
| `ASSERT_FLOAT_EQ(a, b)` | Verifica se dois floats são iguais (tolerância 0.001) | `ASSERT_FLOAT_EQ(3.14, pi)` |
| `ASSERT_NULL(ptr)` | Verifica se ponteiro é NULL | `ASSERT_NULL(ponteiro)` |
| `ASSERT_NOT_NULL(ptr)` | Verifica se ponteiro não é NULL | `ASSERT_NOT_NULL(ptr)` |
| `ASSERT_TRUE(cond)` | Verifica se condição é verdadeira | `ASSERT_TRUE(lista_vazia)` |
| `ASSERT_FALSE(cond)` | Verifica se condição é falsa | `ASSERT_FALSE(erro)` |
| `ASSERT_STR_EQ(a, b)` | Verifica se duas strings são iguais | `ASSERT_STR_EQ("teste", str)` |

### 3. Sistema de Execução de Testes

A macro `RUN_TEST` é responsável por executar cada teste:

```c
#define RUN_TEST(test_func) \
    do { \
        current_test_name = #test_func; \
        tests_run++; \
        printf("Executando: %s\n", current_test_name); \
        int antes_falhas = tests_failed; \
        test_func(); \
        if (antes_falhas == tests_failed) { \
            tests_passed++; \
            printf("  [OK]\n"); \
        } \
    } while (0)
```

**Fluxo de execução:**

1. **Armazena o nome do teste**: `#test_func` converte o nome da função em string
2. **Incrementa contador**: `tests_run++` conta que um teste foi executado
3. **Imprime nome do teste**: Mostra qual teste está sendo executado
4. **Salva estado antes**: Armazena quantas falhas existiam antes do teste
5. **Executa o teste**: Chama a função de teste
6. **Verifica resultado**: Se o número de falhas não mudou, o teste passou
7. **Incrementa sucessos**: Se passou, incrementa `tests_passed` e imprime `[OK]`

**Por que verificar `antes_falhas`?**

Se uma assertion falhar, ela incrementa `tests_failed` e executa `return`, saindo da função de teste. Ao comparar `antes_falhas == tests_failed`, sabemos se o teste completou sem falhas.

### 4. Fluxo de Execução Completo

```
main() [tests/main.c]
  │
  ├─> inicializar_dados()  // Prepara o sistema
  │
  ├─> rodar_testes_categoria()
  │     │
  │     ├─> RUN_TEST(test_categorias_vazias_inicial)
  │     │     └─> test_categorias_vazias_inicial()
  │     │           └─> ASSERT_TRUE(categorias_vazias())
  │     │
  │     ├─> RUN_TEST(test_categorias_buscar_inexistente)
  │     └─> ...
  │
  ├─> rodar_testes_produto()
  ├─> rodar_testes_estoque()
  ├─> rodar_testes_integracao()
  │
  ├─> finalizar_sistema()  // Limpa recursos
  │
  └─> test_summary()        // Exibe relatório final
```

## Exemplo Prático: Criando um Teste

Vamos criar um teste passo a passo:

### Passo 1: Criar a função de teste

```c
static void test_exemplo(void) {
    // Inicializa o módulo que será testado
    categorias_inicializar();
    
    // Verifica estado inicial
    ASSERT_TRUE(categorias_vazias());
    
    // Tenta buscar categoria inexistente
    const Categoria *cat = categorias_buscar_por_id(999);
    ASSERT_NULL(cat);
    
    // Limpa recursos
    categorias_finalizar();
}
```

**Características importantes:**
- Função `static`: Visível apenas no arquivo atual
- Retorno `void`: Não retorna valor
- Nome começa com `test_`: Convenção para identificar testes
- Inicializa e finaliza: Garante estado limpo

### Passo 2: Registrar o teste

Adicione na função `rodar_testes_*()` correspondente:

```c
void rodar_testes_categoria(void) {
    printf("\n=== Testes de Categoria ===\n");
    
    RUN_TEST(test_categorias_vazias_inicial);
    RUN_TEST(test_categorias_buscar_inexistente);
    RUN_TEST(test_exemplo);  // <-- Novo teste
    
    categorias_finalizar();
}
```

### Passo 3: Compilar e executar

```bash
gcc -o tests.exe tests/main.c tests/test_runner.c ... [outros arquivos]
./tests.exe
```

## Compilação

### Comando Completo

```bash
gcc -o tests.exe \
    tests/main.c \
    tests/test_runner.c \
    tests/test_categoria.c \
    tests/test_produto.c \
    tests/test_estoque.c \
    tests/test_integracao.c \
    tests/test_helpers.c \
    src/categoria.c \
    src/fornecedor.c \
    src/produto.c \
    src/cliente.c \
    src/funcionario.c \
    src/estoque.c \
    src/venda.c \
    src/pedido.c \
    src/system.c \
    src/utils.c \
    -I include
```

### Por que não usar `src/*.c`?

O arquivo `src/main.c` contém a função `main()` do programa principal, que conflitaria com `tests/main.c`. Por isso, listamos os arquivos explicitamente, excluindo `src/main.c`.

### Windows PowerShell

```powershell
gcc -o tests.exe `
    tests\main.c `
    tests\test_runner.c `
    tests\test_categoria.c `
    tests\test_produto.c `
    tests\test_estoque.c `
    tests\test_integracao.c `
    tests\test_helpers.c `
    src\categoria.c `
    src\fornecedor.c `
    src\produto.c `
    src\cliente.c `
    src\funcionario.c `
    src\estoque.c `
    src\venda.c `
    src\pedido.c `
    src\system.c `
    src\utils.c `
    -I include
```

## Execução

Após compilar:

```bash
./tests.exe    # Linux/Mac
tests.exe      # Windows
```

### Saída Esperada

```
========================================
  Sistema de Testes - Sistema Estoque
========================================

Listas inicializadas. Cadastre os dados pelo menu.

=== Testes de Categoria ===
Executando: test_categorias_vazias_inicial
  [OK]
Executando: test_categorias_buscar_inexistente
  [OK]
...

=== Resumo dos Testes ===
Total de testes: 13
Aprovados: 13
Falhados: 0

[TODOS OS TESTES PASSARAM!]
```

## Tipos de Testes

### Testes Unitários

Testam funções individuais isoladamente:

- **Verificação de estado inicial**: Listas vazias após inicialização
- **Busca de itens inexistentes**: Verifica tratamento de erros
- **Validação de parâmetros**: Testa comportamento com entradas inválidas

**Exemplo:**
```c
static void test_busca_inexistente(void) {
    produtos_inicializar();
    Produto *prod = produtos_buscar_por_id(999);
    ASSERT_NULL(prod);  // Deve retornar NULL para ID inexistente
    produtos_finalizar();
}
```

### Testes de Integração

Testam fluxos completos envolvendo múltiplos módulos:

- **Fluxo de estoque**: Criar produto → Registrar entrada → Registrar saída
- **Fluxo de vendas**: Verificar dependências entre produto, cliente e funcionário
- **Verificação de dependências**: Testa se módulos se comunicam corretamente

**Exemplo:**
```c
static void test_fluxo_completo(void) {
    estoque_inicializar();
    produtos_inicializar();
    
    // Tenta registrar entrada para produto inexistente
    registrar_entrada(1, 10);
    Produto *prod = produtos_buscar_por_id(1);
    ASSERT_NULL(prod);  // Produto não deve existir
    
    produtos_finalizar();
    estoque_finalizar();
}
```

## Boas Práticas

### 1. Sempre inicialize e finalize

```c
static void test_exemplo(void) {
    categorias_inicializar();  // Sempre inicialize
    // ... testes ...
    categorias_finalizar();     // Sempre finalize
}
```

### 2. Use assertions apropriadas

```c
// Para inteiros
ASSERT_EQ(esperado, obtido);

// Para ponteiros
ASSERT_NULL(ponteiro);
ASSERT_NOT_NULL(ponteiro);

// Para condições booleanas
ASSERT_TRUE(condicao);
ASSERT_FALSE(condicao);

// Para strings
ASSERT_STR_EQ("esperado", string_obtida);
```

### 3. Teste casos de erro

```c
// Teste comportamento com entradas inválidas
registrar_entrada(999, -5);  // Quantidade negativa
registrar_entrada(999, 0);   // Quantidade zero
```

### 4. Mantenha testes independentes

Cada teste deve poder executar isoladamente, sem depender de outros testes.

## Limitações e Considerações

### Limitação: Funções que leem do stdin

As funções `cadastrar_*()` usam `ler_texto()` que lê do stdin. Por isso, os testes focam em:

- Funções que recebem parâmetros diretamente (`registrar_entrada`, `registrar_venda`)
- Funções de busca e verificação
- Validação de parâmetros inválidos

### Solução Futura

Para testar fluxos completos com dados reais, seria necessário:

1. Criar funções auxiliares que inserem dados diretamente nas estruturas
2. Ou modificar as funções `cadastrar_*()` para aceitar parâmetros opcionais
3. Ou usar mock de entrada (redirecionar stdin)

Atualmente, optamos por não modificar o código original para manter a integridade do sistema.

## Estrutura de um Teste Completo

```c
#include "../include/system.h"
#include "test_runner.h"

// 1. Função de teste
static void test_nome_descritivo(void) {
    // 2. Setup: Inicializa o que for necessário
    categorias_inicializar();
    
    // 3. Execute: Chama a função sendo testada
    const Categoria *cat = categorias_buscar_por_id(999);
    
    // 4. Assert: Verifica o resultado
    ASSERT_NULL(cat);
    
    // 5. Teardown: Limpa recursos
    categorias_finalizar();
}

// 6. Registra o teste
void rodar_testes_categoria(void) {
    printf("\n=== Testes de Categoria ===\n");
    RUN_TEST(test_nome_descritivo);
    categorias_finalizar();
}
```

## Debugging de Testes

Se um teste falhar, a macro de assertion mostrará:

```
[FALHOU] test_categoria.c:45: Esperado 0, obtido 1
```

Isso indica:
- **Arquivo**: `test_categoria.c`
- **Linha**: `45`
- **Esperado**: `0`
- **Obtido**: `1`

Use essas informações para identificar e corrigir o problema.

## Extensões Futuras

O sistema pode ser estendido com:

- **Testes de performance**: Medir tempo de execução
- **Cobertura de código**: Rastrear quais funções foram testadas
- **Testes parametrizados**: Executar o mesmo teste com diferentes valores
- **Mock de funções**: Simular comportamento de funções externas

## Conclusão

Este sistema de testes fornece uma base sólida para validar o código do sistema de estoque. É simples, sem dependências externas, e fácil de entender e estender.

Para mais informações sobre como adicionar novos testes, consulte a seção "Exemplo Prático" acima.
