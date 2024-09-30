/*STABILIRE SE UNA PERSONA 
PUO' VOTARE ALLE ELEZIONI*/

#include <stdio.h>
int main(){
    int eta;
    eta=0;
    printf("inserisci la tua eta: ");
    scanf("%d", &eta);
    if (eta>=18){
        printf("puoi votare");
    }
    else{
        printf("non puoi votare");
    }
    
}