#ifndef matrix_H_
#define matrix_H_

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

typedef struct {
    int rows;
    int columns;
    int init;
} matrix;

typedef struct {
  float *array;
  size_t used;
  size_t size;
} ArrayF;

typedef struct {
  int *array;
  size_t used;
  size_t size;
} Array;

void removeNL(char *input);
void tStop();
int intInput();
float floatInput();
void initArray(Array *a, size_t initialSize);
void initArrayF(ArrayF *a, size_t initialSize);
void insertArray(Array *a, int element);
void insertArrayF(ArrayF *a, float element);
void freeArray(Array *a);
void freeArrayF(ArrayF *a);
void newMatrix(matrix *m);
void setValue(matrix *mat, Array *m, Array *n, ArrayF *value);
int checkValue(matrix *mat, Array m, Array n, ArrayF value);
int deleteMatrix(matrix *mat, Array *m, Array *n, ArrayF *value);

#endif