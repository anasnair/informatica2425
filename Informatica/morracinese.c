/*Gioco
della Morra cinese: supponendo sasso=1, carta=2, forbice=3, chiedere
all’utente la sua scelta e far generare al computer la sua.
Stabilire il vincitore.
N.B.:per chi non conoscesse il gioco: sasso vince forbice, sasso perde carta, carta perde forbice.*/

#include <stdio.h>
int main(){
    srand(time(NULL));
    int sceltautente=0, sceltacomputer=0;

    sceltacomputer = rand()%3+1;
    printf("scegli tra sasso=1, carta=2, forbice=3:");
    scanf("%d", &sceltautente);

    if(sceltautente==1 || sceltautente==2 || sceltautente==3){
        if(sceltacomputer==sceltautente){
            pritnf("pareggio.");
        }else if(sceltautente == 1 && sceltacomputer==3){
            print("hai vinto.");
        }else if(sceltautente == 2 && sceltacomputer==1){
            print("hai vinto.");
        }else if(sceltautente == 3 && sceltacomputer==2){
            print("hai vinto.");
        }
    }else{
            printf("scelta non valida.");
    }
}