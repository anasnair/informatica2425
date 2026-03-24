//file formattato 

#include <stdio.h>

int main(){
    FILE *file =fopen("dati2.txt", "w");


    if(file == NULL){
        printf("errore apertura file\n");
        return 1;
    }
    fprintf(file, "%s %d %.2f", "luca", 12, 6.5);

    fclose(file);
    return 0;
}