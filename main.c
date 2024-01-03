/******************************************
*                                         *
* Gabriel Felipe Barbosa                  *
* Trabalho Prático                        *
* Disciplina: Algortimos e Programação II *
* Professores: Ivone, Mauro e Ronaldo     *
*                                         *
*******************************************/
#include <stdio.h>
#include "functions.h"

/* Comando para compilar o projeto: 
gcc -ansi -pedantic -Wall main.c file_operations.c product_operations.c sort_terminate.c user_interaction.c -o main */

int main(void){

    Product *products;
    char comando[10];
    int productCount, response;

    products = NULL;
    productCount = 0;

    response = read_file_dat(&products);

    scanf("%s", comando);
    
    pronpt(comando, &products, &productCount);

    productCount = response + productCount;

    /* Comando: sair */
    terminate_program(&products, &productCount);

    printf("\n\n");
    return 0;
}