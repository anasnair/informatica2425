/*
    Realizzare il programma per il gioco CatchThePin.
    Lo scopo del gioco è indovinare un codice a 5 cifre casuali comprese tra 0 e 9 generate random
    dal computer.
    Ogni volta all'utente viene richiesto di inserire i 5 numeri, viene verificata la sequenza
    e vengono stampati i numeri con il seguente schema:
    - se numero è corretto viene visualizzato il numero.
    - se numero non è corretto viene visualizzato un '?'
    Il gioco conta i tentativi utilizzati per indovinare l'intero codice, ovviamente il gioco
    termina quando l'utente ha indovinato tutte e 5 le cifre.

    Realizzare quindi il gioco per funzioni:
    - creaCodiceSegreto.
    - richiediCodiceUtente.
    - verificaStampaCodice.
    il tutto inserito in un ciclo do-while per la ripetizione finche codice non è esatto.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creaCodiceSegreto(int codiceSegreto[5]) {
    for (int i = 0; i < 5; i++) {
        codiceSegreto[i] = rand() % 10;
    }
}

void richiediCodiceUtente(int codiceUtente[5]) {
    printf("Inserisci 5 cifre (da 0 a 9):\n");
    for (int i = 0; i < 5; i++) {
        scanf("%d", &codiceUtente[i]);
    }
}

int verificaStampaCodice(int codiceSegreto[5], int codiceUtente[5]) {
    int codiceEsatto = 1;

    for (int i = 0; i < 5; i++) {
        if (codiceSegreto[i] == codiceUtente[i]) {
            printf("%d", codiceUtente[i]);
        } else {
            printf("?");
            codiceEsatto = 0;
        }
    }
    printf("\n");
    return codiceEsatto;
}

int main() {
    int codiceSegreto[5];
    int codiceUtente[5];
    int tentativi = 0;
    int indovinato;

    srand((unsigned int)time(NULL));
    creaCodiceSegreto(codiceSegreto);

    do {
        richiediCodiceUtente(codiceUtente);
        tentativi++;
        indovinato = verificaStampaCodice(codiceSegreto, codiceUtente);
    } while (!indovinato);

    printf("Hai indovinato il codice in %d tentativi!\n", tentativi);

    return 0;
}
