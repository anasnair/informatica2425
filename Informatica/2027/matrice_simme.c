#include <stdio.h>

#define DIM 3

void riempiSimmetrica(int m[][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            if (i <= j)
                m[i][j] = i + j + 1;
            else
                m[i][j] = m[j][i];
        }
    }
}

void stampaMatrice(int m[][DIM]) {
    for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++)
            printf("%3d ", m[i][j]);
        printf("\n");
    }
}

int main() {
    int m[DIM][DIM];

    riempiSimmetrica(m);
    stampaMatrice(m);

    return 0;
}