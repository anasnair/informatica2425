#include <stdio.h>
#include "array_lib.h"

#define DIM 10

int main(){
    int vet[DIM];
    
    caricaVettore(vet, DIM, 1, 50);
    stampaVettore(vet, DIM);
    printf("\n");
    printf("valore medio del vettore: %.2f\n", mediaVettore(vet, DIM))
    return 0;
}