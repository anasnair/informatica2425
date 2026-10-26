
#include <stdbool.h>
#include <stdio.h>

#define DIM 5

int scacchieraM(int DIM, int _m[DIM][DIM]) {
  int i, j;

  for (i = 0; i < DIM; i++) {
    for (j = 0; j < DIM; j++) {
      if (_m[i][j] != (i + j) % 2)
        return 1;
    }
  }

  return 0;
}


