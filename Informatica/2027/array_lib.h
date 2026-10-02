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

/** Carica un array con valori casuali compresi tra due limiti.
 * @param vet Vettore da riempire.
 * @param dim Dimensione dell'array.
 * @param min Valore minimo da inserire.
 * @param max Valore massimo da inserire.
 */
void caricaVettore(int _vet[], int _dim, int _min, int _max);

/** Stampa tutti gli elementi di un array.
 * @param _vet Vettore da stampare.
 * @param _dim Dimensione dell'array.
 */
void stampaVettore(int _vet[], int _dim);

/** Calcola la media aritmetica degli elementi di un array.
 * @param _vet Vettore di cui calcolare la media.
 * @param _dim Dimensione dell'array.
 * @return La media degli elementi, oppure 0 se l'array è vuoto.
 */
float mediaVettore(int _vet[], int _dim);

/** Restituisce il valore contenuto in una posizione specifica dell'array.
 * @param _vet Vettore da cui leggere il valore.
 * @param _dim Dimensione dell'array.
 * @param _index Indice della cella da leggere.
 * @return Valore presente nella cella richiesta; -1 se indice non esiste.
 */
 int getValoreAt(int _vet[], int _dim, int _index);

/** Stampa a video il sotto-array compreso tra due indici.
 * @param _vet Vettore da cui leggere il sotto-array.
 * @param _dim Dimensione del vettore.
 * @param _index1 Indice iniziale del sotto-array (incluso).
 * @param _index2 Indice finale del sotto-array (incluso).
 * @return true se il sotto-array è valido e viene stampato, false in caso contrario.
 */
 bool stampaSubArray(int _vet[], int _dim, int _index1, int _index2);

