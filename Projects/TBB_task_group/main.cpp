//task_group Class
//A task_group represents concurrent execution of a group of tasks. Tasks may be dynamically added to the group as it is executing.
//Example with Lambda Expressions

#include <iostream>
#include "tbb/task_group.h"

int Fib(int n) {
    if( n<2 ) {
        return n;
    } else {
        int x, y;
        tbb::task_group g;
        g.run([&]{x=Fib(n-1);}); // spawn a task
        g.run([&]{y=Fib(n-2);}); // spawn another task
        g.wait();                // wait for both tasks to complete
        return x+y;
    }
}
int main(){
    for (int i=1;i<10;i++)
        std::cout<<Fib(i)<<" ,";
    std::cout<<std::endl;
}
