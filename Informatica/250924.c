/*ESERCIZIO
Calcola l'area di un triangolo
 inserendo la base e l'altezza.
 */
 
 #include <stdio.h>
 
 int main(){
 	float base, altezza, area; //dichiarazione
 	
 	base=0;				 	//inizializzazione
 	altezza=0;
 	area=0;
 	
 	printf("inserisci base: ");
	scanf("%f", &base);
	printf("inserisci altezza: ");
	scanf("%f", &altezza);
	area= base*altezza/2;
	printf("l'area vale: %f", area);

 }