# matter.c
A matrix library in C

Example Usage:
```c
// create a 2x2 identity matrix
Matrix mat1 = InitMatrix(2,2);
mat.mat = {1,0,1,0};

// create another 2x2 matrix
Matrix mat2 = InitMatrix(2,2);
mat.mat = {34, 52, -123, 1};

// multiply these
Matrix product = MatMulMat(mat1, mat2);

// deinitialisation
DestroyMatrix(mat1);
DestroyMatrix(mat2);
DestroyMatrix(product);
```
