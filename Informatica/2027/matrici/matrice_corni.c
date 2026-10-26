/*corniceValoreM(): dice se tutti gli elementi della cornice della matrice quadrata di interi
 valgono v;*/

 
#include <stdio.h>
#define DIM 5

int corniceValoreM(int m[DIM][DIM], int n, int v) {
    int i, j;
    for (i = 0; i < n; i++) {
        if (m[0][i] != v || m[n - 1][i] != v) {
            return 0; 
        }
    }
    for (j = 1; j < n - 1; j++) {
        if (m[j][0] != v || m[j][n - 1] != v) {
            return 0; 
        }
    }
    return 1; 
}
