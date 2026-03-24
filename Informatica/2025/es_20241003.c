#include <stdio.h>

int main() {
    int n1, n2, n3, n4, n5, temp;
    printf("Inserisci il primo valore: ");
    scanf("%d", &n1);
    printf("Inserisci il secondo valore: ");
    scanf("%d", &n2);
    printf("Inserisci il terzo valore: ");
    scanf("%d", &n3);
    printf("Inserisci il quarto valore: ");
    scanf("%d", &n4);
    printf("Inserisci il quinto valore: ");
    scanf("%d", &n5);

    // Ordinamento dei valori in ordine decrescente
    if (n2 > n1) { temp = n1; n1 = n2; n2 = temp; }
    if (n3 > n1) { temp = n1; n1 = n3; n3 = temp; }
    if (n4 > n1) { temp = n1; n1 = n4; n4 = temp; }
    if (n5 > n1) { temp = n1; n1 = n5; n5 = temp; }
    if (n3 > n2) { temp = n2; n2 = n3; n3 = temp; }
    if (n4 > n2) { temp = n2; n2 = n4; n4 = temp; }
    if (n5 > n2) { temp = n2; n2 = n5; n5 = temp; }
    if (n4 > n3) { temp = n3; n3 = n4; n4 = temp; }
    if (n5 > n3) { temp = n3; n3 = n5; n5 = temp; }
    if (n5 > n4) { temp = n4; n4 = n5; n5 = temp; }

    // Stampa dei valori in ordine decrescente
    printf("I valori in ordine decrescente sono: %d %d %d %d %d\n", n1, n2, n3, n4, n5);

    return 0;
}
