/*CREARE UN PROGRAMMA CHE GESTISCA UNA LIBRERIA DOTATA DI DIVERSI LIBRI TALE DA POTER ESEGUIRE LE SEGUENTI OPERAZONI:
- AGGIUNTA/CREAZIONE DELLA LISTA DI LIBRI;
- RICERCA DI UN Libro;
- CANCELLAZIONE DI UN Libro;
- MODIFICA DELL'ISBN;
- SEPARARE LA LISTA DEI LIBRI IN DUE LISTE CONTENENTI RISPETTIVAMENTE I LIBRI CREATI PRIMA DEL 2000 E QUELLI DOPO;
TUTTO VIENE GESTITO DA FILE BINARI*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
      char autore[30];
      char titolo[30];
      int ISBN;
      int anno;
}Libro;

void inseriscilibro(){
    FILE *fp = fopen("libreria.dat", "ab");
    int n;
    Libro p;

    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    } 
    
    printf("quanti libri vuoi inserire?: ");
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        printf("Libro %d\n", i+1);
        printf("ISBN: ");
        scanf("%d", &p.ISBN);
        getchar();
        printf("titolo: ");
        scanf("%[^\n]", p.titolo);
        getchar();
        printf("autore: ");
        scanf("%[^\n]", p.autore);
        getchar();
        printf("anno pubblicazione: ");
        scanf("%d", &p.anno);
        getchar();

        fwrite(&p, sizeof(Libro), 1, fp);
    }
    fclose(fp);
}

void stampaLibro(){
    FILE *fp = fopen("libreria.dat", "rb");
    Libro p;

    if(fp==NULL){
        printf("errore apertura file\n");
        return;
    } 

    printf("ELENCO LIBRI\n");
    while(fread(&p, sizeof(Libro), 1, fp)==1){
        printf("ISBN: %d - titolo: %s - autore: %s  - anno pubblicazione: %d\n", p.ISBN, p.titolo, p.autore, p.anno);
    }
    fclose(fp);
       
}

void cercalibro(){
    FILE *fp = fopen("libreria.dat", "rb");
    Libro p;
    int trovato=0;
    int _id;

    if(fp==NULL){
        printf("libreria vuota\n");
        return;
    } 

    printf("Inserisci l'ISBN del libro da cercare: ");
    scanf("%d", &_id);
    getchar();  

    while(fread(&p, sizeof(Libro), 1, fp)==1 && !trovato){
        if(p.ISBN == _id){
            printf("\ntrovato titolo: %s - autore: %s - anno pubblicazione: %d", p.titolo, p.autore, p.anno);
        }
    }  
    if(!trovato)
        printf("\nlibro non trovato");

    fclose(fp);
}

void eliminalibro(){
    FILE *fp = fopen("libreria.dat", "rb");
    FILE *fpTmp = fopen("temp.dat", "wb");
    char cerca[30];
    Libro p;

    if (fp == NULL) {
        printf("Rubrica vuota!\n");
        return;
    }
    if (fpTmp == NULL) {
        printf("errore sul file temporaneo!\n");
        return;
    }
    printf("Inserisci il titolo: ");
    scanf(" %[^\n]", cerca);
    getchar();

    while( fread(&p, sizeof(Libro), 1, fp) ){
        if ( strcmp(p.titolo,cerca)==0 )
            printf("Trovato!..l'elemento sarà eliminato.\n");
        else
            fwrite(&p, sizeof(Libro), 1, fpTmp);
    }

    fclose(fp);
    fclose(fpTmp);

    fp = fopen("temp.dat", "rb");
    fpTmp = fopen("libreria.dat", "wb");

    while( fread(&p, sizeof(Libro),1, fp) )
        fwrite(&p, sizeof(Libro),1, fpTmp);

    fclose(fp);
    fclose(fpTmp);

}

void modificaIsbn( int _id, float nId){
    FILE *fp = fopen("libreria.dat", "rb+");
    Libro p;
    
    if(fp==NULL){
        printf("libreria vuota\n");
        return;
    } 
    while(fread(&p, sizeof(Libro), 1, fp)==1){
        if(p.ISBN == _id){
            p.ISBN = nId;

            fseek(fp, -sizeof(Libro), SEEK_CUR);
            fwrite(&p, sizeof(Libro), 1, fp);
        }
    }
    fclose(fp);  
}

void separaLibri(){
    FILE *fp = fopen("libreria.dat", "rb");
    FILE *fpF = fopen("ante2000.dat", "ab");
    FILE *fpM = fopen("dos2000.dat", "ab");
    Libro p;

    while( fread(&p, sizeof(Libro), 1, fp) ){
        if( p.anno < 2000)
            fwrite(&p, sizeof(Libro),1, fpF);
        else if ( p.anno >= 2000)
            fwrite(&p, sizeof(Libro),1, fpM);
    }
     fclose(fp);
    fclose(fpF);
    fclose(fpM);

    fpF = fopen("ante2000.dat", "rb");
    fpM = fopen("dos2000.dat", "rb");

    printf("\n --------Rubrica ante2000------\n");
    while( fread(&p, sizeof(Libro), 1, fpF) ){
        printf("titolo: %s, autore: %s, anno: %d\n", p.titolo, p.autore, p.anno);
    }

    printf("\n --------Rubrica dos2000------\n");
    while( fread(&p, sizeof(Libro), 1, fpM) ){
        printf("titolo: %s, autore: %s, anno: %d\n", p.titolo, p.autore, p.anno);
    }
    fclose(fpF);
    fclose(fpM);
}

int main() {
    int scelta;

    do {
        printf("\nMenu Libreria:\n");
        printf("1. Aggiungi libri\n");
        printf("2. Visualizza libri\n");
        printf("3. cerca libri\n");
        printf("4. Elimina libri\n");
        printf("5. Separa i libri in base al anno(ante/dos2000)\n");
        printf("0. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        getchar();

        switch(scelta) {
            case 1:
               inseriscilibro();
                break;
            case 2:
                stampaLibro();
                break;
            case 3:
                cercalibro(); 
                break;
            case 4:
                eliminalibro();
                break;
            case 5:
                separaLibri();
                break;
            case 0:
                printf("Uscita dal programma.\n");
                break;
            default:
                printf("Scelta non valida!\n");
        }
    } while(scelta != 0);

    return 0;
}
