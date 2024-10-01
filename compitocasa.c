/* Verificare se un numero dato
  in input è divisibile sia per 3 sia per 
*/

#include <stdio.h>
    int main(){
        int numero=0;
         
         
         
         printf("Inserisci un numero: ");
         scanf("%d", &numero);
    if (numero % 3 == 0 && numero % 5 == 0) {
        printf("Il numero %d è divisibile sia per 3 che per 5.",  numero);
    }
     else {
        printf("Il numero %d NON è divisibile sia per 3 che per 5.", numero);
    }

 }