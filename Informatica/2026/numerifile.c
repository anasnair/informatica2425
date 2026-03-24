/* scrivere una funzione che preso in ingresso il 
nome del file contenente interi,lo modifichi in 
modo tale da contenere gli stessi numeri ma
 ordinati in senso decrescente
*/

#include <stdlib.h>
#include <stdio.h>

void OrdinaFile(char nomeFile[]){
    FILE *Fp;
    int vett[100], i,j,temp,n=0;

    Fp=fopen(nomeFile, "r");
    if(Fp==NULL){
        printf("errore di apertura\n");
        exit(1);
    }
    //lettura dei numeri dal file
    while(fscanf(Fp, "%d", &vett[n])==1){
        printf("elemento %d: %d", n+1, vett[n]);
        n++;
    }
    fclose(Fp);

    //ordinamento del bubble sort
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(vett[i]<vett[j]){
                temp=vett[i];
                vett[i]=vett[j];
                vett[j]=temp;
            }
        }
    }
    /riapriamo il file per scriverci i numeri ordinati/
    Fp=fopen(nomeFile, "w");
    if(Fp==NULL){
        printf("errore di apertura\n");
        exit(1);
    }
    for(i=0;i<n;i++){
        fprintf(Fp,"%d ",vett[i]);
    }
    fclose(Fp);
    Fp=fopen(nomeFile, "r");
    if(Fp==NULL){
        printf("errore di apertura\n");
        exit(1);
    }
    n=0;
    //lettura dei numeri dal file
    while(fscanf(Fp, "%d", &vett[n])==1){
        printf("elemento %d: %d", n+1, vett[n]);
        n++;
    }
    fclose(Fp);
}

int main(){
    char nome[20];

    printf("inserisci il nome del file: ");
    scanf("%s", nome);

    OrdinaFile(nome);
}