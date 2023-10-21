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

/* Busca e insere */
void search_insert(int newCode, Product** lst) {
    Product *p, *q, *nova;
    p = NULL;
    q = *lst;

    while (q != NULL && q->code != newCode) {
        p = q;
        q = q->prox;
    }

    if (q == NULL) {
        nova = (Product*)malloc(sizeof(Product));
        nova->code = newCode; 

        /* Cadastra restante das informacoes do produto */
        scanf("%s", nova->description);
        scanf("%d", &nova->quantity);   
        scanf("%f", &nova->price);

        nova->prox = NULL;

        if (p != NULL)
            p->prox = nova;
        else
            *lst = nova;

        printf(" Produto %d inserido com sucesso!\n", newCode);
    } else {
        printf("[ERROR: Erro ao inserir o produto %d.]\n", newCode);
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
void pronpt(char *comando, Product **lst){

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

        /*Recebe um novo comando apos finalizar o comando anterior*/
        scanf("%s", comando);
    }
}


int main(void){

    Product *products;
    char comando[10];

    products = NULL;

    scanf("%s", comando);
    
    pronpt(comando, &products);

    imprime_lista(products);

    printf("\n\n");
    return 0;
}