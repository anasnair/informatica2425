#include <stdio.h>

int main() {
    int ore1, minuti1, secondi1, ore2, minuti2, secondi2;
    printf("Inserisci il primo orario (ore minuti secondi): ");
    scanf("%d %d %d", &ore1, &minuti1, &secondi1);
    printf("Inserisci il secondo orario (ore minuti secondi): ");
    scanf("%d %d %d", &ore2, &minuti2, &secondi2);

    if (ore1 < ore2 || (ore1 == ore2 && minuti1 < minuti2) || (ore1 == ore2 && minuti1 == minuti2 && secondi1 < secondi2)) {
        printf("Il primo orario (%d:%d:%d) viene prima del secondo (%d:%d:%d).", ore1, minuti1, secondi1, ore2, minuti2, secondi2);
    } else {
        printf("Il secondo orario (%d:%d:%d) viene prima del primo (%d:%d:%d).", ore2, minuti2, secondi2, ore1, minuti1, secondi1);
    }

    return 0;
}
