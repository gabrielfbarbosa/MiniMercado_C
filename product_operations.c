#include "functions.h"

/* Busca e insere ordenado pela descrição  */
int search_insert(int newCode, Product **lst, int *productCount) {
    Product *p, *q, *nova;
    char descrip[25];
    int codeExist;

    p = NULL;
    q = *lst;
    codeExist = 0;

    scanf("%s", descrip);

    /* Verifica se o novo código já existe na lista */
    while (q != NULL && q->code != newCode)
    {
        p = q;
        q = q->prox;
    }

    /* Marcador para o caso do novo código já existir na lista  */
    if (q != NULL)
    {
        codeExist++;
    }

    /* Resetando p e q para inserir em ordem alfabética 
    considerando a primeira letra da descrição */
    p = NULL;
    q = *lst;
    
    /* Utilizando o strcmp para ordenar de acordo com a palavra, 
    para que a palavra 'abc' venha depois de 'aac' */
    while (q != NULL && strcmp(q->description, descrip) < 0) {
        p = q;
        q = q->prox;
    }

    /* Caso código não exista na lista, cadastra em ordem alfabética */
    if (codeExist == 0)
    {
        nova = (Product*)malloc(sizeof(Product));
        if (nova == NULL) {
            printf("Erro de alocação de memória.\n");
            /* Retorna -1 para encerrar o programa e 
            salvar o estado do mesmo até o momento */
            return -1;
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

            printf("Produto %d inserido com sucesso!\n", newCode);
            *productCount = *productCount + 1;
        }
        /* Retorna 1 para o programa prosseguir após inserir mais um produto */
        return 1;
    } else{
        printf("Erro ao inserir o produto %d.\n", newCode);
        return 1;
    }
}

/* Busca e remove */
void search_delete(int newCode, Product **lst, int *productCount) {
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
        printf("Produto %d excluído com sucesso!\n", newCode);
        *productCount = *productCount - 1;
    }else{
        printf("Produto %d não cadastrado!\n", newCode);
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
            printf("Produto %d atualizado \n", newCode);
        } 

        /* Atualiza o Preco do produto */
        if (!strcmp(flag, "-v")) {
            scanf("%f", &newPrice);
            p->price = newPrice;
            printf("Produto %d atualizado \n", newCode);
        } 
        
    }else{
        printf("Produto %d não cadastrado!\n", newCode);
    }
}

/* Consulta produto
get_product: Retorna os produtos que tem em sua descricao, a sequencia
de caracteres digiada pelo usuario. Como na documentacao do trabalho 
nao diz nada a respeito da ordem a ser impressa na tela, entao para evitar 
mais umka ordenacao, esta sendo impresso ordenados pela descricao do produto,
como esta minha lista */
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
            printf("Nenhum produto encontrado!\n");
        }
    }
    else
    {
        printf("Nenhum produto encontrado!\n");
    }
}
