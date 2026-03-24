#include <stdio.h>

int main() {
    int num1, num2, num3;
    printf("Inserisci tre numeri: ");
    scanf("%d %d %d", &num1, &num2, &num3);

    if ((num2 - num1) == (num3 - num2)) {
        printf("I numeri %d, %d, %d sono in progressione aritmetica.\n", num1, num2, num3);
    } else {
        printf("I numeri %d, %d, %d non sono in progressione aritmetica.\n", num1, num2, num3);
    }

    return 0;
}
