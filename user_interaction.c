#include "functions.h"

/* checkout_process: Funcao que faz a verificacao se um produto
 pode ser vendido ou nao, fazendo a soma da venda dos produtos */
void checkout_process(int code, Product *lst, float *sale){
    Product *q;

    q = lst;

    /* Procura pelo codigo na lista */
    while (q != NULL && q->code != code)
    {
        q = q->prox;
    }

    if (q == NULL)
    {
        printf("%d - produto não cadastrado\n", code);
        return;
    } else {
        if (q->quantity == 0)
        {
            printf("%d - produto em falta no estoque\n", code);
            return;
        }else{
            q->quantity = q->quantity - 1;
            printf("%d - %s - %.2f\n", q->code, q->description, q->price);
            *sale = *sale + q->price;
        }
    }
}

/* checkout_menu: Faz o controle da entrada dos codigos de produtos
para a venda. Complementa da funcao checkout_process, para gerar 
as vendas dos produtos */
void checkout_menu(Product *lst){
    int code;
    float totalSalePrice;
    
    totalSalePrice = 0;
    scanf("%d", &code);
    while (code != 0)
    {
        checkout_process(code, lst, &totalSalePrice);
        scanf("%d", &code);
    }
    printf("---------\n");
    printf("Total %.2f\n", totalSalePrice);
}

/* help: Explica o motivo da escolha da estrutura */
void help(){
    printf("*************************************************************************************************************\n");
    printf("*                                                                                                           *\n");
    printf("* Estrutura de dados escolhida: Lista simplesmente encadeada ordenada.                                      *\n");
    printf("* Motivo da escolha: Do meu ponto de vista e baseando-me no que foi visto em aula até o momento,            *\n");
    printf("* devido a alguns pedidos de ordenação dos produtos exigidos durante o trabalho,                            *\n");
    printf("* como a ordenação alfabética para o relatório e a ordenação não-decrescente para a operação sair,          *\n");
    printf("* escolher essa estrutura evita uma ordenação durante a execução do código, o que geralmente,               *\n");
    printf("* consome mais processamento e evita criar uma nova lista para inserir os itens ordenados,                  *\n");
    printf("* assegurando um gasto menor de memória.                                                                    *\n");
    printf("*                                                                                                           *\n");
    printf("*************************************************************************************************************\n");
}

/* pronpt: Funcao que faz o controle da entrada dos comandos */
void pronpt(char *comando, Product **lst, int *productCount){
    int newCode, response;
    char flag[3], fileName[20];

    while (strcmp(comando, "sair"))
    {
        /* Comando: inserir */
        if (!strcmp(comando,"inserir"))
        {
            scanf("%d", &newCode);
            response = search_insert(newCode, lst, productCount);
        }

        /* Comando: excluir */
        if (!strcmp(comando,"excluir"))
        {
            scanf("%d", &newCode);
            search_delete(newCode, lst, productCount);
        }

        /* Comando: atualizar */
        if (!strcmp(comando,"atualizar"))
        {
            scanf("%s", flag);
            scanf("%d", &newCode);
            update_product(flag, newCode, *lst);
        }

        /* Comando: consultar */
        if (!strcmp(comando,"consultar"))
        {
            get_product(*lst);
        }

        /* Comando: relatorio */
        if (!strcmp(comando,"relatorio"))
        {
            generate_report(*lst);
        }
        
        /* Comando: importar */
        if (!strcmp(comando,"importar"))
        {
            scanf("%s", fileName);
            response = read_file_txt(fileName, lst);
            *productCount = *productCount + response;
        }

        /* Comando: vender */
        if (!strcmp(comando,"vender"))
        {
            checkout_menu(*lst);
        }

        /* Comando: help */
        if (!strcmp(comando,"help"))
        {
            help();
        }

        if(response == -1)
        { /*Erro ao alocar memoria*/
            comando = "sair";
        } else {
            scanf("%s", comando);
        }
    }
}
