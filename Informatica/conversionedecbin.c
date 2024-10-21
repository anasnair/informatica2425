/*convertire un numero da decimale a binario 
introducendo un valore da 0 a 63*/

#include <stdio.h>
int main(){
        int n0=0;
        int n1=0;
        int n2=0;
        int n3=0;
        int n4=0;
        int n5=0;
        int num=0;
        int quoz=0;

        printf("inserisci un numero compreso tra 0 e 63: ");
        scanf("%d", &num);
        quoz=num;
        if(num>=0 && num<=63){
            if(quoz!=0){
                n0=quoz%2;
                quoz=quoz/2;
            

            }
            if(quoz!=0){
                n1=quoz%2;
                quoz=quoz/2;
            

            }
            if(quoz!=0){
                n2=quoz%2;
                quoz=quoz/2;
            

            }
            if(quoz!=0){
                n3=quoz%2;
                quoz=quoz/2;
        

            }
            if(quoz!=0){
                n4=quoz%2;
                quoz=quoz/2;
            

            }
            if(quoz!=0){
                n5=quoz%2;
                quoz=quoz/2;
            }

            printf("\nil numero decimale %d inbinario vale: %d%d%d%d%d%d", num, n5, n4, n3, n2, n1, n0);



        }
        else
            printf("\n il valore inserito non rispetta la richiesta.");
        
    

}