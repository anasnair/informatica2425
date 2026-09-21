/*Nel main program, dichiara un vettore vett di 10 elementi definendo una DIM
-Con apposita funzione inizializza il vettore (tutte le celle a 0).
-Con apposita funzione procedi ad un input manuale dei valori nel vettore.
-Con apposita funzione stampa tutti i valori in colonna.*/

#include <stdio.h>

#define DIM 10

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

int main() {
	int vett[DIM];

	inizializza(vett, DIM);
	inserisciValori(vett, DIM);
	stampaColonna(vett, DIM);

	return 0;
}

