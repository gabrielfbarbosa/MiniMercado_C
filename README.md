# Sistema de Gerenciamento de Estoque

## Visão Geral

Este Sistema de Gerenciamento de Estoque em C é um aplicativo de console projetado para facilitar o rastreamento e gerenciamento de produtos. O sistema oferece funcionalidades como adição, atualização e venda de produtos, geração de relatórios e importação/exportação de dados de/arquivos.

[![Licença](https://img.shields.io/badge/licença-MIT-green.svg)](https://opensource.org/licenses/MIT)

## 🛠 Tecnologias utilizadas

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![Visual Studio Code](https://img.shields.io/badge/Visual%20Studio%20Code-0078d7.svg?style=for-the-badge&logo=visual-studio-code&logoColor=white)
![GitHub](https://img.shields.io/badge/gitflow-%23121011.svg?style=for-the-badge&logo=github&logoColor=white)
![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)

## Sumário

- [Começando](#começando)
  - [Pré-requisitos](#pré-requisitos)
  - [Compilação](#compilação)
- [Uso](#uso)
  - [Comandos](#comandos)
  - [Operações de Arquivo](#operações-de-arquivo)
  - [Operações de Produto](#operações-de-produto)
- [Contribuição](#contribuição)
- [Licença](#licença)

## Começando

### Pré-requisitos

Certifique-se de ter as seguintes ferramentas instaladas:

- [GCC Compiler](https://gcc.gnu.org/)

### Compilação

Use o seguinte comando para compilar o projeto:

```
gcc -ansi -pedantic -Wall main.c file_operations.c product_operations.c sort_terminate.c user_interaction.c -o main
```

Após compilar, execute o arquivo criardo

```
 ./main
```
## Uso
### Comandos
O sistema suporta os seguintes comandos:

- _**´inserir´**_: Inserir um novo produto.

- _**´excluir´**_: Excluir um produto.
- _**´atualizar´**_: Atualizar informações do produto.
- _**´consultar´**_: Exibir produtos com base em uma consulta.
- _**´relatorio´**_: Gerar um relatório alfabético de produtos.
- _**´importar´**_: Importar produtos de um arquivo .txt.
- _**´vender´**_: Inserir códigos de produtos para venda.
- _**´help´**_: Exibir informações sobre a estrutura de dados escolhida.

O sistema deve funcionar como um interpretador de comandos, dando suporte para as seguintes operações:

### Operações de Arquivo

#### Importar Produtos:

- Ao inicializar o programa, o mesmo lê automaticamente os dados de um arquivo 'Produtos.dat', caso esse arquivo não existir, ele será criado na inicialização.

#### Importar de um Arquivo.txt:

- Insira o comando importar e forneça o nome do arquivo.txt.

```
 importar nome_arquivo.txt
```

### Operações de Produto

#### Inserir um Produto:

- Insira o comando 'inserir' e forneça os detalhes do produto, como o codigo, o nome, a quantidade desse mesmo produto e o valor do produto.

```
inserir <código> <nome> <quantidade> <valor>
```

#### Excluir um Produto:

- Insira o comando 'excluir' e forneça o código do produto.

```
excluir <código>
```

#### Atualizar Informações do Produto:

- Insira o comando 'atualizar', uma flag (**-q**: para quantidade, __-v__: para preço), e forneça o código do produto.

```
atualizar -q <código> <novo valor>
```

#### Consulta

- Através de uma sequência de caracteres , esta operação apresenta todos os produtos cadastrados que possuem essa sequência de caracteres no seu nome

```
consultar <sequencia de caracteres>
```

---
---
---
---------------------------------------------------------------

### O que falta
#### relatorio : Gerar um relatório alfabético de produtos.

- ...

```
relatorio 
```
#### importar: Importar produtos de um arquivo .txt.

- ...

```
importar 
```
#### vender: Inserir códigos de produtos para venda.

- ...

```
vender 
```
#### help: Exibir informações sobre a estrutura de dados escolhida.

- ...

```
help 
```

------------------------------------------------------------------
---
---
---

## Contribuição

Contribuições são bem-vindas! Por favor, abra uma issue ou envie um pull request.

## Pessoa Desenvolvedora do Projeto

[<img loading="lazy" style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/74202510?v=4" width=115><br><sub><b>Gabriel Felipe Barbosa</b></sub>](https://github.com/gabrielfbarbosa)

Feito com ❤️ por Gabriel Felipe Barbosa 👋🏽 Entre em contato!


![LinkedIn](https://img.shields.io/badge/Gabriel-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)

[![Yahoo!](https://img.shields.io/badge/Yahoo!-gfelipebarbosa@yahoo.com-6001D2?style=for-the-badge&logo=Yahoo!&logoColor=white&link=mailto:gfelipebarbosa@yahoo.com)](mailto:gfelipebarbosa@yahoo.com)




