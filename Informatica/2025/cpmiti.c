/*Creare una sorta di menù( vedi esempio) tramite dei printf per la scelta dell'operazione
da compiere tra due valori generati casualmente( eseguendo lì dove c'è bisogno gli opportuni controlli).
Comunicare il risultato dell'operazione o la scelta dell'utente di non fare niente e uscire dal programma:
ES: "Seleziona l'operazione da eseguire: 
        0.  TERMINA
        1.  SOMMA
        2.  DIFFERENZA
        3.  MOLTIPLICAZIONE
        4.  DIVISIONE  "*/


 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 int main(){
    float num1;
    float num2;
    int scelta;

    printf("------SCEGLI DAL MENù LOPERAZIONE DA FARE------");
    printf(" 0. TERMINA ");
    printf(" 1. SOMMA ");
    printf(" 2. DIFFERENZA ");
    printf(" 3. MOLTIPLICAZIONE ");
    printf(" 4. DIVISIONE ");

    printf("\n scegli loperazione da compiere: ");
    scanf("%d", &scelta);
    srand(time(NULL));
    num1=rand()%50+1;
    num2=rand()%50+1;

    switch(scelta){
        case 0:
            printf("il programma è terminato.");
            break;
        case 1:
            printf("la somma vale: %.2f", num1+num2);
            break;
        case 2:
            printf("la differenza vale: %.2f", num1+num2);
            break;
        case 3:
            printf("la moltiplicazione vale: %.2f", num1+num2);
            break;
        case 4:
            printf("la divisione vale: %.2f", num1+num2);
            break;
        default:
            printf("\n hai inserito una scelta non valida.");
    }
    return 0;

 }