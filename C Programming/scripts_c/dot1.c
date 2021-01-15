#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

static int random_int_array(int array[], int length){// const size_t length){
    int i;
    for (i = 0; i < length; ++i) {
        array[i] = rand() % 2;// random_integer(0, 1);
    }
    return 0;
}

int dot_product(int *, int *, size_t);

int dot_product(int *c, int *d, size_t n)
{
    int sum = 0;
    size_t i;

    for (i = 0; i < n; i++) {
            sum += c[i] * d[i];
    }

    return sum;
}

int main(void)
{
    int n = 100;
    int *A, *B, *C;
    int i;
    time_t endwait;
    int seconds = 60 * 10;
    endwait = time (NULL) + seconds;
    FILE * fp = fopen("dot1.csv", "w");  
    fprintf(fp, "Size, Label, Opereation Count, Exection Time, Flops\n");
    fclose(fp);
    while (time (NULL) < endwait){
        FILE * fp1 = fopen("dot1.csv","a");
        clock_t t = clock();
        double operation_count = pow(2*n,3);
        // int a[n];
        // int b[n];
        A = (int *)malloc( n*sizeof( int ) );
        B = (int *)malloc( n*sizeof( int ) );
        C = (int *)malloc( n*sizeof( int ) );
        if (A == NULL || B == NULL || C == NULL) {
            free(A);
            free(B);
            free(C);
            return 1;
        }
        for (i = 0; i < (n); i++) {
            A[i] = (double)(i+1);
        }

        for (i = 0; i < (n); i++) {
            B[i] = (double)(-i-1);
        }

        for (i = 0; i < (n); i++) {
            C[i] = 0.0;
        }
        random_int_array(A,n);
        random_int_array(B,n);
        dot_product(A,B, sizeof(A) / sizeof(A[0]));
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        double flops = (operation_count/time_taken)/1000000000;
        fprintf(fp1, "%d, %d, %lf, %f, %lf\n", n, n, operation_count, time_taken, flops); 
        sleep(1);
        n = n * 2;
        // printf("%d", a[2]);
        fclose(fp1);
    }
return 0;
}    
// gcc -o dot dot.c 