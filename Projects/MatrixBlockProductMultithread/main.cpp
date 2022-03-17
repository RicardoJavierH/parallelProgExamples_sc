#include <iostream>
#include <new>
#include "mkl.h"
#include<thread>
#include <chrono>

void initializeMatrix(int n,double* ptrM);

void printMatrixForm(int N, int M, double *A, int LDA);

void simpleProduct(int n,double* ptrA,double* ptrB,double* ptrC);

void BlockDecomp(int n,int k,double* ptrM, double* ptrM11,double* ptrM12,double* ptrM21,double* ptrM22);

//This function is for compute blocks of the product matrix (C11=A11B11+A12B21)
void blockCij (int k,double* A1,double* A2,double* B1,double* B2,double* Res);

void BlockMatrixProduct (int n,double* A,double* B,double* C);

int main(){
    int n=1000;//Order of square matrices A and B to computing the product
    double* A=new double[n*n];
    double* B=new double[n*n];
    double* C=new double[n*n];
    mkl_set_num_threads(1);
    std::cout<<"Matrix "<<"A: "<<n<<" by "<<n<<std::endl;
    initializeMatrix(n, A);
    //printMatrixForm(n, n, A, n);
    std::cout<<"\n\n";
    std::cout<<"Matrix "<<"B: "<<n<<" by "<<n<<std::endl;
    initializeMatrix(n, B);
    //printMatrixForm(n, n, B, n);
    std::cout<<"\n\n";
    
    auto start = std::chrono::system_clock::now();
    BlockMatrixProduct(n, A, B, C);
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<float,std::milli> duration = end - start;
    std::cout << duration.count() << " ms " << std::endl;
    
    //printMatrixForm(n,n,C,n); std::cout<<"\n";
    
    delete[] A;
    delete[] B;
    delete[] C;
    
    return 0;
}

void initializeMatrix(int n,double* ptrM){
    for (int i=0;i<n*n;i++){
        *(ptrM+i)=i+1;
        //std::cout<<*(ptrM+i)<<", ";
    }
};
void printMatrixForm(int N, int M, double *A, int LDA) {
double mtmp;
printf("[ ");
for (int i = 0; i < N; i++) {
    printf("[ ");
    for (int j = 0; j < M; j++) {
        mtmp = A[i*LDA + j];
        printf("%5.2f", mtmp);
        if (j < M - 1) printf(", ");
    }
    if (i < N - 1) printf("]; ");
    else printf("] ");
}
    printf("]");
}

void simpleProduct(int n,double* ptrA,double* ptrB,double* ptrC){
    double alpha=1.0; double beta=0.;
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, alpha, ptrA, n, ptrB, n, beta, ptrC, n);
};
//This function is for compute blocks of the product matrix (C11=A11B11+A12B21)
void blockCij (int k,double* A1,double* A2,double* B1,double* B2,double* Res){
    double* Aux1=new double[k*k]; double* Aux2=new double[k*k];
    simpleProduct(k,A1,B1,Aux1);
    simpleProduct(k,A2,B2,Aux2);
    for (int i=0;i<k*k;i++)
        *(Res+i)=*(Aux1+i)+*(Aux2+i);
        
    delete[] Aux1; delete[] Aux2;
}

void BlockDecomp(int n,int k,double* ptrM, double* ptrM11,double* ptrM12,double* ptrM21,double* ptrM22){
    for (int i=0;i<n*n;i++){
        int aux2=i%n;
        if ((aux2<k)&(i<k*n)) {
            *(ptrM11++)=*(ptrM+i);
        }
        if ((aux2>=k)&(i<k*n)) {
            *(ptrM12++)=*(ptrM+i);
        }
        if ((aux2<k)&(i>=k*n)) {
            *(ptrM21++)=*(ptrM+i);
        }
        if ((aux2>=k)&(i>=k*n)) {
            *(ptrM22++)=*(ptrM+i);
        }
    };
}

void BlockMatrixProduct (int n,double* A,double* B,double* C){
    int k=n/2;
    double* A11=new double[k*k]; double* A12=new double[k*k];
    double* A21=new double[k*k]; double* A22=new double[k*k];
    double* B11=new double[k*k]; double* B12=new double[k*k];
    double* B21=new double[k*k]; double* B22=new double[k*k];
    double* C11=new double[k*k]; double* C12=new double[k*k];
    double* C21=new double[k*k]; double* C22=new double[k*k];
    BlockDecomp(n, k, A, A11, A12, A21, A22);
    BlockDecomp(n, k, B, B11, B12, B21, B22);
    
    auto fun1=[](int k,double* A1,double* A2,double* B1,double* B2,double* Res){
        double* Aux1=new double[k*k]; double* Aux2=new double[k*k];
        simpleProduct(k,A1,B1,Aux1);
        simpleProduct(k,A2,B2,Aux2);
        for (int i=0;i<k*k;i++)
            *(Res+i)=*(Aux1+i)+*(Aux2+i);
            
        delete[] Aux1; delete[] Aux2;
    };
    auto fun2=[](int k,double* A1,double* A2,double* B1,double* B2,double* Res){
        double* Aux1=new double[k*k]; double* Aux2=new double[k*k];
        simpleProduct(k,A1,B1,Aux1);
        simpleProduct(k,A2,B2,Aux2);
        for (int i=0;i<k*k;i++)
            *(Res+i)=*(Aux1+i)+*(Aux2+i);
            
        delete[] Aux1; delete[] Aux2;
    };
    auto fun3=[](int k,double* A1,double* A2,double* B1,double* B2,double* Res){
        double* Aux1=new double[k*k]; double* Aux2=new double[k*k];
        simpleProduct(k,A1,B1,Aux1);
        simpleProduct(k,A2,B2,Aux2);
        for (int i=0;i<k*k;i++)
            *(Res+i)=*(Aux1+i)+*(Aux2+i);
            
        delete[] Aux1; delete[] Aux2;
    };
    auto fun4=[](int k,double* A1,double* A2,double* B1,double* B2,double* Res){
        double* Aux1=new double[k*k]; double* Aux2=new double[k*k];
        simpleProduct(k,A1,B1,Aux1);
        simpleProduct(k,A2,B2,Aux2);
        for (int i=0;i<k*k;i++)
            *(Res+i)=*(Aux1+i)+*(Aux2+i);
            
        delete[] Aux1; delete[] Aux2;
    };
    
    std::thread t0(fun1,k, A11, A12, B11, B21, C11);
    std::thread t1(fun2,k, A11, A12, B12, B22, C12);
    std::thread t2(fun3,k, A21, A22, B11, B21, C21);
    std::thread t3(fun4,k, A21, A22, B12, B22, C22);
    t0.join(); t1.join(); t2.join(); t3.join();

    /*
    blockCij(k, A11, A12, B11, B21, C11);
    blockCij(k, A11, A12, B12, B22, C12);
    blockCij(k, A21, A22, B11, B21, C21);
    blockCij(k, A21, A22, B12, B22, C22);*/
    
    
    double* ptrC11=C11; double* ptrC12=C12;
    double* ptrC21=C21; double* ptrC22=C22;
    
    //Assembling the resulting product matrix
    for (int i=0;i<n*n;i++){
        int aux2=i%n;
        if ((aux2<k)&(i<k*n)) {
            *(C+i)=*(ptrC11++);
        }
        if ((aux2>=k)&(i<k*n)) {
            *(C+i)=*(ptrC12++);
        }
        if ((aux2<k)&(i>=k*n)) {
            *(C+i)=*(ptrC21++);
        }
        if ((aux2>=k)&(i>=k*n)) {
            *(C+i)=*(ptrC22++);
        }
    };
        
    delete[] A11; delete[] A12; delete[] A21; delete[] A22;
    delete[] B11; delete[] B12; delete[] B21; delete[] B22;
    delete[] C11; delete[] C12; delete[] C21; delete[] C22;
}
