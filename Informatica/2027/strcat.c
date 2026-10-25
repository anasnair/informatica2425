#include <stdio.h>
#include <string.h>

void strcat2(char *dst, char *s) {
    int i = 0;
    int j = 0;

    while (dst[i] != '\0') {
        i++;
    }

    while (s[j] != '\0') {
        dst[i] = s[j];
        i++;
        j++;
    }

    dst[i] = '\0';
}