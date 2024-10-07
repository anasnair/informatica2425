#include <stdio.h>

int main() {
    int numero;
    printf("Inserisci un numero minore di 10.000: ");
    scanf("%d", &numero);

    if (numero >= 10000) {
        printf("Il numero deve essere minore di 10.000.\n");
    }

    // Separazione delle cifre
    int migliaia = numero / 1000;
    int centinaia = (numero / 100) % 10;
    int decine = (numero / 10) % 10;
    int unita = numero % 10;

    // Visualizzazione dei risultati
    printf("Migliaia: %d", migliaia);
    printf("Centinaia: %d", centinaia);
    printf("Decine: %d", decine);
    printf("Unità: %d", unita);

    return 0;
}

