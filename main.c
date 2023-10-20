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
    Product* p;
    Product* q;
    Product* nova;
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

        printf("Produto %d inserido com sucesso!\n", newCode);
    } else {
        printf("Erro ao inserir o produto %d\n", newCode);
    }
}

/* Imprimi a lista de produtos */
void imprime_lista(Product* lst) {
    Product* p;

    printf("Lista de Produtos:\n\t");
    for (p = lst; p != NULL; p = p->prox) {
        printf("%d;", p->code);
        printf("%s;", p->description);
        printf("%d;", p->quantity);
        printf("%.2f\n", p->price);
    }
}

/* 
Recebe os Comandos (inserir, inserir excluir, atualizar, ...) 
e chama a função correspondente
*/
void pronpt(char *comando,Product **lst){

    int newCode;

    while (strcmp(comando, "sair"))
    {
        /* pronpt inserir */
        if (!strcmp(comando,"inserir"))
        {
            scanf("%d", &newCode);
            search_insert(newCode, lst);
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