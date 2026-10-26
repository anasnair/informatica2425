/*Crea un nuovo file .c
Dichiara un Array altezza di 5 elementi, usa una DIM.
Inizializza l'Array, tutti i valori iniziali devono essere 0.
Procedi ad un popolamento manuale dell'Array.
Stampa i valori presenti nell'Array, così verifichi l'avvenuto input.
Compila gcc nome_file.c ed esegui ./a.out, funziona?
Se si: allora Modifica la DIM da 5 a 10, ricompila ed esegui, tutti i cicli si sono adeguati?*/

/*Calcola e stampa l'altezza minima presente nell'Array.
Calcola e stampa l'altezza media presente nell'Array.
Richiedi in input un'altezza, calcola e comunica quante volte compare nell'Array.
Avendo calcolato precedentemente l'altezza media, calcola e comunica in quali celle è presente un valore inferiore all'altezza media.*/


#include <stdio.h>
#define DIM 10

int main(){
    int altezza[DIM];
    int i;
    int min;
    int src;
    int conteggio = 0;

    for(i=0; i<DIM;i++){
        altezza[i]=0;
    }

    for(i=0; i<DIM;i++){
        printf("inserisci il valore %d: ", i+1);
        scanf("%d", &altezza[i]);
    }

    for(i=0; i<DIM; i++){
        printf("%d ", altezza[i]);
    }
    printf("\n");

    min = altezza[0]; 
    for(i=1; i<DIM; i++){
        if(altezza[i] < min)
        min = altezza[i];
    }

    int totale = 0;
    float media = 0;
    for(i=0; i<DIM; i++){
        totale = totale + altezza[i];
    }
    media = (float) totale / DIM;

    printf("Altezza minima: %d\n", min);
    printf("Altezza media: %.2f\n", media);

    printf("Inserisci un'altezza da cercare: ");
    scanf("%d", &src);

    for(i=0; i<DIM; i++){
        if(altezza[i] == src)
            conteggio++;
    }

    if(conteggio > 0)
        printf("Valore %d presente nell'Array %d volte.\n", src, conteggio);
    else
        printf("Valore %d non presente nell'Array.\n", src);

    printf("Celle con un valore inferiore alla media: ");
    for(i=0; i<DIM; i++){
        if(altezza[i] < media)
            printf("%d ", i);
    }
    printf("\n");

}

