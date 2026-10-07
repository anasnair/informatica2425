// Includi tutte le librerie necessarie e il file lib.h dei prototipi.
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "array_lib.h"

void inizializza(int vett[], int dimensione) {
	for (int i = 0; i < dimensione; i++) {
		vett[i] = 0;
	}
}

void inserisciValori(int vett[], int dimensione) {
	for (int i = 0; i < dimensione; i++) {
		printf("Inserisci il valore %d: ", i + 1);
		scanf("%d", &vett[i]);
	}
}

void stampaColonna(const int vett[], int dimensione) {
    for (int i = 0; i < dimensione; i++) {
        printf("%d\n", vett[i]);
    }
}

void stampaVettore(int vet[], int dim) {
    for (int i = 0; i < dim; i++) {
        printf("%d ", vet[i]);
    }
    printf("\n");
}

void trovavaloreMassimo(int vet[], int dim) {
    int massimo = vet[0];

    for (int i = 1; i < dim; i++) {
        if (vet[i] > massimo) {
            massimo = vet[i];
        }
    }

    printf("Valore massimo: %d\n", massimo);
}

int contaValore(int vet[], int dim, int valore) {
    int conteggio = 0;

    for (int i = 0; i < dim; i++) {
        if (vet[i] == valore) {
            conteggio++;
        }
    }

    return conteggio;
}

void caricaVettore(int _vet[], int _dim, int _min, int _max) {
    srand(time(NULL));
    for (int i = 0; i < _dim; i++) {
        _vet[i] = rand() % (_max - _min + 1) + _min;
    }
}

float mediaVettore(int _vet[], int _dim){
    int totale = 0;
    for(int i=0;i<_dim;i++){
        totale = totale + _vet[i];
    }
    return ((float)totale)/_dim;
}

int getValoreAt(int _vet[], int _dim, int _index){
    if(_index >= 0 && _index < _dim)
        return _vet[_index];
     else 
        return -1; 
    
}

 bool stampaSubArray(int _vet[], int _dim, int _index1, int _index2){
    if (_index1 < 0 || _index1 >= _dim ) {
        return false; 
    }
    if (_index2 < 0 || _index2 >= _dim ) {
        return false; 
    }
    if (_index1 > _index2 ) {
        return false; 
    }

    if (_index1 == _index2 ) {
        return false; 
    }

    for (int i = _index1; i <= _index2; i++) {
        printf("%d ", _vet[i]);
    }
    return true;
 }

 void bubbleSort(int vett[], int dim, int _mode){
    int temp;
    int flag = 0;
    int i = 0;

    while (flag == 0) {
        flag = 1;
        for (int j = 0; j < dim - 1 - i; j++) {
            if (_mode == 1) {
                if (vett[j] < vett[j + 1]) {
                    flag = 0;
                    temp = vett[j];
                    vett[j] = vett[j + 1];
                    vett[j + 1] = temp;
                }
            } else {
                if (vett[j] > vett[j + 1]) {
                    flag = 0;
                    temp = vett[j];
                    vett[j] = vett[j + 1];
                    vett[j + 1] = temp;
                }
            }
        }
        i++;
    }
}

 /*---------------------------------MATRICI---------------------------------------*/

void caricaMatrice(int _rows, int _cols, int _m[_rows][_cols]) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _m[i][j] = 1 + rand() % 25;
        }
    }
}

void stampaMatrice(int _rows, int _cols, int _m[_rows][_cols]) {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            printf("%3d ", _m[i][j]);
        }
        printf("\n");
    }
}

int scacchiera(int _rows, int _cols, int _m[_rows][_cols]) {
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      if (_m[i][j] != (i + j) % 2)
        return 1;
    }
  }

  return 0;
}


int maxSumM(int _rows, int _cols, int _m[_rows][_cols], int *somma) {
    int max = _m[0][0];
    int totale = 0;

    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            if (_m[i][j] > max) {
                max = _m[i][j];
            }
            totale += _m[i][j];
        }
    }

    *somma = totale;
    return max;
}   

