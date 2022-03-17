
#include <iostream>
#include <vector>
#include <thread>

//long multiThreadedSum = 0; //occurs rice condition
std::atomic<long> multiThreadedSum(0);

void sumNumbers(const std::vector<int>& toBeSummed, int idxStart, int idxEnd){
    for (int i=idxStart; i<=idxEnd; i++)
        multiThreadedSum += toBeSummed[i];
}

int main(int argc, const char * argv[]) {
    
    std::vector<int> toBeSummed;
    for (int i=0; i<30000; i++)
        toBeSummed.push_back(rand());
    
    long sum = 0;
    for (int i=0; i < toBeSummed.size(); i++)
        sum += toBeSummed[i];
    
    std::cout<< "sum = " << sum <<std::endl;
    
    //----------
    
    std::thread t1(sumNumbers, toBeSummed, 0, 9999);
    std::thread t2(sumNumbers, toBeSummed ,10000, 19999);
    std::thread t3(sumNumbers, toBeSummed ,20000, 29999);

    t1.join();
    t2.join();
    t3.join();
    
    std::cout<< "sum = " << multiThreadedSum <<std::endl;

    
    return 0;
}
