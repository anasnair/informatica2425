/*creata una struct prodotto con nome, id e prezzo
scrivere su file binario una serie di prodotti.
modificare il prezzo di un prodotto dato il suo id*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char nome[50];
    float prezzo;

}prodotto;

void inserisciProdotto(const char *fileName){
    FILE *fp = fopen(fileName, "ab");
    int n;
    prodotto p;

    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    } 
    
    printf("quanti prodotti vuoi inserire?: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("prodotto %d\n", i+1);
        printf("ID: ");
        scanf("%d", &p.id);
        getchar();
        printf("NOME: ");
        scanf("%s", p.nome);
        getchar();
        printf("PREZZO: ");
        scanf("%f", &p.prezzo);
        getchar();

        fwrite(&p, sizeof(prodotto), 1, fp);
    }
    fclose(fp);
}

void stampaProdotto(const char *fileName){
    FILE *fp = fopen(fileName, "rb");
    prodotto p;

    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    } 

    printf("ELENCO PRODOTTI\n");
    while(fread(&p, sizeof(prodotto), 1, fp)==1){
        printf("ID = %d - Nome: %s  - Prezzo: %.2f\n", p.id, p.nome, p.prezzo);
    }
    fclose(fp);
       
}

void cercaProdotto(const char *fileName, int _id){
    FILE *fp = fopen(fileName, "rb");
    prodotto p;
    int trovato;

    if(fp==NULL){
        printf("rubrica vuota\n");
        return;
    } 
    while(fread(&p, sizeof(prodotto), 1, fp)==1 && !trovato){
        if(p.id == _id){
            printf("\ntrovato Nome: %s - Prezzo: %.2f", p.nome, p.prezzo);
            trovato = 1;
        }
    }  
    if(!trovato)
        printf("\nProdotto non trovato");

    fclose(fp);
}

void modificaProdotto(const char *fileName, int _id, float nP){
    FILE *fp = fopen(fileName, "rb+");
    prodotto p;
    
    if(fp==NULL){
        printf("rubrica vuota\n");
        return;
    } 
    while(fread(&p, sizeof(prodotto), 1, fp)==1){
        if(p.id == _id){
            p.prezzo = nP;

            fseek(fp, -sizeof(prodotto), SEEK_CUR);
            fwrite(&p, sizeof(prodotto), 1, fp);
        }
    }
    fclose(fp);  
}

int main(){
    const char *file = "prodotti.dat";
    int scelta, id;
    float nuovoPrezzo;

    do{
        printf("\nMenu rubrica: \n");
        printf("1. aggiungi prodotto\n");
        printf("2. visualizza elenco prodotti\n");
        printf("3. modificare prezzo prodotto\n");
        printf("0. esci\n");
        printf("scelta: \n");
        scanf("%d", &scelta);
        getchar();

        switch (scelta){
            case 1:
                inserisciProdotto(file);
                break;
            case 2:
                stampaProdotto(file);
                break;
            case 3:
                printf("inserisci ID del prodotto: ");
                scanf("%d", &id);
                getchar();
                cercaProdotto(file, id);
                printf("inserisci il nuovo prezzo: ");
                scanf("%f", &nuovoPrezzo);
                getchar();
                modificaProdotto(file, id, nuovoPrezzo);
                break;
            case 0:
            printf("uscita dal programma\n");
                break;
        }
       

    }while(scelta != 0);
}