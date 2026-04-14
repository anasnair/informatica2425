/*data la struct prodotto:
-nome
-codice
-quantita
-prezzo
eseguire:
1. inserire prodotto
2. stampare elenco prodotti
3. cercare un prodotto per codice
4. calcolare il valore totale del magazzino*/

#include <stdio.h>
#include <string.h>

#define MAX_PRODOTTI 100

typedef struct {
    char nome[50];
    int codice;
    int quantita;
    float prezzo;
} Prodotto;

Prodotto magazzino[MAX_PRODOTTI];
int num_prodotti = 0;

void inserisci_prodotto() {
    if (num_prodotti >= MAX_PRODOTTI) {
        printf("Magazzino pieno!\n");
        return;
    }
    printf("Nome: ");
    scanf("%s", magazzino[num_prodotti].nome);
    printf("Codice: ");
    scanf("%d", &magazzino[num_prodotti].codice);
    printf("Quantita: ");
    scanf("%d", &magazzino[num_prodotti].quantita);
    printf("Prezzo: ");
    scanf("%f", &magazzino[num_prodotti].prezzo);
    num_prodotti++;
    printf("Prodotto inserito!\n");
}

void stampa_prodotti() {
    if (num_prodotti == 0) {
        printf("Magazzino vuoto!\n");
        return;
    }
    for (int i = 0; i < num_prodotti; i++) {
        printf("%d. %s - Cod: %d - Qt: %d - Prezzo: %.2f\n",
               i+1, magazzino[i].nome, magazzino[i].codice,
               magazzino[i].quantita, magazzino[i].prezzo);
    }
}

void cerca_codice() {
    int cod;
    printf("Inserisci codice: ");
    scanf("%d", &cod);
    for (int i = 0; i < num_prodotti; i++) {
        if (magazzino[i].codice == cod) {
            printf("Trovato: %s - Qt: %d - Prezzo: %.2f\n",
                   magazzino[i].nome, magazzino[i].quantita, magazzino[i].prezzo);
            return;
        }
    }
    printf("Prodotto non trovato!\n");
}

void valore_totale() {
    float totale = 0;
    for (int i = 0; i < num_prodotti; i++) {
        totale += magazzino[i].quantita * magazzino[i].prezzo;
    }
    printf("Valore totale magazzino: %.2f\n", totale);
}

int main() {
    int scelta;
    while (1) {
        printf("\n1. Inserisci prodotto\n2. Stampa prodotti\n3. Cerca per codice\n4. Valore totale\n5. Esci\nScelta: ");
        scanf("%d", &scelta);
        switch (scelta) {
            case 1: inserisci_prodotto(); break;
            case 2: stampa_prodotti(); break;
            case 3: cerca_codice(); break;
            case 4: valore_totale(); break;
            case 5: return 0;
            default: printf("Scelta non valida!\n");
        }
    }
}