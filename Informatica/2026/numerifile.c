/* scrivere una funzione che preso in ingresso il nome del file contenente interi,lo modifichi in 
modo tale da contenere gli stessi numeri ma ordinati in senso decrescente
*/

#include <stdlib.h>
#include <stdio.h>

void OrdinaFile(char nomeFile[]){
    FILE *Fp;
    int vett[100], i=0;

    Fp=fopen(nomeFile, "r");
    if(Fp==NULL){
        printf("errore di apertura\n");
        return 1;
    }
    //lettura dei numeri dal file
    while(fscanf(Fp, "%d", &vett[i])==1){      
        printf("elemento %d: %d", i+1, vett[i]);
        i++;
    }
    fclose(Fp);
}

int main(){
    char nome[20];

    printf("inserisci il nome del file: ");
    scanf("%s", nome);

    OrdinaFile(nome);
}