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
    while (*endBuff != '\0' || number <= 0){
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

typedef struct node {
    float value;
    int column;
    struct node *next;
} node;

typedef struct matrix {
    node **a;
    int rows;
    int columns;
} matrix;

void newMatrix(matrix *m){
    printf("\nDigite quantas linhas terao a matriz: ");
    int row = intInput();
    printf("\nDigite quantas colunas terao a matriz: ");
    int col = intInput();

    m -> rows = row;
    m -> columns = col;
    m -> a = (node**) malloc(row * sizeof(node*));
    for (int i = 0; i < row; i++){
        m -> a[i] = NULL;
    }
}

int setValue(matrix *m){
    if (m){
        printf("\nDigite o valor a ser atribuido: ");
        float val = floatInput();
        printf("\nDigite a linha que se encontrara o valor: ");
        int row = intInput();
        printf("\nDigite a coluna que se encontrara o valor: ");
        int col = intInput();

        if (row < 0 || row >= m -> rows || col < 0 || col >= m -> columns){
            return 0;
        }

        node *temp = NULL;
        node *current = m -> a[row];

        while (current != NULL && current -> column < col){
            temp = current;
            current = current -> next;
        }

        if (current -> column == col && current != NULL){
            if (val == 0){
                if (temp == NULL) { // temp será NULL se o nó for o primeiro
                    m -> a[row] = current -> next;
                } else {
                    temp -> next = current -> next;
                }
                free (current);
            } else {
                current -> value = val;
            }
        } else {
            node *new = (node*) malloc(sizeof(node));
            new -> column = col;
            new -> value = val;
            new -> next = current;
            if (!temp){
                m -> a[row] = new;
            }
        }
    } else {
        printf("\nMatriz nao inicializada");
        printf("\n\nPressione ENTER para continuar ");
        getchar();
    }
    return 1;
}

int checkValue(matrix *m){
    if (m){
        printf("\nDigite a linha do valor: ");
        int row = intInput();
        printf("\nDigite a coluna do valor: ");
        int col = intInput();

        if (row < 0 || row >= m -> rows || col < 0 || col >= m -> columns){
            printf("\nValor: 0");
            printf("\n\nPressione ENTER para continuar ");
            getchar();
            return 0;
        }

        node *current = m -> a[row];
        while (current){
            if (current -> column == col){
                printf("\nValor: %.3f", current -> value);
                printf("\n\nPressione ENTER para continuar ");
                getchar();
                return 0;
            }
            current = current -> next;
        }
    } else {
        printf("\nMatriz nao inicializada");
        printf("\n\nPressione ENTER para continuar ");
        getchar();
    }
}

int main() {
    matrix *mat = NULL;
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
                newMatrix(mat);
                break;
            case 2:
                setValue(mat);
                break;
            case 3:
                checkValue(mat);
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
}