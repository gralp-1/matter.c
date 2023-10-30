/* matter.c - gralp-1
 * A complete(ly untested) matrix library in C
 * Features:
 *  - probably unsafe
 *  - only works with integers
 *  - unlikely to work
 */
#include <assert.h>
#include <stdlib.h>

typedef struct {
  int cols;
  int rows;
  int *mat;
} Matrix;

Matrix InitMatrix(int cols, int rows) {
  Matrix res;
  res.cols = cols;
  res.rows = rows;
  res.mat = malloc(sizeof(int) * cols * rows);
  assert(res.mat != NULL && "buy more RAM");
  return res;
}

Matrix MatAddMat(Matrix *a, Matrix *b) {
  assert(a->rows == b->rows && a->cols == b->cols &&
         "Non conformable matrices");
  Matrix newMatrix = InitMatrix(a->cols, a->rows);

  for (int i = 0; i < a->rows * a->cols; i++) {
    newMatrix.mat[i] = a->mat[i] + b->mat[i];
  }
  return newMatrix;
}
int *MatrixGetRow(const Matrix *a, const int n) {
  // get the ith column
  int *row = malloc(sizeof(int) * a->cols);
  assert(row != NULL && "buy more RAM");
  int j = 0;
  for (int i = 0; i < n; i++) {
    // get the y coordinate (wrap because it's a 1d array)
    int y = i / a->cols;
    if (y == n) {
      row[j] = a->mat[i];
      j++;
    }
  }
  return row;
}
int *MatrixGetCol(const Matrix *a, const int n) {
  // get the ith column
  int *col = malloc(sizeof(int) * a->rows);
  assert(col != NULL && "buy more RAM");
  int j = 0;

  for (int i = 0; i < n; i++) {
    // get the x coordinate (wrap because it's a 1d array)
    int x = i % a->cols;
    if (x == n) {
      col[j] = a->mat[i];
      j++;
    }
  }
  return col;
}

Matrix PointerArrToMat(int *arr, int rows, int cols) {
  return (Matrix){.mat = arr, .rows = rows, .cols = cols};
}

int MatSum(Matrix *a, Matrix *b) {
  assert(a->rows != 1 && b->cols != 1 &&
         "Non conformable for matrix multiplication (not 1 by x and x by 1)");
  assert(a->cols == b->rows && "Rows and Cols must be equal");

  int sum = 0;

  for (int i = 0; i < a->rows; i++) {
    sum += a->mat[i] * b->mat[i];
  }
  return sum;
}

void MatSetPoint(Matrix *a, int col, int row, int val) {
  // turn x & y into an index and then set that index to val
  int idx = a->cols * row + col;
  a->mat[idx] = val;
}

// dot product of matrices
Matrix MatDotMat(Matrix *a, Matrix *b) {
  Matrix newMatrix = InitMatrix(a->rows, b->cols);
  assert(a->cols == b->rows && "Non conformable for dot product");

  for (int row = 0; row < a->rows; row++) {
    int *aRow = MatrixGetRow(a, row);
    Matrix aRowMatrix = PointerArrToMat(aRow, 1, a->cols);
    for (int col = 0; col < b->cols; col++) {
      int *bCol = MatrixGetCol(b, col);
      Matrix bRowMatrix = PointerArrToMat(bCol, b->rows, 1);
      int matPoint = MatSum(&aRowMatrix, &bRowMatrix);
      MatSetPoint(&newMatrix, col, row, matPoint);
    }
  }

  return newMatrix;
}
// Matrix MatCrossMat(const Matrix *a, const Matrix *b) {  }

// TODO: convert arguments to const
// Equivalent to a - b
Matrix MatSubMat(Matrix *a, Matrix *b) {

  assert(a->rows == b->rows && a->cols == b->cols &&
         "Non conformable matrices");

  Matrix newMatrix = InitMatrix(a->cols, a->rows);

  for (int i = 0; i < a->cols * a->rows; i++) {
    newMatrix.mat[i] = a->mat[i] - b->mat[i];
  }

  return newMatrix;
}

// TODO: unify usage of newMatrix and res
Matrix MatTimesScalar(Matrix *a, int scalar) {

  Matrix res = InitMatrix(a->cols, a->rows);
  for (int i = 0; i < a->cols * a->rows; i++)
    res.mat[i] = scalar * a->mat[i];

  return res;
}

void DestroyMatrix(Matrix mat) { free(mat.mat); }
