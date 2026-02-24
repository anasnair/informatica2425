/*    Dichiarare un array di libri di dimensione massima N
    Consentire l'inserimento dei dati di un libro.
    Aggiornare correttamente il numero di copie disponibili.
    Registare il prestito di un libro:
        -inserendo la data di un prestito e la data di restituzione
        -decrementando il numero di copie disponibili
        -impedendo il prestito se non ci sono copie disponibili
    Visualizzare l'elenco completo dei libri con tutte le informazioni
    Visualizzare solo i libri attualmente in prestito(copie disponibili<copie totali)
    Cercare un libro tramite ISBN
    Stampare solo i libri con prestito scaduto
    Vincoli: accedere ai campi delle date tramite struct annidata
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data{
    	int giorno;
    	int m;
    	int a;
}data;

typedef struct libro {
    char titolo[50];
    char autore[50];
    int isbn;
    int copie_totale;
    int copie_disponibile;
    data data_pre;
    data data_rest;
} libro;


libro* creaLibri(libro* l, int n) {
    l = (libro*)realloc(l, (*n) * sizeof(libro));
    if(l == NULL) {
        printf("Errore di allocazione");
        exit(1);
    }
    return l;
}

void inserisciLibri(libro* l, int n) {
	int i;
    printf(" === Inserimento Di Tutti I Libri ===\n");

	for(i=0 ; i<n ; i++){
	printf(" === Inserimento Del L ===\n");
	printf("Inserisci il titolo del libro :\n");	
	fgets(l[i].titolo, 50, stdin);

	printf("Inserisci il nome dell'autore del libro : \n");	
	fgets(l[i].autore, 50, stdin);

	printf("Inserisci l'ISBN del libro:\n ");
	scanf("%d", &l[i].isbn);

	printf("Inserisci i copie totali del libro: \n");
	scanf("%d", &l[i].copie_totale);

    printf("Inserisci i copie disponibili del libro: \n");
	scanf("%d", &l[i].copie_disponibile);
	}
	char c;
	while((c = getchar()) != '\n') {}
}

void inserisciDataRegitra(libro* l, int n) {
    
    printf(" === Inserimento La data di prestito ===\n");
    printf("Inserisci il giorno del prestito del libro:\n ");
	scanf("%d", &l[n].data_pre.giorno);
	printf("Inserisci il mese del prestito del libro:\n ");
	scanf("%d", &l[n].data_pre.m);
    printf("Inserisci l'anno del prestito del libro:\n ");
	scanf("%d", &l[n].data_pre.a);

	printf(" === Inserimento La data di restituzione ===\n");

	
	printf("Inserisci il giorno del prestito del libro:\n ");
	scanf("%d", &l[n].data_rest.giorno);
	printf("Inserisci il mese del prestito del libro:\n ");
	scanf("%d", &l[n].data_rest.m);
    printf("Inserisci l'anno del prestito del libro:\n ");
	scanf("%d", &l[n].data_rest.a);
	
	char c;
	while((c = getchar()) != '\n') {}
}
void inserisciDataRestituzione(data* l, int n) {
    printf(" === Inserimento La data di prestito ===\n");

	printf("Inserisci il giorno del retituzione del libro:\n ");
	scanf("%d", &l.giorno);
	printf("Inserisci il mese del retituzione del libro:\n ");
	scanf("%d", &l.m);
    printf("Inserisci l'anno del retituzione del libro:\n ");
	scanf("%d", &l.a);
	
	char c;
	while((c = getchar()) != '\n') {}
}
void stampaTutto(libro* l, int n){
	int i;
    for(i=0 ; i<n ; i++){
	printf(" === la stampa dei libri ===\n");
	printf("il titolo del libro %d: %s\n", i+1, par);	
	printf("il nome dell'autore del libro : \n", i+1,l[i].autore);	
	printf("l'ISBN del libro %d:\n ",i+1 , l[i].isbn);
	printf("I copie totali del libro %d: \n",i+1 , l[i].copie_totale);
    printf("Inserisci i copie disponibili del libro: \n", i+1 , l[i].copie_disponibile);
	}
}
int cercalibro(libro* l, int dim, int n){
	int i;
	for(i=0 ; i<n ; i++){
		if(l[i].isbn == n){
			return i;
		}
	}
	return -1;
}
void stampaAprest(libro* l, int n){
	int i;
	for(i=0 ; i<n ; i++){
	if(l[i].copie_disponibile<l[i].copie_totale){
		printf(" === la stampa dei libri ===\n");
	printf("il titolo del libro %d: %s\n", i+1, par);	
	printf("il nome dell'autore del libro : \n", i+1,l[i].autore);	
	printf("l'ISBN del libro %d:\n ",i+1 , l[i].isbn);
	printf("I copie totali del libro %d: \n",i+1 , l[i].copie_totale);
    printf("Inserisci i copie disponibili del libro: \n", i+1 , l[i].copie_disponibile);
	}}
	
}
int main(){
    libro* libri = NULL;
    int n=0;
    char c;
    printf("Inserisci la quantita libri:\n ");
	scanf("%d", &n);
	while((c = getchar()) != '\n') {}
    libri=creaLibri(libri , n);
    inserisciLibri(libri , n);
	data rest;
    int scelta;
    

    do {
        printf("\n===== BEBLIOTECA FELONICA	=====\n");
        
        printf("0. REGISTRARE IL PRESTITO DI UN LIBRO\n");
        printf("1. REGISTRARE IL RESTITUImENTO DI UN LIBRO\n");
        printf("2. Visualizza L'elenco completo dei libri\n");
        printf("3. Visualizza solo i libri attuaqlmente in prestito\n");
        printf("4. Visualizza solo i libri con prestito scaduto\n");
        printf("5. Esci\n");
        printf("Scelta: ");
        scanf("%d", &scelta);
        while((c = getchar()) != '\n') {}

        switch (scelta) {
            case 0:
            	
                int num=0;
                printf("Inserisci l'ISBN del libro che vuoi prendere:\n ");
                scanf("%d", &num);
                int n = cercalibro(libri, n, num);
                if(n != -1){
                	inserisciDataRegitra(libri , n);
                	if(libri[i].copie_disponibile > 0)
                		libri[i].copie_disponibile--;
                	else
                		printf("purtroppo non ci sono disponibili i libri\n ");
				}else
                		printf("non c'e' il libro in cui cerchi\n ");
                brean;
            case 1:
                int num=0;
                printf("Inserisci l'ISBN del libro che vuoi ristituire:\n ");
                scanf("%d", &num);
                int n = cercalibro(libri, n, num);
                if(n != -1){
                	inserisciDataRestituzione(rest , n);
						printf("fatto\n ");
                		libri[i].copie_disponibile+++;
                	
				}else
                		printf("non c'e' il libro in cui cerchi\n ");
                brean;
            case 2:
                stampaTutto(libri, n);
                brean;    
            case 3:
                stampaAprest(libri, n);
                brean; 
            case 4:
            	for(i=0 ; i<n ; i++){
					if(rest.a > libri.data_rest.a){
						printf("il titolo del libro %d: %s\n", i+1, libri[i].titolo);	
						printf("il nome dell'autore del libro : \n", i+1,libri[i].autore);	
						printf("l'ISBN del libro %d:\n ",i+1 , libri[i].isbn);
						printf("I copie totali del libro %d: \n",i+1 , libri[i].copie_totale);
    					printf("Inserisci i copie disponibili del libro: \n", i+1 , libri[i].copie_disponibile);
					}else if(rest.m > libri.data_rest.m+2){
						printf("il titolo del libro %d: %s\n", i+1, libri[i].titolo);	
						printf("il nome dell'autore del libro : \n", i+1,libri[i].autore);	
						printf("l'ISBN del libro %d:\n ",i+1 , libri[i].isbn);
						printf("I copie totali del libro %d: \n",i+1 , libri[i].copie_totale);
    					printf("Inserisci i copie disponibili del libro: \n", i+1 , libri[i].copie_disponibile);
					}else if(rest.giorno > libri.data_rest.giorno && rest.m > libri.data_rest.m+1){
						printf("il titolo del libro %d: %s\n", i+1, libri[i].titolo);	
						printf("il nome dell'autore del libro : \n", i+1,libri[i].autore);	
						printf("l'ISBN del libro %d:\n ",i+1 , libri[i].isbn);
						printf("I copie totali del libro %d: \n",i+1 , libri[i].copie_totale);
    					printf("Inserisci i copie disponibili del libro: \n", i+1 , libri[i].copie_disponibile);
					}
					else
					 	printf("il libro %d non va : %s\n", i+1ų);
						
				}
                
                brean; 
            case 5:
                printf("Uscita dal programma.\n");
                brean;
            default:
                printf("Scelta non valida!\n");
        } 
    } while (scelta != 6);

    return 0;
}

