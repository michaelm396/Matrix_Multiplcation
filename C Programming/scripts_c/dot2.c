#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>
#include "mkl.h"

static int random_int_array(int array[], int length){// const size_t length){
    int i;
    for (i = 0; i < length; ++i) {
        array[i] = rand() % 2;// random_integer(0, 1);
    }
    return 0;
}

int dot_product(int *, int *, MKL_INT); // size_t);

int dot_product(int *c, int *d, MKL_INT n)// size_t n)
{

    MKL_INT incx, incy;
    float res;
    incx = 2;
    incy = 1;
    res = cblas_sdot(n, (const float *)c, incx, (const float *)d, incy);
    return res;


}

int main(void)
{
    int n = 100;
    time_t endwait;
    int seconds = 2;
    endwait = time (NULL) + seconds;
    FILE * fp = fopen("dot2.csv", "w");  
    fprintf(fp, "Size, Opereation Count, Exection Time, Flops\n");
    while (time (NULL) < endwait){
        clock_t t = clock();
        int operation_count = pow(2*n,3);
        int a[n];
        int b[n];
        random_int_array(a,n);
        random_int_array(b,n);
        dot_product(a,b, sizeof(a) / sizeof(a[0]));
        t = clock() - t;
        double time_taken = ((double)t)/CLOCKS_PER_SEC;
        int flops = (operation_count/time_taken)/1000000000;
        fprintf(fp, "%d, %d, %f, %d\n", n, operation_count, time_taken, flops); 
        sleep(1);
        n = n * 2;
        // printf("%d", a[2]);
    }
    fclose(fp);
    return 0;
}

// icc -mkl dot2.c 

/*
source /opt/intel/compilers_and_libraries_2020/mac/bin/compilervars.sh -arch intel64
icc -mkl dgemm_example.c -o dgemm_example
./dgemm_example
*/