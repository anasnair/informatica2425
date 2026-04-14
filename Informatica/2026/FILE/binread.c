/*leggere un file binario*/

#include <stdio.h>

int main(){
    FILE *fp= fopen("numeri.bin", "wb");
    int numeri[3], i;

    if(fp==NULL){
        printf("errore apertura file\n");
        return -1;
    }

    fread(numeri,sizeof(int), 3, fp);

    for(int i = 0; i<3;i++){
        printf("%d", numeri[i]);
    }

    fclose(fp);
}