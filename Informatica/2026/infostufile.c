/*inserire le informazioni di studenti:
nome -eta  -media voti scolastici
determinare lo studente
con la media scolastica piu alta*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Studente{
    char nome[20];
    int eta;
    float media;

}Studente;

void scriveStudenti(char *nome_file, int n_studenti){
    FILE *f= fopen(nome_file, "ab");
    if(f == NULL){
        printf("errore nel apertura file.");
        return;
    }
    for(int i=0; i<n_studenti;i++){
        Studente s;
        printf("inserisci nome studente %d", i+1);
        scanf("%49s", s.nome);
        getchar();

        printf("inserisci eta studente %d", i+1);
        scanf("%49s", s.eta);
        getchar();

        printf("inserisci media studente %d", i+1);
        scanf("%49s", s.media);
        getchar();
        fwrite(&s, sizeof(Studente), 1, f);
    }
    fclose(f);
    if(ferror(f)){
        printf("errore nella chiusura file...\n");
    }
}

Studente* leggiStudenti(char *nome_file, Studente *array){
    FILE* f= fopen(nome_file, "rb");
    if(f == NULL){
        printf("errore nel apertura file.");
        return array;
    }
    int i=0;
    array = (Studente*)realloc(array, sizeof(Studente));
    if(array == NULL){
        printf("errore allocazione\n");
        return array;
    }
    while(fread(&array[i],sizeof(Studente),1,f) != 0){
        i++;
        array = (Studente*)realloc(array, (i+1) * sizeof(Studente));
        if(array == NULL){
            printf("errore allocazione\n");
            return array;
    }
    }
    array = (Studente*)realloc(array,i * sizeof(Studente));
        if(array == NULL){
            printf("errore allocazione\n");
            return array;
    }
    fclose(f);
    if(ferror(f)){
        printf("errore nella chiusura file...\n");
    }
    return array;
}

Studente trova_migliore(Studente *array){
    int dim = sizeof(array) / sizeof(Studente);
    Studente best = {"", 0, 0};

    for(int i=0; i<dim; i++){
        if(array[i].media > best.media){
            best.media = array[i].media;
            best.eta = array[i].eta;
            strcpy(best.nome, array[i].nome);
        }
    }
    return best;
}

int main(){
    int scelta;
    Studente *array = NULL;
    do{
        printf("1. inserisci studenti\n");
        printf("2. leggi studenti\n");
        printf("3. trova migliore\n");
        printf("4. esci\n");
        printf("inserisci scelta: ");
        scanf("%d", &scelta);
        switch(scelta){
            case 1:
                scriveStudenti("studenti.dat", 3);
                break;
            case 2:
                array = leggiStudenti("studenti.dat", array);
                break;
            case 3:
                if(array != NULL){
                    Studente best = trova_migliore(array);
                    printf("Migliore studente: %s, eta: %d, media: %.2f\n", best.nome, best.eta, best.media);
                } else {
                    printf("Nessuno studente trovato. Leggi prima gli studenti.\n");
                } 
        }
    }
}  