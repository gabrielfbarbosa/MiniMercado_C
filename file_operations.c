#include "functions.h"

/* Relatorio 
A lista ja esta em ordem alfabetica.
Como as comparacoes sao feitas de acordo com os valores da TABELA ASCII
para cada caracter, sera ordenado entao primeiro as letras maiusculas de 'A' a 'Z'
e logo em seguida sera ordenado os as letras minusculas de 'a' a 'z' */
void generate_report(Product *lst){
    Product *p;
    FILE *relatorio;
    char init;
    p = lst;
    /*Inciando com um valor menor do que as letras 
    do alfabeto segundo a TABELA ASCII e por nao conter
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

/* Importa arquivo .dat */
void import_dat(Product *productFile, Product **lst, int *registered) {
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

/*Importa arquivo .txt*/
void import_txt(int fileCode, char *fileDescription, int fileQuantity, float filePrice, Product **lst, int *registered) {
    Product *p, *q, *nova;
    int codeExist;

    p = NULL;
    q = *lst;
    codeExist = 0;

    while (q != NULL && q->code != fileCode)
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
    
    while (q != NULL && strcmp(q->description, fileDescription) < 0) {
        p = q;
        q = q->prox;
    }

    if (codeExist == 0)
    {
        nova = (Product*)malloc(sizeof(Product));
        if (nova == NULL) {
            printf("\nProblema ao alocar memoria");
        }else{
            nova->code = fileCode;
            strcpy(nova->description, fileDescription);
            nova->quantity = fileQuantity;   
            nova->price = filePrice;
            nova->prox = q;

            if (p != NULL)
                p->prox = nova;
            else
                *lst = nova;

            *registered = *registered + 1;
        }
    }
}

/* Le arquivo do tipo .dat */
int read_file_txt(char *fileNameTxt, Product  **lst){
    FILE *fileImportTxt;
    int fileCode, fileQuantity, registered, quantityProducts;
    char fileDescription[25];
    float filePrice;

    /*Confirmar a quantidade de produtos importados do arquivo*/
    registered = 0; 

    fileImportTxt = fopen(fileNameTxt, "r");
    if (fileImportTxt == NULL)
    {
        printf("Erro ao importar do arquivo %s\n", fileNameTxt);
    }
    else
    {
        fscanf(fileImportTxt, "%d\n", &quantityProducts);

        while (feof(fileImportTxt) == 0)
        {
            fscanf(fileImportTxt, "%d;", &fileCode);
            fscanf(fileImportTxt, "%[^;];", fileDescription);
            fscanf(fileImportTxt, "%d;", &fileQuantity);
            fscanf(fileImportTxt, "%f", &filePrice);
            import_txt(fileCode, fileDescription, fileQuantity, filePrice, lst, &registered);
        }
    }
    printf("%d produtos importados!\n", registered);
    fclose(fileImportTxt);
    return registered;
}

/* Le arquivo do tipo .dat*/
int read_file_dat(Product  **lst){
    FILE *fileImportDat;
    Product *productFile;
    int registered, quantityProducts, readCount;

    /*Confirmar a quantidade de produtos importados do arquivo*/
    registered = 0;

    /* Para o caso de se iniciar o programa, e o arquivo Produtos.dat não exister
    ele dever ser criado, como o professor Mauro indicou na aula do dia 7/11/2023.
    Aqui ao utilizar 'rb+' ou 'wb+, não estava conseguindo fazer com que o 
    programa funcionasse sem dar falha de segmentação (Mesmo com a ajuda do professor
    Mauro durante a aula), e quando conseguia, ele não mantinha os dados gravados 
    para proxima inicialização do programa. Ao inciar o programa pela primeira vez, ele
    não conseguira ler o arquivo Produtos.dat (não existente), então ele é criado.
    Assim em uma segunda utilização do programa caso exita o Produtos.dat, ele utiliza
    apenas da leitura sem escrever um conteudo "vazio", como acontece ao utilizar o 
    programa pela primeira vez */
    /*Para um Produtos.dat vazio, ainda esta dando falaha de segmentação*/
    fileImportDat = fopen("Produtos.dat", "rb");
    if (fileImportDat == NULL) {
        /* Se o arquivo não existir, abra-o para escrita e crie o arquivo*/
        fileImportDat = fopen("Produtos.dat", "wb+");
        if (fileImportDat == NULL) {
            /* O documento do trabalo não aborda nem uma menssagem
            quando houver problemas com a leitura do arquivo 
            Produtos.dat, por isso aqui não tem nem uma menssagem
            a ser exibida. */
        }
    } 
    else
    {
        /* Faz a leitura da quantidade de registros na primeira linha do arquivo*/
        readCount = fread(&quantityProducts, sizeof(int), 1, fileImportDat);

        if (readCount == 1)
        {
            while (!feof(fileImportDat)) {
                
                /* Aloca memoria para receber os registros do arquivo */
                productFile = (Product*)malloc(sizeof(Product));
                if (productFile == NULL)
                {
                    printf("Erro de alocação de memória.\n");
                    return -1;
                }
                
                /* Caso tenha registro a ser lido, importa para a lista */
                if (fread(productFile, sizeof(Product), 1, fileImportDat) == 1) 
                {
                    import_dat(productFile, lst, &registered);
                }
            }
            free(productFile);
        }
    }
    fclose(fileImportDat);
    return registered;
}
