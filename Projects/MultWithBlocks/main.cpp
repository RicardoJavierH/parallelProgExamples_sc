/* C source code is found in dgemm_example.c */

#define min(x,y) (((x) < (y)) ? (x) : (y))
#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include "mkl.h"
#include<thread>
#include<vector>
int main()
{
    double *A11, *B11, *C11;
    int m, n, k, i, j;
    double alpha, beta;
    int incX=1, incY=1;

    printf ("\n This example computes real matrix C=alpha*A*B+beta*C using \n"
            " Intel(R) MKL function dgemm, where A, B, and  C are matrices and \n"
            " alpha and beta are double precision scalars\n\n");

    m = 8, k = 8, n = 8;
    printf (" Initializing data for matrix multiplication C=A*B for matrix \n"
            " A(%ix%i) and matrix B(%ix%i)\n\n", m, k, k, n);
    alpha = 1.0; beta = 0.0;
    printf (" Allocating memory for matrices aligned on 64-byte boundary for better \n"
            " performance \n\n");
    A11 = (double *)mkl_malloc( m*k*sizeof( double ), 64 );
    B11 = (double *)mkl_malloc( k*n*sizeof( double ), 64 );
    C11 = (double *)mkl_malloc( m*n*sizeof( double ), 64 );
    if (A11 == NULL || B11 == NULL || C11 == NULL) {
      printf( "\n ERROR: Can't allocate memory for matrices. Aborting... \n\n");
      mkl_free(A11);
      mkl_free(B11);
      mkl_free(C11);
      return 1;
    }
    
    printf (" Intializing matrix data \n\n");
    for (i = 0; i < (m*k); i++) {
        A11[i] = (double)(1.);
    }

    for (i = 0; i < (k*n); i++) {
        B11[i] = (double)(1.);
    }

    for (i = 0; i < (m*n); i++) {
        C11[i] = 0.0;
    }
    
    printf (" Computing matrix product using Intel(R) MKL dgemm function via CBLAS interface \n\n");
    
    std::vector<std::thread> hilos;
 
    for(int i = 0; i < 4; ++i){
    hilos.push_back(std::thread([&](){
    //std::cout << "Hola desde el hilo " << std::this_thread::get_id() << std::endl;
        std::cout<<"\n"<<std::this_thread::get_id()<<std::endl;
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    m, n, k, alpha, A11, k, B11, n, beta, C11, n);
        cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                    m, n, k, alpha, A11, k, B11, n, beta, C11, n);
        
        cblas_daxpy( n,alpha, C11, incX, C11,incY);
    }));
    }
 
    for(auto& thread : hilos){thread.join();}
    

    printf ("\n Computations completed.\n\n");
    
    
    printf (" Top left corner of matrix A: \n");
    for (i=0; i<min(m,4); i++) {
      for (j=0; j<min(k,4); j++) {
        printf ("%12.0f", A11[j+i*k]);
      }
      printf ("\n");
    }

    printf ("\n Top left corner of matrix B: \n");
    for (i=0; i<min(k,4); i++) {
      for (j=0; j<min(n,4); j++) {
        printf ("%12.0f", B11[j+i*n]);
      }
      printf ("\n");
    }
    
    printf ("\n Top left corner of matrix C: \n");
    for (i=0; i<min(m,4); i++) {
      for (j=0; j<min(n,4); j++) {
        printf ("%12.5G", C11[j+i*n]);
      }
      printf ("\n");
    }

    printf ("\n Deallocating memory \n\n");
    mkl_free(A11);
    mkl_free(B11);
    mkl_free(C11);

    printf (" Example completed. \n\n");
    return 0;
}
