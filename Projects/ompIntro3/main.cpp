/*For the implementation of the parallel form with optimized for loops, the "parallel" directives will be used for parallel execution and "for" in each for loop present in the implementation For the calculation of the subseries, the use of this directive is responsible to distribute the iterations according to the number of threads available and to calculate the response of the problem, this directive is used to make the sum of the values calculated by each thread, more quickly. */
#include <stdio.h>
#include "omp.h"
#include <iostream>
using namespace std;

int main(){
    int numeroHilos = 2, idHilo;
    omp_set_num_threads(numeroHilos);
    double respuesta = 0.0, sumasParciales[numeroHilos];
    long numeroIteraciones=100000;
    //printf("Ingresar el numero de iteraciones: ");
    //scanf("%ld", &numeroIteraciones);

    #pragma omp parallel private(idHilo) shared(sumasParciales)
    {
        int idHilo = omp_get_thread_num();
        sumasParciales[idHilo] = 0.0;
        #pragma omp for
        for(long indice = 0; indice < numeroIteraciones; indice++){
            if(indice % 2 == 0){
                if(omp_get_thread_num()==0){
                    std::cout<<" (0)thread num = " << omp_get_thread_num() << std::endl;
                    std::cout<<"(0)indice = " << indice << std::endl;
                    std::cout<<"(0)even"<<endl;
                }
                if(omp_get_thread_num()==1){
                    std::cout<<" (1)thread num = " << omp_get_thread_num() << std::endl;
                    std::cout<<"(1)indice = " << indice << std::endl;
                    std::cout<<"(1)even"<<endl;
                }
                sumasParciales[idHilo] += 4.0 / (2.0 * indice + 1.0);
            }
            else{
                if(omp_get_thread_num()==0){
                    std::cout<<" (0)thread num = " << omp_get_thread_num() << std::endl;
                    std::cout<<"(0)indice = " << indice << std::endl;
                    std::cout<<"(0)odd"<<endl;
                }
                if(omp_get_thread_num()==1){
                    std::cout<<" (1)thread num = " << omp_get_thread_num() << std::endl;
                    std::cout<<"(1)indice = " << indice << std::endl;
                    std::cout<<"(1)odd"<<endl;
                }
                sumasParciales[idHilo] -= 4.0 / (2.0 * indice + 1.0);
                
            }
        }
    }

    #pragma omp for
    for(int indice = 0; indice < numeroHilos; indice++){
        respuesta += sumasParciales[indice];
    }

    printf("La respuesta es: %.8f\n", respuesta);
    
//#pragma omp for
//    for(int i=0; i<10; i++){
//        cout<< i << endl;
//    }
        
    return 0;
}
