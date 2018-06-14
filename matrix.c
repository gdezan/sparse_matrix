#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

void removeNL(char *input){                             // Função para remover o \n do fgets
    size_t len = strlen(input);
        if (len > 0 && input[len-1] == '\n') {
            input[--len] = '\0';
    }
}

void tStop(){
    printf("\n\nPressione ENTER para continuar ");
    getchar();
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
    while (*endBuff != '\0' || number < 0){
        printf("Por favor digite um numero valido: ");
        fgets(inputString, 64, stdin);
        removeNL(inputString);
        number = strtod(inputString, &endBuff);
    }
    return number;
}

void initArray(Array *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void initArrayF(ArrayF *a, size_t initialSize) {
  a->array = (float *)malloc(initialSize * sizeof(float));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(Array *a, int element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void insertArrayF(ArrayF *a, float element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (float *)realloc(a->array, a->size * sizeof(float));
  }
  a->array[a->used++] = element;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void freeArrayF(ArrayF *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

void newMatrix(matrix *m){
    if (m->init == 0){
        printf("\nDigite quantas linhas terao a matriz: ");
        int row = intInput();
        printf("Digite quantas colunas terao a matriz: ");
        int col = intInput();

        m->rows = row;
        m->columns = col;
        m->init = 1;
        printf("\nMatriz criada.");
    } else {
        printf("\nA matriz ja foi inicializada. Para criar uma nova matriz, delete a atual.");
    }
    tStop();
}


int setValue(matrix *mat, Array *m, Array *n, ArrayF *value){
    if (mat->init == 1){
        int found = -1;
        printf("\nDigite o valor a ser atribuido: ");
        float val = floatInput();
        
        printf("Digite a linha que se encontrara o elemento: ");
        int row = intInput();

        printf("Digite a coluna que se encontrara o elemento: ");
        int col = intInput();
        
        for (int i = 0; i < m->used; i++){
            if(row == m->array[i] && col == n->array[i]){
                found = i;
            }
        }

        if (row <= 0 || row > mat->rows || col <= 0 || col > mat->columns){
            printf("\nElemento fora do escopo da matriz. Valor nao atribuido.");
        } else if (found != -1){
            printf("\nEsse elemento ja possui um valor diferente de 0.\n");
            printf("Deseja substitui-lo? (Valor antigo: %.2f) (S/N): ", value->array[found]);
            char prompt;
            while (1){
                fflush(stdin);
                prompt = getchar();
                getchar();
                if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                    break;
                }
                printf("\nPor favor digite \"S\" ou \"N\"\n");                      
            }                                                                       
            if (prompt == 'N' || prompt == 'n'){
                printf("\nValor antigo mantido.");
                tStop();                                   
                return 0;              
            }
            value->array[found] = val;
            printf("\nValor antigo substituido.");
        } else {
            insertArray(n, col);
            insertArray(m, row);
            insertArrayF(value, val);
            printf("\nValor atribuido.");
        }
    } else {
        printf("\nMatriz nao inicializada.");
    }
    tStop();
    return 0;
}

int checkValue(matrix *mat, Array m, Array n, ArrayF value){
    if (mat->init == 1){
        printf("\nDigite a linha do elemento: ");
        int row = intInput();
        printf("Digite a coluna do elemento: ");
        int col = intInput();

        if (row <= 0 || row > mat->rows || col <= 0 || col > mat->columns){
            printf("\nElemento fora do escopo da matriz.");
            tStop();
            return 0;
        }

        int found = 0;
        for (int i = 0; i < m.used; i++){
            if(row == m.array[i] && col == n.array[i]){
                found = 1;
                printf("\nValor: %.2f", value.array[i]);
            }
        }
        if (found == 0){
            printf("\nValor: 0");
        }
    } else {
        printf("\nMatriz nao inicializada.");
    }

    tStop();
    return 0;
}

int deleteMatrix(matrix *mat, Array *m, Array *n, ArrayF *value){
    if (mat->init == 1){
        printf("\nTem certeza que deseja deletar a matriz? (S/N)\n");

        char prompt;
        while (1){
            fflush(stdin);
            prompt = getchar();
            getchar();
            if (prompt == 'S' || prompt == 's' || prompt == 'n' || prompt == 'N'){
                break;
            }
            printf("\nPor favor digite \"S\" ou \"N\"\n");                      
        }                                                                       
        if (prompt == 'N' || prompt == 'n'){
            printf("\nMatriz nao deletada.");
            tStop();                                   
            return 0;              
        }

        freeArray(m);
        freeArray(n);
        freeArrayF(value);
        initArray(m, 5); 
        initArray(n, 5); 
        initArrayF(value, 5);
        mat->init = 0;
        printf("\nMatriz deletada.");
    } else {
        printf("\nMatriz nao inicializada.");
    }
    tStop();
    return 0;
}

void rowSum(matrix *mat, Array m, ArrayF value){
    if (mat->init == 1){
        printf("\nDigite a linha para consultar a soma dos elementos: ");
        int row = intInput();
        if (row <= mat->rows && row > 0){
            float sum = 0;
            for (int i = 0; i < m.used; i++){
                if(row == m.array[i]){
                    sum += value.array[i];
                }
            }
            printf("\nValor da soma da linha %d: %.2f", row, sum);
        } else {
            printf("\nLinha fora do escopo da matriz.");
        }
    } else {
        printf("\nMatriz nao inicializada.");
    }
    tStop();
}

void columnSum(matrix *mat, Array n, ArrayF value){
    if (mat->init == 1){
        printf("\nDigite a coluna para consultar a soma dos elementos: ");
        int col = intInput();
        if (col <= mat->columns && col > 0){
            float sum = 0;
            for (int i = 0; i < n.used; i++){
                if(col == n.array[i]){
                    sum += value.array[i];
                }
            }
            printf("\nValor da soma da coluna %d: %.2f", col, sum);
        } else {
            printf("\nColuna fora do escopo da matriz.");
        }
    } else {
        printf("\nMatriz nao inicializada.");
    }
    tStop();
}

void displayMatrix(matrix *mat, ArrayF val){
    if (mat->init == 1){
        printf("\nDimensoes da matriz (m x n): %d x %d", mat->rows, mat->columns);
        int zeroes = 0;
        for (int i = 0; i < val.used; i++){
            if (val.array[i] == 0){
                zeroes++;
            }
        }
        printf("\nNumero de elementos nao nulos: %d", val.used - zeroes);
    } else {
        printf("\nMatriz nao inicializada.");
    }
    tStop();
}
 