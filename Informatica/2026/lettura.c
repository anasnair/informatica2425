//lettura

#include <stdio.h>

int  main(){
    FILE *file = fopen("dati2.txt", "r");
    char nome[100];
    int eta;
    float media;

    if(file == NULL){
        printf("errore apertura file\n");
        return 1;
    }
    fscanf(file, "%s %d %f", nome, &eta, &media);

    printf("Nome: %s eta: %d media: %.2f", nome, eta, media);

    fclose(file);
    return 0;
}
