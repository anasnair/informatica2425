/*creare una rubrica che gestisca la memorizzazione 
dei contatti e ne visualizzi l'elenco*/

#include <stdio.h>
typedef struct{
    char nome[30];
    char telefono[15];
}contatto;

void aggiungiContatto(contatto c){
    FILE *fp= fopen("numeri.bin", "ab");

    if(fp==NULL){
        printf("errore apertura file\n");
        return
    }

    Contatto c;
    printf("inserisci nome: \n");
    scanf("%[^\n]", c.nome);
    printf("inserisci telefono: \n");
    scanf("%[^\n]", c.telefono);

    fwrite(&c,sizeof(contatto), 1, fp);
    fclose(fp);
}

void stampaContatti(){
    FILE *fp= fopen("numeri.bin", "rb");
    
    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    }

    contatto c;
    printf("\n---RUBRICA---\n");
    while(fread(&c,sizeof(contatto), 1, fp)==1){
        printf("nome: %[^\n]", c.nome);
        printf("telefono: %[^\n]", c.telefono);
    }

    fclose(fp);
}

int main(){
    int scelta;

    do{
        printf("\nMenu rubrica: \n");
        printf("1. aggiungi contatto\n");
        printf("2. visualizza contatti\n");
        printf("0. esci\n");
        printf("scelta: \n");
        scanf("%d", &scelta);

        switch(scelta){
            case 1:
                aggiungiContatto();
                break;
            case 2:
                stampaContatti();
                break;
            case 0:
                printf("uscita in corso...\n");
                exit(1);
            default:
                printf("scelta non valida\n");
        }

    }while(scelta !=0);
}