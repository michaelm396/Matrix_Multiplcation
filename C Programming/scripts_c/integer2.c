#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include "mkl.h"

static int random_int_matrix(int m, int n, int array[m][n] ){
    int x, y;
    for(x = 0; x < m; x++) {
        for(y = 0; y < n; y++) {
            array[x][y] = rand() % 2;
        }
    }
    return 0;
}

static int random_int_array(int array[], int length){// const size_t length){
    int i;
    for (i = 0; i < length; ++i) {
        array[i] = rand() % 2;// random_integer(0, 1);
    }
    return 0;
}

// This function multiplies mat1[][] and mat2[][], 
// and stores the result in res[][] 

// void matrix_matrix_mult((int *, int *, int*);

void matrix_matrix_mult(size_t m,size_t n, int mat1[m][n], int mat2[m][n], int res[m][n]) { 
    double beta = 0.0;
    double alpha = 1.0;
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, n, alpha, (const double *)mat1, m, (const double *)mat2, n, beta, (double *)res, n);
}
  
int main() 
{ 
    int n = 100;
    int m = 100;
    int i;
    double beta = 0.0;
    double alpha = 1.0;
    double *A, *B, *C;
    time_t endwait;
    int seconds = 5;
    endwait = time (NULL) + seconds;
    FILE * fp = fopen("integer2.csv", "w");  
    fprintf(fp, "Size, Label, Opereation Count, Exection Time, Flops\n");
    while (time (NULL) < endwait){
        clock_t t = clock();
        int operation_count = pow(2*n,3);
        /*
        int a[m][n];
        int b[m][n];
        int res[n][n];
        */
        A = (double *)mkl_malloc( m*m*sizeof( double ), 64 );
        B = (double *)mkl_malloc( n*n*sizeof( double ), 64 );
        C = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
        if (A == NULL || B == NULL || C == NULL) {
            mkl_free(A);
            mkl_free(B);
            mkl_free(C);
            return 1;
        }
        for (i = 0; i < (m*m); i++) {
            A[i] = (double)(i+1);
        }

        for (i = 0; i < (n*n); i++) {
            B[i] = (double)(-i-1);
        }

        for (i = 0; i < (m*n); i++) {
            C[i] = 0.0;
        }
        // random_int_matrix(m,n,a);
        // random_int_matrix(m,n,b);
        // matrix_matrix_mult(m,n,A,B,C);// sizeof(a) / sizeof(a[0]));
        //cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, m, n, n, alpha, A, m, B, n, beta, C, n);
        vdPow(n,A,B,C);
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        int flops = (operation_count/time_taken)/1000000000;
        fprintf(fp, "%d, %d, %d, %f, %d\n", n, n, operation_count, time_taken, flops); 
        n = n * 2;
        m = m * 2;
        // printf("%d", a[2]);
    }
    fclose(fp);
    return 0; 
}