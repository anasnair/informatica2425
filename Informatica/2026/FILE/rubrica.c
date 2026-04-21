/*creare una rubrica che gestisca la memorizzazione 
dei contatti e ne visualizzi l'elenco.
aggiungere o creare il file rubrica
stampa lista contatti
elimina un contatto in base al nome
separa il file rubrica in due file in base al sesso*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char nome[30];
    char telefono[15];
    char sesso;
}contatto;

void aggiungiContatto(){
    FILE *fp= fopen("rubrica.dat", "ab");

    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    }

    contatto c;
    printf("inserisci nome: \n");
    scanf("%s", c.nome);
    printf("inserisci telefono: \n");
    scanf("%s", c.telefono);
    printf("inserisci sesso: \n");
    scanf("%c", &c.sesso);


    fwrite(&c,sizeof(contatto), 1, fp);
    fclose(fp);
}

void stampaContatti(){
    FILE *fp= fopen("rubrica.dat", "rb");
    
    if(fp==NULL){
        printf("rubrica vuota\n");
        return;
    }

    contatto c;
    printf("\n---RUBRICA---\n");
    while(fread(&c,sizeof(contatto), 1, fp) != 0){
        printf(" %s", c.nome);
        printf(" %s", c.telefono);
        printf("%c", &c.sesso);
    }

    fclose(fp);
}

void eliminaContatti(){
    FILE *fp= fopen("rubrica.dat", "rb");
    FILE *fpTmp= fopen("temp.dat", "wb");
    char cerca[30];
    contatto c;

    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    }

    if(fpTmp==NULL){
        printf("errore file temporaneo\n");
        return;
    }
    printf("inserisci il nome:");
    scanf("%s", cerca);
    getchar();

    while( fread(&c, sizeof(contatto), 1, fp)){
        if(strcmp(c.nome, cerca)==0)
            printf("trovato! elemento sara eliminato");
        else
            fwrite(&c, sizeof(contatto), 1, fpTmp);
    }

    fclose(fp);
    fclose(fpTmp);

    fp = fopen("temp.dat", "rb");
    fpTmp = fopen("rubrica.dat", "wb");

    while( fread(&c, sizeof(contatto), 1, fp))
        fwrite(&c, sizeof(contatto), 1,fpTmp);
    
    fclose(fp);
    fclose(fpTmp);
}

int main(){
    int scelta;

    do{
        printf("\n---Menu rubrica---\n");
        printf("1. aggiungi contatto\n");
        printf("2. visualizza contatti\n");
        printf("3. elimina contatti\n");
        printf("4. separa i contatti in base al sesso\n");
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
            case 3:
                eliminaContatti();
                break;
            case 0:
                printf("uscita in corso...\n");
                exit(1);
            default:
                printf("scelta non valida\n");
        }

    }while(scelta != 0);
}