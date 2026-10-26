/*Realizza un programma che gestisca un array di 15 elementi interi, il programma dopo aver dichiarato il vettore deve inizializzarlo con valori random compresi tra 1 e 25 (estremi compresi).
Una volta inizializzato richiama le seguenti funzioni dopo averle preparate con il prototipo nel file array_lib.h e le funzioni nel file array_lib.c:*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "array_lib.h"

#define DIM 15

int main(){
    int vet[DIM];

    srand(time(NULL));

    for (int i = 0; i < DIM; i++) {
        vet[i] = rand() % 25 + 1;
    }

    printf("Vettore iniziale:\n");
    stampaVettore(vet, DIM);

    trovavaloreMassimo(vet, DIM);

    int valore;
    printf("Inserisci un valore da contare (tra 1 e 25): ");
    scanf("%d", &valore);

    int occorrenze = contaValore(vet, DIM, valore);
    printf("Il valore %d compare %d volte nel vettore.\n", valore, occorrenze);

    int src;
    int sost;

    printf("Inserisci il valore da ricercare: ");
    scanf("%d", &src);

    printf("Inserisci il valore sostitutivo: ");
    scanf("%d", &sost);


    return 0;
}