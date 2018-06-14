#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int main()
{
    Array m,n;
    ArrayF value;
    matrix mat;
    mat.init = 0;

    initArray(&m, 5); 
    initArray(&n, 5); 
    initArrayF(&value, 5); 

    while (1){
        system(CLEAR);
        printf("\n Matriz Esparsa");
        printf("\n\n 1 - Nova Matriz");
        printf("\n 2 - Deletar Matriz");
        printf("\n 3 - Atribuir Valor a Elemento");
        printf("\n 4 - Conferir Valor de um Elemento");
        printf("\n 5 - Conferir Soma dos Elementos de uma Linha");
        printf("\n 6 - Conferir Soma dos Elementos de uma Coluna");
        printf("\n 7 - Consultar Matriz");
        printf("\n\n\n 0 - Sair\n\n");
        int input = intInput();
        
        switch(input){
            case 1:
                newMatrix(&mat);
                break;
            case 2:
                deleteMatrix(&mat, &m, &n , &value);
                break;
            case 3:
                setValue(&mat, &m, &n , &value);
                break;
            case 4:
                checkValue(&mat, m, n ,value);
                break;
            case 5:
                rowSum(&mat, m, value);
                break;
            case 6:
                columnSum(&mat, n, value);
                break;
            case 7:
                displayMatrix(&mat, value);
                break;
            case 0:
                return 0;
            default:
                printf("Essa opcao nao existe.\n");
                printf("\n\nPressione ENTER para continuar ");
                getchar();
                break;
        }
        fflush(stdin);
    }


    freeArray(&m);
    freeArray(&n);
    freeArrayF(&value);
    
    return 0;
}