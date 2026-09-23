// Includi tutte le librerie necessarie e il file lib.h dei prototipi.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "array_lib.h"

void inizializza(int vett[], int dimensione) {
	for (int i = 0; i < dimensione; i++) {
		vett[i] = 0;
	}
}

void inserisciValori(int vett[], int dimensione) {
	for (int i = 0; i < dimensione; i++) {
		printf("Inserisci il valore %d: ", i + 1);
		scanf("%d", &vett[i]);
	}
}

void stampaColonna(const int vett[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        printf("%d\n", vett[i]);
    }
}

void stampaVettore(int vet[], int dim) {
    for (int i = 0; i < dim; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void trovavaloreMassimo(int vet[], int dim) {
    int massimo = vet[0];

    for (int i = 1; i < dim; i++) {
        if (vet[i] > massimo) {
            massimo = vet[i];
        }
    }

    printf("Valore massimo: %d\n", massimo);
}

int contaValore(int vet[], int dim, int valore) {
    int conteggio = 0;

    for (int i = 0; i < dim; i++) {
        if (vet[i] == valore) {
            conteggio++;
        }
    }

    return conteggio;
}

int ricercaSostituisci(int vet[], int dim, int src, int sost) {
    int sostituzioni = 0;

    for (int i = 0; i < dim; i++) {
        if (vet[i] == src) {
            vet[i] = sost;
            sostituzioni++;
        }
    }

    return sostituzioni;
}