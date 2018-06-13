#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void removeNL(char *input){                             // Função para remover o \n do fgets
    size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[--len] = '\0';
    }
}

int intInput() {                                        // Recebe um input com fgets, confere se é
    int number;                                         // um inteiro e o converte com a função strtol
    char inputString[64];
    char *endBuff;
    fgets(inputString, 64, stdin);
    removeNL(inputString);
    number = strtol(inputString, &endBuff, 10);
    while (*endBuff != '\0' || number < 0){
        printf("Por favor digite um numero valido: ");
        fgets(inputString, 64, stdin);
        removeNL(inputString);
        number = strtol(inputString, &endBuff, 10);
    }
    return number;
}

float floatInput() {                                    // Similar a função intInput(), porém
    float number;                                       // validando um float
    char inputString[64];
    char *endBuff;
    fgets(inputString, 64, stdin);
    removeNL(inputString);
    number = strtod(inputString, &endBuff);
    while (*endBuff != '\0' || number <= 0){
        printf("Por favor digite um numero valido: ");
        fgets(inputString, 64, stdin);
        removeNL(inputString);
        number = strtod(inputString, &endBuff);
    }
    return number;
}


typedef struct matrix {
    int rows;
    int columns;
} matrix;


typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, float element[3]) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element[3];
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void newMatrix(matrix m, Array a){
    initArray(&a, 1);
    printf("\nDigite quantas linhas terao a matriz: ");
    int row = intInput();
    printf("\nDigite quantas colunas terao a matriz: ");
    int col = intInput();

    m.rows = row;
    m.columns = col;
}

int setValue(matrix m, Array a){
    // if (a.array){
        printf("\nDigite o valor a ser atribuido: ");
        float val = floatInput();
        printf("\nDigite a linha que se encontrara o valor: ");
        int row = intInput();
        printf("\nDigite a coluna que se encontrara o valor: ");
        int col = intInput();

        if (row < 0 || row >= m.rows || col < 0 || col >= m.columns){
            return 0;
        }
        float element[3] = {row, col, val};
        insertArray(&a, element);
    // }
    return 0;
}

// int checkValue(matrix *m){
//     if (a){
//         printf("\nDigite a linha do valor: ");
//         int row = intInput();
//         printf("\nDigite a coluna do valor: ");
//         int col = intInput();

//         if (row < 0 || row >= m -> rows || col < 0 || col >= m -> columns){
//             printf("\nValor: 0");
//             printf("\n\nPressione ENTER para continuar ");
//             getchar();
//             return 0;
//         }

//         node *current = m -> a[row];
//         while (current){
//             if (current -> column == col){
//                 printf("\nValor: %.3f", current -> value);
//                 printf("\n\nPressione ENTER para continuar ");
//                 getchar();
//                 return 0;
//             }
//             current = current -> next;
//         }
//     } else {
//         printf("\nMatriz nao inicializada");
//         printf("\n\nPressione ENTER para continuar ");
//         getchar();
//     }
// }


int main() {
    Array a;
    a.array = NULL;
    matrix m;
    while (1){
        system("cls");
        printf("\nMatriz Esparsa");
        printf("\n\n 1 - Nova Matriz");
        printf("\n 2 - Atribuir Valor");
        printf("\n 3 - Conferir Valor\n\n");
        printf("\n 0 - Sair\n\n");
        int input = intInput();
        
        switch(input){
            case 1:
                newMatrix(m, a);
                break;
            case 2:
                setValue(m, a);
                break;
//             case 3:
//                 checkValue(mat);
//                 break;
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
}