#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura para representar um Produto*/
typedef struct Product {
    int code;
    char description[25];
    int quantity;
    float price;
    struct Product *prox;
} Product;

/* Funções de manipulação de produtos*/
void pronpt(char *comando, Product **lst, int *productCount);
void generate_report(Product *lst);
void import_txt(int fileCode, char *fileDescription, int fileQuantity, float filePrice, Product **lst, int *registered);
void import_dat(Product *productFile, Product **lst, int *registered);
int read_file_txt(char *fileName, Product **lst);
int read_file_dat(Product **lst);
void sort_product_code(Product **lst);
void sort_product_quantity(Product **lst);
void terminate_program(Product **lst, int *productCount);
int search_insert(int newCode, Product **lst, int *productCount);
void search_delete(int newCode, Product **lst, int *productCount);
void update_product(char *flag, int newCode, Product *lst);
void get_product(Product *lst);
