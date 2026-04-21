#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char telefono[15];
    char sesso; // 'M' o 'F'
} contatto;

// Funzione per verificare se il numero esiste già
int numeroEsiste(const char *telefono) {
    FILE *fp = fopen("rubrica.dat", "rb");
    if (fp == NULL) {
        return 0; // Se il file non esiste, sicuramente il numero non c'è
    }
    contatto c;
    while (fread(&c, sizeof(contatto), 1, fp) == 1) {
        if (strcmp(c.telefono, telefono) == 0) {
            fclose(fp);
            return 1; // Numero trovato
        }
    }
    fclose(fp);
    return 0; // Numero non trovato
}

// Funzione per cercare un contatto per numero
void cercaPerNumero() {
    char num[15];
    printf("Inserisci il numero da cercare: ");
    scanf("%14s", num);

    FILE *fp = fopen("rubrica.dat", "rb");
    if (fp == NULL) {
        printf("Rubrica vuota\n");
        return;
    }

    contatto c;
    int trovato = 0;
    while (fread(&c, sizeof(contatto), 1, fp) == 1) {
        if (strcmp(c.telefono, num) == 0) {
            printf("Contatto trovato:\n");
            printf("Nome: %s | Telefono: %s | Sesso: %c\n", c.nome, c.telefono, c.sesso);
            trovato = 1;
            break;
        }
    }
    if (!trovato) {
        printf("Nessun contatto trovato con questo numero.\n");
    }
    fclose(fp);
}

// Aggiungi contatto con verifica del numero
void aggiungiContatto() {
    FILE *fp = fopen("rubrica.dat", "ab");
    if (fp == NULL) {
        printf("Errore apertura file\n");
        return;
    }

    contatto c;
    printf("Inserisci nome: ");
    scanf("%29s", c.nome);
    printf("Inserisci telefono: ");
    scanf("%14s", c.telefono);

    // Controllo se il numero esiste già
    if (numeroEsiste(c.telefono)) {
        printf("Il numero %s è già presente in rubrica. Impossibile aggiungerlo.\n", c.telefono);
        fclose(fp);
        return;
    }

    printf("Inserisci sesso (M/F): ");
    scanf(" %c", &c.sesso); // spazio prima di %c per catturare eventuali spazi

    fwrite(&c, sizeof(contatto), 1, fp);
    fclose(fp);
}

// Restanti funzioni invariata...

void stampaContatti() {
    FILE *fp = fopen("rubrica.dat", "rb");
    if (fp == NULL) {
        printf("Rubrica vuota\n");
        return;
    }

    contatto c;
    printf("\n--- RUBRICA ---\n");
    while (fread(&c, sizeof(contatto), 1, fp) == 1) {
        printf("Nome: %s | Telefono: %s | Sesso: %c\n", c.nome, c.telefono, c.sesso);
    }

    fclose(fp);
}

// La funzione eliminaContatto() e separaPerSesso() restano uguali...

void eliminaContatto() {
    FILE *fp = fopen("rubrica.dat", "rb");
    if (fp == NULL) {
        printf("Errore apertura file\n");
        return;
    }

    FILE *fpTmp = fopen("temp.dat", "wb");
    if (fpTmp == NULL) {
        printf("Errore creazione file temporaneo\n");
        fclose(fp);
        return;
    }

    char cerca[30];
    printf("Inserisci il nome da eliminare: ");
    scanf("%29s", cerca);

    contatto c;
    int trovato = 0;
    while (fread(&c, sizeof(contatto), 1, fp) == 1) {
        if (strcmp(c.nome, cerca) == 0) {
            printf("Contatto trovato e eliminato: %s\n", c.nome);
            trovato = 1;
            // Non scrivere nel file temporaneo per eliminare
        } else {
            fwrite(&c, sizeof(contatto), 1, fpTmp);
        }
    }

    fclose(fp);
    fclose(fpTmp);

    // Ricopia il file temporaneo sul file originale
    remove("rubrica.dat");
    rename("temp.dat", "rubrica.dat");
}

void separaPerSesso() {
    FILE *fp = fopen("rubrica.dat", "rb");
    if (!fp) { printf("Rubrica vuota\n"); return; }

    FILE *m = fopen("maschi.dat", "wb");
    FILE *femm = fopen("femmine.dat", "wb");
    if (!m || !femm) {
        printf("Errore creazione file\n");
        fclose(fp);
        if (m) fclose(m);
        if (femm) fclose(femm);
        return;
    }

    contatto c;
    while (fread(&c, sizeof(c), 1, fp))
        if (c.sesso == 'M' || c.sesso == 'm') fwrite(&c, sizeof(c), 1, m);
        else if (c.sesso == 'F' || c.sesso == 'f') fwrite(&c, sizeof(c), 1, femm);

    fclose(fp); fclose(m); fclose(femm);
    printf("Separazione completata.\n");
}

int main() {
    int scelta;

    do {
        printf("\n--- Menu rubrica ---\n");
        printf("1. Aggiungi contatto\n");
        printf("2. Visualizza contatti\n");
        printf("3. Elimina contatto\n");
        printf("4. Separa i contatti in base al sesso\n");
        printf("5. Cerca contatto per numero\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                aggiungiContatto();
                break;
            case 2:
                stampaContatti();
                break;
            case 3:
                eliminaContatto();
                break;
            case 4:
                separaPerSesso();
                break;
            case 5:
                cercaPerNumero();
                break;
            case 0:
                printf("Uscita in corso...\n");
                break;
            default:
                printf("Scelta non valida\n");
        }
    } while (scelta != 0);

    return 0;
}