/*stampa la matrice*/

#include <stdio.h>

#define DIM 3

void printMatrix(int righe, int colonne, int m[righe][colonne]) {
	for (int i = 0; i < righe; i++) {
		for (int j = 0; j < colonne; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
}

int main(){
	int m[DIM][DIM] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};

	printMatrix(DIM, DIM, m);
	return 0;
}