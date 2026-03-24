/*STABILIRE SE DATI DUE NUMERI A e B CONTROLLARE SE
 A è MINORE, UGUALE o MAGGIORE DI B*/

 #include <stdio.h>
 int main(){
    int a=0;
    int b=0;
    printf("inserisci il primo numero: ");
    scanf("%d", &a);
    printf("inserisci il secondo numero: ");
    scanf("%d", &b);
    if (a>b){
        printf("a è maggiore di b");
    }
      else{
        if (a<b){
            printf("a è minore di b");
            
        }
        else{
            if (a==b){
                printf("a è uguale di b");
            }
            
                
            }
      }                
 }
    
 
