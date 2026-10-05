
#include <stdio.h>
#define DIM 5

int maxSumM(int _m[DIM][DIM], int *somma) {
    int max = _m[0][0];
    int totale = 0;

    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (_m[i][j] > max) {
                max = _m[i][j];
            }
            totale += _m[i][j];
        }
    }

    *somma = totale;
    return max;
}