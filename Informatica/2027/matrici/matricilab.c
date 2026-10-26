#include <stdio.h>
#include "array_lib.h"

#define DIM 10
#define ROWS 5      // Numero di righe della matrice
#define COLS 5      // Numero di colonne della matrice

int main(){

    int matrice[ROWS][COLS];

    caricaMatrice(ROWS, COLS, matrice);
    stampaMatrice(ROWS, COLS, matrice);
    
    return 0;
}