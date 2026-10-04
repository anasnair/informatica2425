
#include <stdio.h>

void scacchieraM(int _rows, int _cols, int _m[_rows][_cols]){
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            _m[i][j] = (i + j) % 2;
        }
    }
}


