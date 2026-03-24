//file con struct

#include <stdio.h>

int main(){
    FILE *file =fopen("dati2.txt", "w");
    persona *p1 = NULL;


    if(file == NULL){
        printf("errore apertura file\n");
        return 1;
    }
    printf("inserisci il nome dello studente")
    fprintf(file, "%s %d %.2f", "luca", 12, 6.5);

    fclose(file);
    return 0;
}