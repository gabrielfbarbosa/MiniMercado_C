#include "functions.h"

/* Ordenar por codigo, utilizando o modelo Insertion Sort 
por ser um algoritmo de ordenacao estável
sort_product_code: Ordena os produtos por codigo
para ser salvo no arquivo Produto.dat */
void sort_product_code(Product **lst) {
    Product *sorted, *current, *next, *search;

    sorted = NULL;
    current = *lst;

    while (current != NULL) {
        next = current->prox; /*Guarda o Produto da frente para a proxima comparacao comecar a partir dele*/
        if (sorted == NULL || sorted->code >= current->code) {
            current->prox = sorted; /*Se for o primeiro Produto ou se o codigo for menor que o codigo do primeiro Produto*/
            sorted = current; /*O primeiro Produto vai ser o atual*/
        } else {
            search = sorted;
            while (search->prox != NULL && search->prox->code < current->code) {
                search = search->prox;/*Procura pelo proximo Produto para inserir*/
            }
            current->prox = search->prox; /*Inserir o Produto no lugar certo*/
            search->prox = current; 
        }
        current = next; /*Proximo Produto*/
    }
    *lst = sorted;/*Atualiza a lista*/
}

/* Ordenar estoque baixo
sort_product_quantity: Ordena os produtos por sua quantidade
quando abaixo de 15. Caso a quantidade for maior que 15 nao salva o produto */
void sort_product_quantity(Product **lst) {
    Product *sorted, *current, *next, *search;

    sorted = NULL;
    current = *lst;

    while (current != NULL) {

        next = current->prox;
        if (current->quantity <= 15)
        {
            if (sorted == NULL || sorted->quantity >= current->quantity) {
                current->prox = sorted;
                sorted = current;
            } else {
                search = sorted;
                while (search->prox != NULL && search->prox->quantity < current->quantity) {
                    search = search->prox;
                }
                current->prox = search->prox;
                search->prox = current;
            }
        }
        current = next;
    }
    *lst = sorted;
}

/* Sair */
/* terminate_program: Encerra o programa e preenche os 
arquivos Comprar.txt e Produtos.dat */
void terminate_program(Product **lst, int *productCount){
    Product *p, *next;
    FILE *buyFile, *productsFile;

    productsFile = fopen("Produtos.dat", "wb");
    if (productsFile == NULL)
    {
        printf("Erro ao escrever no arquivo Produtos.dat");
        return;
    }

    buyFile = fopen("Comprar.txt", "w");
    if (buyFile == NULL)
    {
        printf("Erro ao escrever no arquivo Comprar.txt");
        return;
    }

    fwrite(&productCount, sizeof(int), 1, productsFile);
    
    sort_product_code(lst);
    for(p = *lst; p != NULL; p = p->prox){
        /* Salva informacoes no arquivo*/
        fwrite(p, sizeof(Product), 1, productsFile);
    }
    fclose(productsFile);

    sort_product_quantity(lst);
    for(p = *lst; p != NULL; p = p->prox){
        /* Salva informacoes no arquivo*/
        fprintf(buyFile,"%d - ", p->code);
        fprintf(buyFile,"%s - ", p->description);
        fprintf(buyFile,"%d\n", p->quantity);

        /* Moastra informacoes na tela*/
        printf("%d - ", p->code);
        printf("%s - ", p->description);
        printf("%d\n", p->quantity);
    }
    fclose(buyFile);

    /*Libera toda memoria alocada */
    p = *lst;
    while (p != NULL) {
        next = p->prox;  
        free(p);         
        p = next;        
    }
    *lst = NULL;
}