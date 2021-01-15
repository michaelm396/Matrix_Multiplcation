#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>


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

void matrix_vector_mult(size_t m,size_t n, int mat1[m][n], int mat2[n], int res[m][n]) { 
    int i, j;
    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
        {
            res[j][0] += mat1[j][i] * mat2[i];
        }
    }
} 
  
int main() 
{ 
    int n = 100;
    int m = 100;
    int *B;
    int **A, **C;
    int i,j;
    time_t endwait;
    int seconds = 60 * 10;
    endwait = time (NULL) + seconds;
    FILE * fp = fopen("mv1.csv", "w");  
    fprintf(fp, "Size, Label, Opereation Count, Exection Time, Flops\n");
    fclose(fp);
    while (time (NULL) < endwait){
        FILE * fp1 = fopen("mv1.csv","a");
        clock_t t = clock();
        double operation_count = pow(2*n,3);
        // int a[m][n];
        // int b[n];
        // int res[n][n];
        A = (int **)malloc( n*n*sizeof( int *) );
        for (i=0; i<n; i++) 
            A[i] = (int *)malloc(n * sizeof(int)); 
        B = (int *)malloc( n*sizeof( int ) );
        C = (int **)malloc( n*n*sizeof( int *) );
        for (i=0; i<n; i++) 
            C[i] = (int *)malloc(n * sizeof(int)); 
        if (A == NULL || B == NULL || C == NULL) {
            free(A);
            free(B);
            free(C);
            return 1;
        }
        // Allocate Matrx
        for (i = 0; i <  n; i++) 
            for (j = 0; j < n; j++) 
                A[i][j] = rand() % 2;
        for (i = 0; i < (n); i++) {
            B[i] = rand() % 2;
        }
        // Martix vector multiplication
        for (i=0; i<n; i++)
        {
            for (j=0; j<n; j++)
            {
                C[j][0] += A[j][i] * B[i];
            }
        }

        // random_int_matrix(m,n,A);
        // random_int_array(B,n);
        // matrix_vector_mult(m,n,A,B,C);// sizeof(a) / sizeof(a[0]));
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        double flops = (operation_count/time_taken)/1000000000;
        fprintf(fp1, "%d, %d, %lf, %lf, %lf\n", n, n, operation_count, time_taken, flops); 
        sleep(2);
        n = n * 2;
        m = m *2;
        fclose(fp1);
        // printf("%d", a[2]);
    }
return 0; 
}