/*Scrivere un programma che letto due orari
in ore, minuti e secondi restituisce quale orario viene prima.*/

#include <stdio.h>
int main(){
    int ore1, min1, sec1;
    int ore2, min2, sec2;

    printf("inserisci il primo orario: ");
    scanf("%d%d%d", &ore1, &min1, &sec1);
    printf("inserisci il secondo orario: ");
    scanf("%d%d%d", &ore2, &min2, &sec2);

    if(ore1>ore2){
        printf("il primo orario viene prima.");
    
    }
    else if(ore1<ore2){
      printf("il secondo orario viene prima.");
    }
        if(min1>min2){
            printf("il primo orario viene prima.");
        }
        else if(min1<min2){
            printf("il secondo orario viene prima.");
        }
            if(sec1>sec2){
                printf("il primo orario viene prima.");
            }
            else if(sec1<sec2){
                printf("il secondo orario viene prima.");
            }
            else{
                printf("i due orari sono uguali.");
                }
    
 }
