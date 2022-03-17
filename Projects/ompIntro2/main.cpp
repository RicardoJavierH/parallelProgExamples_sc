#include <stdio.h>
#include "omp.h"

int main(){
    int numeroHilos = 4, idHilo;
    omp_set_num_threads(numeroHilos);
    double respuesta = 0.0, sumasParciales[numeroHilos];
    long numeroIteraciones = 100000;

    #pragma omp parallel private(idHilo) shared(sumasParciales)
    {
        int idHilo = omp_get_thread_num();
        sumasParciales[idHilo] = 0.0;
        for(long indice = idHilo; indice < numeroIteraciones; indice += numeroHilos){
            if(indice % 2 == 0){
                sumasParciales[idHilo] += 4.0 / (2.0 * indice + 1.0);
            }else{
                sumasParciales[idHilo] -= 4.0 / (2.0 * indice + 1.0);
            }
        }
    }
    for(int indice = 0; indice < numeroHilos; indice++){
        respuesta += sumasParciales[indice];
    }
    printf("La respuesta es: %.8f\n", respuesta);
    return 0;
    
}
