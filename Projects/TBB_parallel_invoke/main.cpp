// parallel_invoke Template Function
// Template function that evaluates several functions in parallel

#include <tbb/parallel_invoke.h>
#include <iostream>
long parallel_fib(long n) {
    if(n<2) {
        return n;
    }
    else {
        long x,y;
        tbb::parallel_invoke([&]{x=parallel_fib(n-1);},
                             [&]{y=parallel_fib(n-2);});
        return x+y;
    }
}
int main(){
    std::cout<<" Fibonacci sequence generated using parallel_invoke"<<std::endl;
    for(int i=1;i<13;i++)
        std::cout<<parallel_fib(i)<<" ,";
    std::cout<<std::endl;
}
