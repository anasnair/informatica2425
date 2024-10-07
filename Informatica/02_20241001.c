/*dato un numero a più cifre eseguire la somma 
delle cifre e stabilire se è divisibile per 3*/

#include <stdio.h>

int main() {
    int numero, somma = 0, cifra;
    printf("Inserisci un numero: ");
    scanf("%d", &numero);

    int temp = numero; // Variabile temporanea per conservare il numero originale

    // Calcolo della somma delle cifre
    while (temp > 0) {
        cifra = temp % 10; // Estrazione dell'ultima cifra
        somma += cifra;    // Aggiunta della cifra alla somma
        temp /= 10;        // Rimozione dell'ultima cifra
    }

    // Verifica se la somma delle cifre è divisibile per 3
    if (somma % 3 == 0) {
        printf("La somma delle cifre di %d è %d e questa è divisibile per 3.\n", numero, somma);
    } else {
        printf("La somma delle cifre di %d è %d e questa non è divisibile per 3.\n", numero, somma);
    }

    return 0;
}
