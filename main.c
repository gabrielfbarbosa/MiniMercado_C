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
int search_insert(int newCode, Product** lst, int *productCount) {
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
void search_delete(int newCode, Product** lst, int *productCount) {
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
        printf("\t%d - ", p->code);
        printf("%s - ", p->description);
        printf("%d - ", p->quantity);
        printf("%.2f\n", p->price);

        /*Inserindo no arquivo Relatorio.txt*/
        fprintf(relatorio,"\t%d - ", p->code);
        fprintf(relatorio,"%s - ", p->description);
        fprintf(relatorio,"%d - ", p->quantity);
        fprintf(relatorio,"%.2f\n", p->price);
    }
    fclose(relatorio);
}

/* Importar */
/* Import: função para importar os produtos lidos no arquivo 
para a lista utilizada pelo programa */
void import(Product *productFile, Product **lst, int *registered) {
    Product *p, *q;
    int codeExist;

    p = NULL;
    q = *lst;
    codeExist = 0;

    while (q != NULL && q->code != productFile->code)
    {
        p = q;
        q = q->prox;
    }

    if (q != NULL)
    {
        codeExist++;
    }

    p = NULL;
    q = *lst;
    
    while (q != NULL && strcmp(q->description, productFile->description) < 0) {
        p = q;
        q = q->prox;
    }

    if (codeExist == 0)
    {
        productFile->prox = q;

        if (p != NULL)
            p->prox = productFile;
        else
            *lst = productFile;

        *registered = *registered + 1;
    }
}

/* Como conversado com a professora Ivone na aula do dia 01/11/2023,
a operação 'importar <nome do arquivo>' será considerada que seja
importado arquivos do tipo binário.
read_file: Funcao para ler o arquivo binarios e inserir na lista utilziada no projeto
para se ter uma unica lista com todos os produtos e garantir que nao tenha 
codigo repetido */
int read_file(char *fileName, Product  **lst){
    FILE *fileImport;
    Product *productFile;
    int registered, quantityProducts;

    /*Confirmar a quantidade de produtos importados do arquivo*/
    registered = 0; 
        
    fileImport = fopen(fileName, "rb");
    if (fileImport == NULL)
    {
        /*Mostrar erro apenas quando for arquivos diferente do Produtos.dat
        Ao inicializar o programa e ler o Produtos.dat, não exibir erro*/
        if (!strstr(fileName, "Produtos.dat")) 
        {
            printf("Erro ao importar do arquivo %s\n", fileName);
        }
    }
    else
    {
        /* Faz a leitura da quantidade de registros na primeira linha do arquivo*/
        fread(&quantityProducts, sizeof(int), 1, fileImport);
        
        /* Faz a leitura dos registros do arquivo enquanto tiver registros,
        caso contrario fread é diferente do 3 parametro passado para ela,
        nesse caso o valor 1 */

        while (!feof(fileImport)) {
            
            /* Aloca memoria para receber os registros do arquivo */
            productFile = (Product*)malloc(sizeof(Product));
            if (productFile == NULL)
            {
                printf("Erro de alocação de memória.\n");
                fclose(fileImport);
                return -1;
            }
            
            /* Caso tenha registro a ser lido, importa para a lista */
            if (fread(productFile, sizeof(Product), 1, fileImport) == 1) 
            {
                import(productFile, lst, &registered);
            }
        }

        /* Mostrar a quantidade de produtos importados do arquivo apenas
        quando for arquivos diferente do Produtos.dat. Ao inicializar o
        programa e ler o Produtos.dat, não exibir quantidade importada */
        if (!strstr(fileName, "Produtos.dat"))
        {
            printf("%d produtos importados!\n", registered);
        }

        free(productFile);
        fclose(fileImport);
    }
    return registered;
}

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

/* Ordenar por codigo, utilizando o modelo Insertion Sort
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

/* Recebe os comandos (inserir, excluir, atualizar, ...) 
e chama a função correspondente */
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
            response = read_file(fileName, lst);
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

int main(void){

    Product *products;
    char comando[10];
    int productCount, response;

    products = NULL;
    productCount = 0;

    response = read_file("Produtos.dat", &products);

    scanf("%s", comando);
    
    pronpt(comando, &products, &productCount);

    productCount = response + productCount;

    /* Comando: sair */
    terminate_program(&products, &productCount);

    printf("\n\n");
    return 0;
}
