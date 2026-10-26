#include <stdio.h>
#include "array_lib.h"

#define DIM 10

int main(){
    int vett[DIM];
    int tmp;
    int i;

    caricaVett(vett, DIM, 5, 25);
    stampaVett(vett, DIM);
    printf("/n");

    printf("valore medio del vett : %.2f\n", mediaVett(vett, DIM));
    i=7;
    tmp=getValoreAt(vett, DIM, 7);
    if(tmp != -1)
        printf("valore alla cella indice %d: %d\n", i, tmp);
    else    printf("hey, something went wrong!");

    
    
    

}