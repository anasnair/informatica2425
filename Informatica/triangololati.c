#include <stdio.h>

int main() {
    int lato1, lato2, lato3;
    printf("Inserisci tre numeri: ");
    scanf("%d %d %d", &lato1, &lato2, &lato3);

    if (lato1 + lato2 > lato3 && lato1 + lato3 > lato2 && lato2 + lato3 > lato1) {
        printf("I numeri %d, %d, %d possono essere i lati di un triangolo.\n", lato1, lato2, lato3);
    } else {
        printf("I numeri %d, %d, %d non possono essere i lati di un triangolo.\n", lato1, lato2, lato3);
    }

    return 0;
}
