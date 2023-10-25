/******************************************
*                                         *
* Gabriel Felipe Barbosa                  *
* Trabalho Prático                        *
* Disciplina: Algortimos e Programação II *
* Professores: Ivone, Mauro e Ronaldo     *
*                                         *
*******************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct prod
{
    int code;
    char description[25];
    int quantity;
    float price;
    struct prod *prox;
}Product;

/* Busca e insere ordenado  */
void search_insert(int newCode, Product** lst) {
    Product *p, *q, *nova;
    char descrip[25];
    int codeExist;

    p = NULL;
    q = *lst;
    codeExist = 0;

    scanf("%s", descrip);

    /*Para saber se o novo codigo ja existe na lista */
    while (q != NULL && q->code != newCode)
    {
        p = q;
        q = q->prox;
    }

    /* Marcador para o caso do novo codigo ja existirna lista  */
    if (q != NULL)
    {
        codeExist++;
    }

    /* Reseto p e q para inserir em ordem alfabetica
    considerando a primeira letra da descricao */
    p = NULL;
    q = *lst;
    
    /* Utilizando o strcmp para ordenar de acordo com a palavra
    para que a palavra 'abc' venha depois da palavra 'aac' */
    while (q != NULL && strcmp(q->description, descrip) < 0) {
        p = q;
        q = q->prox;
    }

    /*Caso codigo nao existir na lista, cadastra em ordem alfabetica*/
    if (codeExist == 0)
    {
        nova = (Product*)malloc(sizeof(Product));
        if (nova == NULL) {
            printf("\nProblema ao alocar memoria");
        }else{
            nova->code = newCode;
            strcpy(nova->description, descrip);
            scanf("%d", &nova->quantity);   
            scanf("%f", &nova->price);
            nova->prox = q;

            if (p != NULL)
                p->prox = nova;
            else
                *lst = nova;

            printf(" Produto %d inserido com sucesso!\n", newCode);
        }
    } else{
        printf("[ERRO: Erro ao inserir o produto %d.]\n", newCode);
    }
}

/* Busca e remove */
void search_delete(int newCode, Product** lst) {
    Product *p, *q;
    p = NULL;
    q = *lst;

    while (q != NULL && q->code != newCode) {
        p = q;
        q = q->prox;
    }

    if (q != NULL) {
        if (p != NULL) {
            p->prox = q->prox;
        } else {
            *lst = q->prox;
        }
        free(q);
        printf(" Produto %d excluído com sucesso!\n", newCode);
    }else{
        printf("[ERROR: Produto %d não cadastrado!]\n", newCode);
    }
}

/* Atualiza produto */
void update_product(char *flag ,int newCode, Product *lst) {
    Product *p;
    int newQuantity;
    float newPrice;
    p = lst;

    while (p != NULL && p->code != newCode) {
        p = p->prox;
    }

    if (p != NULL) {
        
        /* Atualiza a Qauntidade do produto */
        if (!strcmp(flag, "-q")) {
            scanf("%d", &newQuantity);
            p->quantity = newQuantity;
            printf(" Produto %d atualizado \n", newCode);
        } 

        /* Atualiza o Preco do produto */
        if (!strcmp(flag, "-v")) {
            scanf("%f", &newPrice);
            p->price = newPrice;
            printf(" Produto %d atualizado \n", newCode);
        } 
        
    }else{
        printf("[ERROR: Produto %d não cadastrado!]\n", newCode);
    }
}

/* Consulta produto */
void get_product(Product *lst){
    Product *p;
    char searchQuery[25];
    int cont;

    /*Para saber se encontrou ao menos um produto*/
    cont = 0;
    
    scanf("%s", searchQuery);
    if (lst != NULL)
    {
        for (p = lst; p != NULL; p = p->prox) {
            if(strstr(p->description, searchQuery)){
                printf("\t%d - ", p->code);
                printf("%s - ", p->description);
                printf("%d - ", p->quantity);
                printf("%.2f\n", p->price);
                cont++;
            }
        }
        if (cont == 0)
        {
            printf("[ERROR: Nenhum produto encontrado!]\n");
        }
    }
}


/* Relatorio */
/* A lista ja esta em ordem alfabetica.
Como as comparacoes sao feitas de acordo com os valores da TABELA ASCII
para cada caracter, sera ordenado entao primeiro as letras maiusculas de 'A' a 'Z'
e logo em seguida sera ordenado os as letras minusculas de 'a' a 'z' */
void generate_report(Product *lst){
    Product *p;
    FILE *relatorio;
    char init;
    p = lst;
    /*Inciando com um valor menor do que as letras 
    do alfabeto segundo a TABELA ASCII e pro nao conter
    espacos na decricao*/
    init = ' '; 
    
    relatorio = fopen("Relatorio.txt", "w");
    if (relatorio == NULL)
    {
        printf("Erro ao abrir arquivo");
        return;
    }

    for (p = lst; p != NULL; p = p->prox) {
        /*Verifica se a primeira letra do produto ja foi mostrada na tela*/
        if (p->description[0] > init)
        {
            printf("%c\n", p->description[0]);
            fprintf(relatorio, "%c\n", p->description[0]);
            init = p->description[0];
        }
        /*Mostrando no terminal*/
        printf("\t%d;", p->code);
        printf("%s;", p->description);
        printf("%d;", p->quantity);
        printf("%.2f\n", p->price);

        /*Inserindo no arquivo Relatorio.txt*/
        fprintf(relatorio,"\t%d;", p->code);
        fprintf(relatorio,"%s;", p->description);
        fprintf(relatorio,"%d;", p->quantity);
        fprintf(relatorio,"%.2f\n", p->price);
    }
    fclose(relatorio);
}


/* Imprimi a lista de produtos */
void imprime_lista(Product *lst) {
    Product* p;
    printf("Lista de Produtos:\n\t");
    if (lst != NULL)
    {
        for (p = lst; p != NULL; p = p->prox) {
            printf("%d;", p->code);
            printf("%s;", p->description);
            printf("%d;", p->quantity);
            printf("%.2f\n\t", p->price);
        }
    }else
        printf("Lista Vazia!\n");
}

/* 
Recebe os Comandos (inserir, inserir excluir, atualizar, ...) 
e chama a função correspondente
*/
void pronpt(char *comando, Product **lst, Product **reportList){

    int newCode;
    char flag[3];

    while (strcmp(comando, "sair"))
    {
        /* Comando: inserir */
        if (!strcmp(comando,"inserir"))
        {
            scanf("%d", &newCode);
            search_insert(newCode, lst);
            /*imprime_lista(*lst);*/
        }

        /* Comando: excluir */
        if (!strcmp(comando,"excluir"))
        {
            scanf("%d", &newCode);
            search_delete(newCode, lst);
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

        /*Recebe um novo comando apos finalizar o comando anterior
        Caso for sair, criar uma nova lista ordenada com os produtos 
        de estoque baixo menor que 15
        */
        scanf("%s", comando);
    }
}


int main(void){

    Product *products, *reportList;
    char comando[10];

    products = NULL;
    reportList = NULL;

    scanf("%s", comando);
    
    pronpt(comando, &products, &reportList);

    imprime_lista(products);

    printf("\n\n");
    return 0;
}