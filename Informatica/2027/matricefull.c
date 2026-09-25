/*stampa una matrice unitaria*/

#include <stdio.h>

#define DIM 3

void matrix_unitaria(int righe, int colonne, int m[righe][colonne]) {
	for (int i = 0; i < righe; i++) {
		for (int j = 0; j < colonne; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int m[DIM][DIM] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
	};

	matrix_unitaria(DIM, DIM, m);
	return 0;
}