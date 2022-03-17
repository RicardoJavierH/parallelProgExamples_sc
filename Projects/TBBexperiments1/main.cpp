#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

using namespace tbb;

const int size = 4;

float a[size][size];
float b[size][size];
float c[size][size];

void printMatrixForm(int size, float A[size][size]);

class Multiply
{
public:
    void operator()(blocked_range<int> r) const {
        for (int i = r.begin(); i != r.end(); ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
    }
};

int main()
{
    // Initialize buffers
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            a[i][j] = (float)i + j;
            b[i][j] = (float)i - j;
            c[i][j] = 0.0f;
        }
    }
    std::cout<<"Matrix A"<<std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout<<*(*(a+i)+j)<<", ";
            
        }
        std::cout<<"\n";
    }
    
    std::cout<<"\n";

    std::cout<<"Matrix B"<<std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout<<*(*(b+i)+j)<<", ";
            
        }
        std::cout<<"\n";
    }
    std::cout<<"\n";

    //printMatrixForm(size, a);
    //printMatrixForm(size, b);


    // Compute matrix multiplication.
    // C <- C + A x B
    parallel_for(blocked_range<int>(0,size), Multiply());
    //printMatrixForm(size, c);
    std::cout<<"Matrix C"<<std::endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout<<*(*(c+i)+j)<<", ";
            
        }
        std::cout<<"\n";
    }

    return 0;
}

void printMatrixForm(int size, float A[size][size]){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout<<*(*(A+i)+j)<<", ";
            
        }
        std::cout<<"/n";
    }
}
