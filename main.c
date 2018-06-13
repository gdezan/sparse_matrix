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
        printf("\n 2 - Atribuir Valor");
        printf("\n 3 - Conferir Valor");
        printf("\n 4 - Deletar Matriz");
        printf("\n\n\n 0 - Sair\n\n");
        int input = intInput();
        
        switch(input){
            case 1:
                newMatrix(&mat);
                break;
            case 2:
                setValue(&mat, &m, &n , &value);
                break;
            case 3:
                checkValue(&mat, m, n ,value);
                break;
            case 4:
                deleteMatrix(&mat, &m, &n , &value);
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