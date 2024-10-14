/*DATE DUE DATE ESPRESSE IN g, m, a 
DETERMINARE LA DATA PIU' RECENTE. */

#include <stdio.h>

int main(){
    int giorno1, mese1, anno1;
    int giorno2, mese2, anno2;

    printf("inserisci la prima data: ");
    scanf("%d%d%d", &giorno1, &mese1, &anno1 );
    printf("inserisci la seconda data: ");
    scanf("%d%d%d", &giorno2,&mese2, &anno2);
    if(anno1>anno2)
        printf("la data più recente è: %d/%d/%d", giorno1, mese1, anno1);
    else if(anno1<anno2)
                printf("la data piu recente è: %d/%d/%d", anno2, mese2, giorno2); 
    else{ //i due anni sono uguali
        if(mese1>mese2)
            printf("la data più recente è: %d/%d/%d", giorno1, mese1, anno1);
        else if(mese1<mese2)
            printf("la data piu recente è: %d/%d/%d", anno2, mese2, giorno2);
            
        else //I DUE MESI SONO UGUALI
            if(giorno1>giorno2)
                printf("la data piu  recente è: %d/%d/%d", giorno1, mese1, anno1);
            else if(giorno1<giorno2)
                printf("la data piu recente è: %d/%d/%d", anno2, mese2, giorno2);
            
            else
                printf("le date sono uguali.");
    }
        

}
    
