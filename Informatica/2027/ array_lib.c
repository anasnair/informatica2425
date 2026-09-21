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