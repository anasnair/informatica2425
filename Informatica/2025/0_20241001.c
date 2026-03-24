#include <stdio.h>

int main() {
    int num1, num2, num3;
    int min, max;
    float media;

    // Input dei tre numeri
    printf("Inserisci tre numeri: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    // Calcolo del minimo
    min = num1;
    if (num2 < min) min = num2;
    if (num3 < min) min = num3;

    // Calcolo del massimo
    max = num1;
    if (num2 > max) max = num2;
    if (num3 > max) max = num3;

    // Calcolo della media aritmetica
    media = (num1 + num2 + num3) / 3.0;

    // Stampa dei risultati
    printf("Il numero più piccolo è: %d", min);
    printf("Il numero più grande è: %d", max);
    printf("La media aritmetica è: %.2f", media);

    return 0;
}
