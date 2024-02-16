# Sistema de Gerenciamento de Estoque
## Visão Geral
Este Sistema de Gerenciamento de Estoque em C é um aplicativo de console projetado para facilitar o rastreamento e gerenciamento de produtos. O sistema oferece funcionalidades como adição, atualização e venda de produtos, geração de relatórios e importação/exportação de dados de arquivos.

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

## Começando
### Pré-requisitos
- Certifique-se de ter as seguintes ferramentas instaladas: [GCC Compiler](https://gcc.gnu.org/)

### Compilação
- Use o seguinte comando para compilar o projeto:
```
gcc -ansi -pedantic -Wall main.c file_operations.c product_operations.c sort_terminate.c user_interaction.c -o main
```

- Após compilar, execute o arquivo criardo.
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
- Realiza a importação de vários produtos salvos em um arquivo texto com a seguinte formatação: a primeira linha contém o número de produtos no arquivo e em cada linha seguinte há a descrição de um produto com seus campos separados pelo caractere ‘;’ (ponto-e-vírgula). A ordem dos dados do produto no arquivo é a mesma que na operação de inserção.
```
importar nome_arquivo.txt
```
- Exemplo de como o conteúdo do arquivo `nome_arquivo.txt` deve estar.
```
4
31;ARROZ;10;5.90
32;ACUCAR_MASCAVO;5;5.50
41;SABAO_EM_BARRA;12;4.00 
42;SABAO_EM_PO;20;6.95 
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

#### Relatorio
- Apresenta na tela os dados de todos os produtos, organizados em ordem alfabética pelo nome do produto e agrupados pela letra inicial e salva essas informações no arquivo Relatorio.txt. 
```
relatorio
```

#### Registro de venda
- Insira o comando "vender" para iniciar o registro de venda. 
```
vender 
```
- Em seguida, insira os códigos dos produtos que serão vendidos. Insira um código por linha, e para finalizar a lista de produtos, insira o código "0" (zero).
```
<codigo>
return: <codigo> - <nome> - <valor>
<codigo>
return: <codigo> - <nome> - <valor> 
0
---------
return: Total <soma dos valores>
```
- Caso o produto esteja em falta.
 ```
<codigo>
return: <codigo> - produto em falta no estoque 
---------
return: Total <soma dos valores>
```
- Caso de produto não cadastrado.
 ```
<codigo>
return: <codigo> - produto não cadastrado 
0
---------
return: Total <soma dos valores>
```

#### Help
-  Exibir informações sobre a estrutura de dados escolhida para o projeto.
```
help 
```

## Pessoa Desenvolvedora do Projeto

[<img loading="lazy" style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/74202510?v=4" width=115><br><sub><b>Gabriel Felipe Barbosa</b></sub>](https://github.com/gabrielfbarbosa)

Feito com ❤️ por Gabriel Felipe Barbosa 👋🏽 Entre em contato!

![LinkedIn](https://img.shields.io/badge/Gabriel-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white)

[![Yahoo!](https://img.shields.io/badge/Yahoo!-gfelipebarbosa@yahoo.com-6001D2?style=for-the-badge&logo=Yahoo!&logoColor=white&link=mailto:gfelipebarbosa@yahoo.com)](mailto:gfelipebarbosa@yahoo.com)

## Contribuição

Contribuições são bem-vindas! Por favor, abra uma issue ou envie um pull request.
