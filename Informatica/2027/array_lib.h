/** Azzera tutte le celle di un array.
 * @param vett Riferimento al vettore da inizializzare.
 * @param dimensione Dimensione dell'array.
 */
void inizializza(int vett[], int dimensione);

/** Inserisce i valori nelle celle di un array.
 * @param vett Riferimento al vettore da riempire.
 * @param dimensione Dimensione dell'array.
 */
void inserisciValori(int vett[], int dimensione);

/** Stampa gli elementi di un array in colonna.
 * @param vett Vettore da stampare.
 * @param dimensione Dimensione dell'array.
 */
void stampaColonna(const int vett[], int dimensione);

/** Stampa tutti gli elementi di un array.
 * @param vet Vettore da stampare.
 * @param dim Dimensione dell'array.
 */
void stampaVettore(int vet[], int dim);

/** Trova e visualizza il valore massimo di un array.
 * @param vet Vettore in cui cercare il valore massimo.
 * @param dim Dimensione dell'array.
 */
void trovavaloreMassimo(int vet[], int dim);

/** Conta quante volte compare un valore in un array.
 * @param vet Vettore in cui effettuare la ricerca.
 * @param dim Dimensione dell'array.
 * @param valore Valore da contare.
 * @return Numero di occorrenze del valore.
 */
int contaValore(int vet[], int dim, int valore);

/** Sostituisce tutte le occorrenze di un valore in un array.
 * @param vet Vettore in cui effettuare la ricerca e la sostituzione.
 * @param dim Dimensione dell'array.
 * @param src Valore da sostituire.
 * @param sost Nuovo valore da inserire.
 * @return Numero di sostituzioni effettuate.
 */
int ricercaSostituisci(int vet[], int dim, int src, int sost);

