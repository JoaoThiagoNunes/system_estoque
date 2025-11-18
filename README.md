# Sistema de Estoque

Sistema de gerenciamento de estoque desenvolvido em C puro como trabalho acadêmico para a disciplina de **Programação Avançada**.

## 📋 Sobre

Sistema completo de controle de estoque que permite gerenciar categorias, fornecedores, produtos, clientes, funcionários, além de controlar entradas/saídas de estoque e registrar vendas.

## 🚀 Funcionalidades

- **Cadastro**: Categorias, Fornecedores, Produtos, Clientes, Funcionários
- **Listagem**: Visualização de todos os cadastros
- **Estoque**: Registro de entradas e saídas com controle de quantidade
- **Vendas**: Sistema completo de registro de vendas com cálculo automático de totais

## 🛠️ Tecnologias

- **Linguagem**: C (C99)
- **Compilador**: GCC
- **Estruturas de Dados**: Listas encadeadas
- **Sem dependências externas**

## 📁 Estrutura do Projeto

```
system_estoque/
├── include/          # Headers (.h)
├── src/              # Código fonte (.c)
├── tests/            # Testes automatizados
└── README.md         # Este arquivo
```

## 🔨 Compilação

```bash
gcc -o system.exe src/*.c -I include
```

**Windows PowerShell:**
```powershell
gcc -o system.exe src\*.c -I include
```

## ▶️ Execução

```bash
./system.exe    # Linux/Mac
system.exe      # Windows
```

## 📝 Menu Principal

```
=== Sistema de Estoque ===
01 - Cadastrar categoria
02 - Cadastrar fornecedor
03 - Cadastrar produto
04 - Cadastrar cliente
05 - Cadastrar funcionario

06 - Listar categorias
07 - Listar fornecedores
08 - Listar produtos
09 - Listar clientes
10 - Listar funcionarios

11 - Registrar entrada em estoque
12 - Registrar saida em estoque
13 - Registrar venda

 0 - Sair
```

## 🧪 Testes

O projeto inclui um sistema completo de testes automatizados. Para mais informações, consulte [tests/README.md](tests/README.md).

**Compilar testes:**
```bash
gcc -o tests.exe tests/main.c tests/test_runner.c tests/test_*.c src/categoria.c src/fornecedor.c src/produto.c src/cliente.c src/funcionario.c src/estoque.c src/venda.c src/pedido.c src/system.c src/utils.c -I include
```

**Executar testes:**
```bash
./tests.exe
```

## 📚 Módulos do Sistema

- **Categoria**: Gerenciamento de categorias de produtos
- **Fornecedor**: Cadastro de fornecedores com endereço completo
- **Produto**: Produtos com preços de compra/venda e estoque
- **Cliente**: Cadastro de clientes
- **Funcionário**: Gestão de funcionários do sistema
- **Estoque**: Controle de entradas e saídas
- **Venda**: Sistema de vendas integrado

## 🎓 Trabalho Acadêmico

Este projeto foi desenvolvido como trabalho da disciplina de **Programação Avançada**, demonstrando:

- Uso de estruturas de dados (listas encadeadas)
- Modularização de código
- Gerenciamento de memória
- Tratamento de entrada/saída
- Sistema de testes automatizados

## 📄 Licença

Projeto acadêmico - uso educacional.

