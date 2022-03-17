#include <iostream>
#include <vector>
#include <cmath>


#include <tbb/parallel_for.h>

/**
 * @file TPZParallelUtils.h
 *
 * @brief Defines useful utility functions related to multithreading for use in the NeoPZ library
 *
 * @ingroup util
 * (Note: this needs exactly one @defgroup somewhere)
 * @date Mar 2021
 * @author Francisco Orlandini
 * Contact: francisco.orlandini@gmail.com
 *
 */
#include <vector>
#include <thread>
#include <atomic>

/**based on: https://ideone.com/Z7zldb and netgen source code*/

/** This function aims to enable parallel for loops from first <= i < last
as in
#pragma omp parallelfor.
It is the user responsability to use the necessary mutexes and locks.

/*based on
https://stackoverflow.com/questions/48794815/replacing-pragma-omp-atomic-with-c-atomics
and netgen source code
*/

template<typename T>
inline std::atomic<T> & AtomicCast (T & d)
{
  return reinterpret_cast<std::atomic<T>&> (d);
}
/** This function aims to enable atomic addition operation
as in
#pragma omp atomic
a += b
*/
template<typename T>
inline T AtomicAdd( T & sum, T val )
{
  std::atomic<T> & asum = AtomicCast(sum);
  T current = asum.load();
  while (!asum.compare_exchange_weak(current, current + val))
    ;
  return current;
}


//std::atomic<double> suma(0);


int main(int argc, char **argv)
{
    double suma = 0;
    tbb::parallel_for( tbb::blocked_range<long>(0,100000),
                       [&](tbb::blocked_range<long> r)
    {
        for (long indice=r.begin(); indice<r.end(); indice++)
        {
            if(indice % 2 == 0){
                AtomicAdd(suma,4.0 / (2.0 * indice + 1.0) );
                //suma +=  4.0 / (2.0 * indice + 1.0);
            }else{
                AtomicAdd(suma,-4.0 / (2.0 * indice + 1.0) );

                //suma -=  4.0 / (2.0 * indice + 1.0);
            }
        }
    });

    std::cout << suma << std::endl;

    return 0;
}
