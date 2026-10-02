/*scacchieraM(): verifica se una matrice quadrata di interi è una "scacchiera", ovvero se vi sono presenti solo 0 e 1 alternati tra loro;*/

#include <stdio.h>
#include "array_lib.c"

#define DIM 5
#define ROWS 5
#define COLS 5

int main(){

    int mat[ROWS][COLS];

    scacchieraM(ROWS, COLS, mat);
    return 0;

}