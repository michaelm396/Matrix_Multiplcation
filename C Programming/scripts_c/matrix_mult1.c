#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>


void block_matrix_matrix_mult(int block, int n, int A[n][n], int B[n][n], int C[n][n]) { 
    int i, j, k, kk, jj; 
    double sum;
    int size;
    size = block * (n/block);

    
    for (i = 0; i < en; i += block){ 
        for (j = 0; j < en; j += block){ 
            for (k = 0; k < n; k++){
                for (jj = j; jj < j + block; jj++){
                    sum = C[k][jj];
                    for (ii = i; ii < i + block; ii++){
                        sum += A[k][ii]*B[ii][jj];
                    }
                    C[k][jj] = sum
                }
            }
        } 
    }
} 
  
int main() 
{ 
    /*
    Matriz size = 4000 x 4000 (static)
    Block sizes 100 x 100 up to 1000 x 1000

    2 plots on 2 different machines 
    */
    int n = 4000;
    int **A, **B, **C;
    int i,j,block;
    // time_t endwait;
    // int seconds = 60 * 10;
    // endwait = time (NULL) + seconds;
    FILE * fp = fopen("mm_block.csv", "w");  
    fprintf(fp, " Matrix Size, Block Size \n");
    fclose(fp);
    test = FALSE
    while (test == FALSE){
        FILE * fp1 = fopen("mm_block.csv","a");
        clock_t t = clock();
        double operation_count = pow(2*n,3);
        A = (int **)malloc( n*n*sizeof( int *) );
        for (i=0; i<n; i++) 
            A[i] = (int *)malloc(n * sizeof(int)); 
        B = (int **)malloc( n*n*sizeof( int *) );
        for (i=0; i<n; i++) 
            B[i] = (int *)malloc(n * sizeof(int)); 
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
        for (i = 0; i < (n); i++)
            for (j = 0; j < n; j++) 
                B[i][j] = rand() % 2;
        for (i = 0; i < (n); i++)
            for (j = 0; j < n; j++) 
                C[i][j] = 0.0  
        block = 100
        block_matrix_matrix_mult(block,n,A,B,C)   
        // Martix vector multiplication
        /*
        for (i=0; i<n; i++)
        {
            for (j=0; j<n; j++)
            {
                C[i][j] = 0.0;
            }
        }
        */
        // t = clock() - t;
        // double time_taken = ((double)t)/CLOCKS_PER_SEC;
        // double flops = (operation_count/time_taken)/1000000000;
        fprintf(fp1, "%d, %d \n", n, block); 
        // sleep(1);
        // n = n * 2;
        // printf("%d", a[2]);
        fclose(fp1);
        test == TRUE
    }
    return 0; 
}