/*Scrivi un programma in C che permetta di inserire 1 voto di uno studente.
Poi genera casualmente un secondo voto compreso tra 4 e 8.
Quindi permetta di scegliere quale operazione fare tra:
- 1 mostrare la media dei due voti
- 2 mostrare il voto maggiore tra i due
- 3 mostrare il voto minore tra i due.
- 4 mostrare il numero di voti sufficiente tra i due.
Verificare che il voto inserito sia compreso tra 2 e 10.*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){
    float voto1=0;
    float voto2=0;
    int scelta=0;
    int sufficienti=0;

printf("inserisci un voto (voto deve essere compreso tra 2 e 10): ");
    scanf("%f", &voto1);

    srand(time(NULL));
    voto2=rand()%5+4;

    if(voto1<2 || voto1>10){
        printf("voto non valido\n");
        return 0;
    }

    printf("\nScegli operazione:\n");
    printf("1 - media dei voti\n");
    printf("2 - voto maggiore\n");
    printf("3 - voto minore\n");
    printf("4 - numero voti sufficienti\n");
    scanf("%d", &scelta);

    if(scelta == 1){
        printf("La media e': %.2f\n", (voto1+voto2)/2);
    }
    if(scelta == 2){
        if(voto1 > voto2){
            printf("Il voto maggiore e': %.2f\n", voto1);
        }else{
            printf("Il voto maggiore e': %.2f\n", voto2);
        }
    }
    if(scelta == 3){
        if(voto1 < voto2){
            printf("Il voto minore e': %.2f\n", voto1);
        }else{
            printf("Il voto minore e': %.2f\n", voto2);
        }
    }
    if(scelta == 4){
        if(voto1 >= 6){
            sufficienti = sufficienti + 1;
        }
        if(voto2 >= 6){
            sufficienti = sufficienti + 1;
        }
        printf("I voti sufficienti sono: %d\n", sufficienti);
    }
    return 0;
}
 
