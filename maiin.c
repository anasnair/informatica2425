#include <stdio.h>    // include printf, fgets, puts — funzioni per input/output su terminale
#include <stdlib.h>   // include funzioni generiche: malloc/free per memoria, atoi per conversioni
#include <string.h>   // include funzioni per le stringhe: strcmp, strcpy, memset, memcpy

#include "../include/tipi.h"         // definisce i tipi usati dal programma (Utente, Conto, StatoBanca...)
#include "../include/utenti.h"       // dichiara le funzioni per gestire gli utenti (aggiungi, cerca, login...)
#include "../include/conti.h"        // dichiara le funzioni per gestire i conti bancari (apri, cerca IBAN...)
#include "../include/transazioni.h"  // dichiara le funzioni per le transazioni e la loro conversione in JSON
#include "../include/file_io.h"      // dichiara le funzioni per leggere e scrivere i file CSV
#include "../include/utils.h"        // dichiara funzioni di utilità: trim, generazione IBAN, parsing JSON
#include "../include/crypto.h"       // dichiara le funzioni per cifrare e verificare le password

// Protocollo: Node.js invia una riga JSON su stdin
// il programma C risponde con una riga JSON su stdout e poi termina
//
// Comandi supportati:
//   registra        — username, nome, cognome, eta, password, saldo_iniziale
//   login           — username, password
//   profilo         — username, password
//   aggiorna_profilo  — username, password, nome, cognome
//   cambia_password — username, password, nuova_password
//   lista_conti     — username, password
//   estratto_conto  — username, password, iban
//   preleva         — username, password, importo
//   invia           — username, password, iban_destinatario, importo
//   cerca_utenti    — username, password, query
//   elimina_account — username, password

StatoBanca banca; // variabile globale che contiene tutto lo stato della banca in memoria (utenti, conti, transazioni)

// --- verifica_credenziali ---
// Legge username e password dal JSON ricevuto e controlla se sono validi
// Ritorna l'id dell'utente se ok, oppure -1 se qualcosa non va
int verifica_credenziali(const char *json) {
    char username[64], password[64]; // buffer per salvare i valori letti dal JSON
    char out[256];                   // buffer per costruire il messaggio di errore JSON

    if (!json_get_str(json, "username", username, sizeof(username)) || // tenta di leggere il campo "username" dal JSON
        !json_get_str(json, "password", password, sizeof(password))) { // tenta di leggere il campo "password" dal JSON
        json_errore("username o password mancanti", out, sizeof(out)); // costruisce un JSON di errore
        puts(out); // stampa l'errore su stdout (lo riceve Node.js)
        return -1; // segnala che la verifica è fallita
    }

    int id = utente_login(&banca, username, password); // cerca l'utente nel database e controlla la password
    if (id < 0) {                                       // se non trova corrispondenza...
        json_errore("credenziali non valide", out, sizeof(out)); // ...costruisce un errore
        puts(out); // ...e lo stampa
        return -1; // ...ritorna -1 come segnale di fallimento
    }

    return id; // ritorna l'id numerico dell'utente autenticato con successo
}

// --- cmd_registra ---
// Gestisce il comando "registra": crea un nuovo utente e gli apre un conto bancario
void cmd_registra(const char *json) {
    char nome[64], cognome[64], password[64], username[64]; // buffer per i campi dell'utente
    double eta_d = 0, saldo_d = 0;                          // variabili temporanee per i numeri
    char out[MAX_JSON_OUT];                                  // buffer per la risposta JSON finale

    if (!json_get_str(json, "nome",     nome,     sizeof(nome))     || // legge il campo "nome" dal JSON
           !json_get_str(json, "cognome",  cognome,  sizeof(cognome))  || // legge il campo "cognome" dal JSON
        !json_get_str(json, "password", password, sizeof(password)) || // legge il campo "password" dal JSON
        !json_get_str(json, "username", username, sizeof(username)) || // legge il campo "username" dal JSON
        !json_get_num(json, "eta",      &eta_d)) {                     // legge il campo numerico "eta" dal JSON
        json_errore("parametri mancanti (nome, cognome, username, eta, password)", out, sizeof(out)); // errore se manca qualcosa
        puts(out); // invia l'errore su stdout
        return;    // esce dalla funzione senza fare nulla
    }

    int eta   = (int)eta_d; // converte l'età da double a intero (dal JSON arriva sempre come numero decimale)
    json_get_num(json, "saldo_iniziale", &saldo_d); // legge il saldo iniziale opzionale (se non c'è rimane 0)
    int saldo = (int)saldo_d;                        // converte il saldo da double a intero

    if (eta < 18) { // controlla che l'utente abbia almeno 18 anni
        json_errore("eta minima 18 anni", out, sizeof(out)); // errore se minorenne
        puts(out); // invia l'errore
        return;    // esce
    }

    if (utente_cerca_username(&banca, username)) { // controlla se lo username è già registrato nel database
        json_errore("username già in uso", out, sizeof(out)); // errore: username duplicato
        puts(out);
        return;
    }

    int id = utente_aggiungi(&banca, username, password, nome, cognome); // aggiunge l'utente all'array in memoria
    if (id < 0) { // se l'aggiunta è fallita (es. memoria piena)
        json_errore("registrazione fallita", out, sizeof(out));
        puts(out);
        return;
    }

    salva_utenti(&banca); // scrive subito i dati degli utenti sul file CSV per non perderli

    int id_conto = conto_apri(&banca, id); // crea un nuovo conto bancario associato all'utente appena creato
    if (id_conto < 0) { // se l'apertura del conto è fallita
        json_errore("apertura conto fallita", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = NULL; // puntatore al conto che sarà trovato nel prossimo ciclo
    for (int i = 0; i < banca.n_conti; i++) { // scorre tutti i conti in memoria
        if (banca.conti[i].id == id_conto) {   // cerca quello con l'id appena creato
            c = &banca.conti[i];               // salva il puntatore al conto trovato
            break;                             // esce dal ciclo
        }
    }

    if (saldo > 0 && c) { // se è stato richiesto un saldo iniziale positivo e il conto esiste
        deposita(&banca, c->iban, saldo); // deposita il saldo iniziale sul conto
    }

    salva_dati(&banca); // salva su file tutto lo stato aggiornato (utenti, conti, transazioni)

    Utente *u = utente_cerca_id(&banca, id); // recupera i dati dell'utente appena creato
    char utente_json[512];                    // buffer per il JSON dell'utente
    utente_to_json(u, utente_json, sizeof(utente_json)); // converte l'utente in stringa JSON

    char data_json[1024]; // buffer per il JSON della risposta completa
    snprintf(data_json, sizeof(data_json),    // costruisce il JSON con username, IBAN, saldo e dati utente
             "{\"username\":\"%s\",\"iban\":\"%s\",\"saldo\":%d,\"utente\":%s}",
             username, c ? c->iban : "", c ? c->saldo : 0, utente_json);

    json_ok(data_json, out, sizeof(out)); // avvolge il risultato in una risposta JSON {"status":"ok","data":...}
    puts(out);                            // stampa la risposta su stdout (la riceve Node.js)
}

// --- cmd_login ---
// Gestisce il comando "login": verifica le credenziali e restituisce i dati dell'utente e del suo conto
void cmd_login(const char *json) {
    char out[MAX_JSON_OUT]; // buffer per la risposta JSON

    int id = verifica_credenziali(json); // controlla username e password, ritorna l'id o -1
    if (id < 0) return;                  // se le credenziali non sono valide, la funzione già ha inviato l'errore

    Utente *u = utente_cerca_id(&banca, id); // recupera i dati dell'utente tramite il suo id
    char utente_json[512];                    // buffer per il JSON dell'utente
    utente_to_json(u, utente_json, sizeof(utente_json)); // serializza l'utente in formato JSON

    Conto *c = NULL; // puntatore al conto da trovare
    for (int i = 0; i < banca.n_conti; i++) { // scorre tutti i conti
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) { // cerca il conto attivo dell'utente
            c = &banca.conti[i]; // salva il riferimento al conto trovato
            break;               // esce dal ciclo
        }
    }

    char data_json[1024]; // buffer per il JSON di risposta
    snprintf(data_json, sizeof(data_json), // costruisce il JSON con IBAN, saldo e dati utente
             "{\"iban\":\"%s\",\"saldo\":%d,\"utente\":%s}",
             c ? c->iban : "", c ? c->saldo : 0, utente_json);

    json_ok(data_json, out, sizeof(out)); // crea la risposta di successo
    puts(out);                            // stampa su stdout
}

// --- cmd_profilo ---
// Gestisce il comando "profilo": restituisce i dati completi dell'utente autenticato
void cmd_profilo(const char *json) {
    char out[MAX_JSON_OUT]; // buffer per la risposta JSON

    int id = verifica_credenziali(json); // verifica le credenziali e ottiene l'id utente
    if (id < 0) return;                  // se fallisce, la funzione ha già risposto con errore

    Utente *u = utente_cerca_id(&banca, id); // cerca l'utente per id
    if (!u) { // se per qualche motivo non viene trovato
        json_errore("utente non trovato", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = NULL; // cerca il conto attivo dell'utente
    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            c = &banca.conti[i]; // salva il conto trovato
            break;
        }
    }

    char utente_json[512]; // buffer per il JSON utente
    utente_to_json(u, utente_json, sizeof(utente_json)); // converte utente in JSON

    char data_json[1024]; // buffer per la risposta finale
    snprintf(data_json, sizeof(data_json), // costruisce JSON con utente, IBAN e saldo
             "{\"utente\":%s,\"iban\":\"%s\",\"saldo\":%d}",
             utente_json, c ? c->iban : "", c ? c->saldo : 0);

    json_ok(data_json, out, sizeof(out)); // risposta di successo
    puts(out);
}

// --- cmd_aggiorna_profilo ---
// Gestisce il comando "aggiorna_profilo": modifica nome e/o cognome dell'utente
void cmd_aggiorna_profilo(const char *json) {
    char nome[64], cognome[64]; // buffer per i nuovi valori
    char out[256];              // buffer per la risposta

    int id = verifica_credenziali(json); // verifica chi sta facendo la richiesta
    if (id < 0) return;

    json_get_str(json, "nome", nome, sizeof(nome));         // legge il nuovo nome dal JSON (opzionale)
    json_get_str(json, "cognome", cognome, sizeof(cognome)); // legge il nuovo cognome dal JSON (opzionale)

    if (!utente_aggiorna_profilo(&banca, id, nome, cognome)) { // aggiorna i dati in memoria
        json_errore("aggiornamento profilo fallito", out, sizeof(out));
        puts(out);
        return;
    }

    salva_utenti(&banca);         // salva le modifiche sul file CSV degli utenti
    json_ok("", out, sizeof(out)); // risposta di successo senza dati aggiuntivi
    puts(out);
}

// --- cmd_cambia_password ---
// Gestisce il comando "cambia_password": sostituisce la password dell'utente con una nuova
void cmd_cambia_password(const char *json) {
    char nuova[64]; // buffer per la nuova password
    char out[256];  // buffer per la risposta

    int id = verifica_credenziali(json); // verifica l'identità dell'utente prima di permettere il cambio
    if (id < 0) return;

    if (!json_get_str(json, "nuova_password", nuova, sizeof(nuova))) { // legge la nuova password dal JSON
        json_errore("nuova_password mancante", out, sizeof(out));
        puts(out);
        return;
    }

    if (!utente_cambia_password(&banca, id, nuova)) { // aggiorna la password (viene criptata internamente)
        json_errore("cambio password fallito", out, sizeof(out));
        puts(out);
        return;
    }

    salva_utenti(&banca);         // salva la nuova password cifrata sul file
    json_ok("", out, sizeof(out)); // risposta OK vuota
    puts(out);
}

// --- cmd_lista_conti ---
// Gestisce il comando "lista_conti": restituisce la lista dei conti attivi dell'utente
void cmd_lista_conti(const char *json) {
    char out[MAX_JSON_OUT]; // buffer per la risposta

    int id = verifica_credenziali(json); // verifica le credenziali
    if (id < 0) return;

    char conti_json[MAX_JSON_OUT - 64]; // buffer per la lista conti serializzata in JSON
    conti_utente_to_json(&banca, id, conti_json, sizeof(conti_json)); // genera il JSON con tutti i conti dell'utente
    json_ok(conti_json, out, sizeof(out)); // avvolge in risposta OK
    puts(out);
}

// --- cmd_estratto_conto ---
// Gestisce il comando "estratto_conto": restituisce i dettagli del conto e tutte le transazioni
void cmd_estratto_conto(const char *json) {
    char iban[35];          // buffer per l'IBAN richiesto
    char out[MAX_JSON_OUT]; // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_str(json, "iban", iban, sizeof(iban))) { // legge l'IBAN richiesto dal JSON
        json_errore("iban mancante", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = conto_cerca_iban(&banca, iban); // cerca il conto con quell'IBAN
    if (!c || c->id_utente != id) {             // verifica che il conto esista E appartenga a questo utente
        json_errore("conto non trovato", out, sizeof(out));
        puts(out);
        return;
    }

    char conto_json[256]; // buffer per i dati del conto
    conto_to_json(c, conto_json, sizeof(conto_json)); // converte il conto in JSON

    char tx_json[MAX_JSON_OUT - 512]; // buffer per l'array delle transazioni
    transazioni_to_json(c->transazioni, tx_json, sizeof(tx_json)); // converte la lista di transazioni in JSON

    char data_json[MAX_JSON_OUT - 256]; // buffer per il JSON combinato
    snprintf(data_json, sizeof(data_json), // unisce conto e transazioni in un unico oggetto JSON
             "{\"conto\":%s,\"transazioni\":%s}", conto_json, tx_json);

    json_ok(data_json, out, sizeof(out)); // risposta di successo
    puts(out);
}

// --- cmd_preleva ---
// Gestisce il comando "preleva": sottrae un importo dal saldo del conto dell'utente
void cmd_preleva(const char *json) {
    double importo_d = 0.0; // importo letto dal JSON come numero decimale
    char out[256];           // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_num(json, "importo", &importo_d)) { // legge l'importo da prelevare dal JSON
        json_errore("importo mancante", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = NULL; // cerca il conto attivo dell'utente
    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            c = &banca.conti[i]; // salva il riferimento al conto trovato
            break;
        }
    }

    if (!c) { // se l'utente non ha nessun conto attivo
        json_errore("nessun conto trovato", out, sizeof(out));
        puts(out);
        return;
    }

    int importo = (int)importo_d; // converte l'importo in intero (centesimi o euro interi)
    if (!preleva(&banca, c->iban, importo)) { // tenta il prelievo: ritorna 0 se i fondi sono insufficienti
        json_errore("fondi insufficienti", out, sizeof(out));
        puts(out);
        return;
    }

    salva_dati(&banca); // salva il nuovo saldo su file

    char saldo_json[64]; // buffer per il saldo aggiornato
    snprintf(saldo_json, sizeof(saldo_json), "{\"saldo\":%d}", c->saldo); // costruisce JSON con il saldo aggiornato
    json_ok(saldo_json, out, sizeof(out)); // risposta di successo con il nuovo saldo
    puts(out);
}

// --- cmd_invia ---
// Gestisce il comando "invia": trasferisce denaro dal conto dell'utente a un altro conto
void cmd_invia(const char *json) {
    char iban_dest[35];     // IBAN del conto destinatario
    double importo_d = 0.0; // importo da trasferire
    char out[256];           // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_str(json, "iban_destinatario", iban_dest, sizeof(iban_dest)) || // legge l'IBAN destinatario
        !json_get_num(json, "importo", &importo_d)) {                              // legge l'importo
        json_errore("parametri mancanti", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *mittente = NULL; // cerca il conto dell'utente mittente
    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            mittente = &banca.conti[i]; // salva il conto mittente trovato
            break;
        }
    }

    if (!mittente) { // se il mittente non ha un conto attivo
        json_errore("nessun conto trovato", out, sizeof(out));
        puts(out);
        return;
    }

    if (strcmp(mittente->iban, iban_dest) == 0) { // controlla che l'utente non stia inviando a sé stesso
        json_errore("non puoi inviare a te stesso", out, sizeof(out));
        puts(out);
        return;
    }

    int importo = (int)importo_d;                                        // converte l'importo a intero
    int esito = bonifico(&banca, mittente->iban, iban_dest, importo);    // esegue il bonifico bancario

    if (esito == -2) { // codice -2: il mittente non ha fondi sufficienti
        json_errore("fondi insufficienti", out, sizeof(out));
        puts(out);
        return;
    }
    if (esito == -3) { // codice -3: l'IBAN destinatario non esiste nel database
        json_errore("IBAN destinatario non trovato", out, sizeof(out));
        puts(out);
        return;
    }
    if (esito < 0) { // qualsiasi altro errore negativo imprevisto
        json_errore("invio fallito", out, sizeof(out));
        puts(out);
        return;
    }

    salva_dati(&banca); // salva i saldi aggiornati su file

    char saldo_json[64];
    snprintf(saldo_json, sizeof(saldo_json), "{\"saldo\":%d}", mittente->saldo); // JSON con il saldo aggiornato del mittente
    json_ok(saldo_json, out, sizeof(out));
    puts(out);
}

// --- cmd_cerca_utenti ---
// Gestisce il comando "cerca_utenti": trova altri utenti per nome, cognome o username
void cmd_cerca_utenti(const char *json) {
    char query[128];        // stringa di ricerca inserita dall'utente
    char out[MAX_JSON_OUT]; // buffer per la risposta

    int id_self = verifica_credenziali(json); // identifica chi sta cercando (per escluderlo dai risultati)
    if (id_self < 0) return;

    query[0] = '\0';                                  // inizializza la query come stringa vuota (ricerca "tutti" se vuota)
    json_get_str(json, "query", query, sizeof(query)); // legge la query opzionale dal JSON

    char arr[MAX_JSON_OUT - 64]; // buffer per l'array JSON dei risultati
    int pos = 0;                 // indice corrente dove scrivere nel buffer
    arr[pos++] = '[';            // apre l'array JSON con [
    int first = 1;               // flag per gestire le virgole tra gli elementi

    for (int i = 0; i < banca.n_utenti; i++) {
        Utente *u = &banca.utenti[i];              // puntatore all'utente corrente
        if (!u->attivo || u->id == id_self) continue; // salta utenti eliminati o l'utente stesso

        if (query[0] &&                               // se c'è una query da cercare...
            !str_contains_ci(u->nome,     query) &&   // ...e il nome non corrisponde
            !str_contains_ci(u->cognome,  query) &&   // ...e il cognome non corrisponde
            !str_contains_ci(u->username, query)) {   // ...e nemmeno lo username
            continue; // allora salta questo utente, non è nei risultati
        }

        Conto *c = NULL; // cerca il conto attivo di questo utente risultato
        for (int j = 0; j < banca.n_conti; j++) {
            if (banca.conti[j].id_utente == u->id && banca.conti[j].attivo) {
                c = &banca.conti[j]; // salva il conto trovato
                break;
            }
        }
        if (!c) continue; // salta l'utente se non ha un conto attivo (non può ricevere bonifici)

        char entry[256]; // buffer per un singolo risultato JSON
        int elen = snprintf(entry, sizeof(entry), // costruisce il JSON di un singolo utente trovato
                            "{\"id\":%d,\"nome\":\"%s\",\"cognome\":\"%s\",\"username\":\"%s\",\"iban\":\"%s\"}",
                            u->id, u->nome, u->cognome, u->username, c->iban);

        if (pos + elen + 4 >= (int)sizeof(arr)) break; // controlla che ci sia ancora spazio nel buffer
        if (!first) arr[pos++] = ',';                   // aggiunge una virgola tra un risultato e il prossimo
        memcpy(arr + pos, entry, elen);                 // copia il JSON del singolo utente nel buffer
        pos += elen;                                    // avanza l'indice di scrittura
        first = 0;                                      // da adesso si aggiunge la virgola tra ogni elemento
    }

    arr[pos++] = ']'; // chiude l'array JSON con ]
    arr[pos] = '\0';  // termina la stringa con il carattere null

    json_ok(arr, out, sizeof(out)); // risposta di successo con l'array degli utenti trovati
    puts(out);
}

// --- cmd_elimina_account ---
// Gestisce il comando "elimina_account": disattiva l'account e tutti i conti dell'utente (soft delete)
void cmd_elimina_account(const char *json) {
    char out[256]; // buffer per la risposta

    int id = verifica_credenziali(json); // verifica le credenziali prima di eliminare
    if (id < 0) return;

    for (int i = 0; i < banca.n_conti; i++) { // scorre tutti i conti del database
        if (banca.conti[i].id_utente == id) {  // se il conto appartiene all'utente da eliminare
            banca.conti[i].attivo = 0;         // lo segna come inattivo (non viene cancellato fisicamente)
        }
    }

    Utente *u = utente_cerca_id(&banca, id); // recupera i dati dell'utente da disattivare
    if (u) {
        u->attivo = 0; // segna l'utente come inattivo (non viene cancellato fisicamente)
    }

    salva_dati(&banca);    // salva i conti aggiornati (con attivo=0) su file
    salva_utenti(&banca);  // salva gli utenti aggiornati (con attivo=0) su file

    json_ok("", out, sizeof(out)); // risposta di successo vuota
    puts(out);
}

// --- main ---
// Funzione principale: inizializza la banca, carica i dati, legge il comando JSON e lo esegue
int main() {
    memset(&banca, 0, sizeof(StatoBanca)); // azera tutti i campi della struttura banca (evita valori sporchi in memoria)
    utenti_init(&banca); // alloca l'array dinamico degli utenti con capacità iniziale
    conti_init(&banca);  // alloca l'array dinamico dei conti con capacità iniziale
    banca.prossimo_id_utente      = 1; // il prossimo utente creato avrà id 1 (poi 2, 3, ...)
    banca.prossimo_id_conto       = 1; // il prossimo conto creato avrà id 1
    banca.prossimo_id_transazione = 1; // la prossima transazione creata avrà id 1

    carica_dati(&banca); // legge i file CSV salvati e ripristina lo stato della banca in memoria

    char input[MAX_INPUT]; // buffer per leggere la riga JSON inviata da Node.js
    if (!fgets(input, sizeof(input), stdin)) { // legge una riga da stdin; se fallisce (es. stdin vuoto)...
        char out[256];
        json_errore("nessun input ricevuto", out, sizeof(out)); // ...costruisce un errore
        puts(out);    // ...lo stampa su stdout
        goto cleanup; // ...salta direttamente alla pulizia della memoria
    }

    str_trim(input); // rimuove spazi e caratteri di nuova riga (\n) finali dalla stringa input

    char cmd[64] = {0}; // buffer per il valore del campo "cmd" nel JSON
    if (!json_get_str(input, "cmd", cmd, sizeof(cmd))) { // tenta di leggere il campo "cmd" dal JSON
        char out[256];
        json_errore("campo cmd mancante", out, sizeof(out)); // errore se il campo non c'è
        puts(out); // stampa l'errore
        goto cleanup; // salta alla pulizia
    }

    // confronta il valore di cmd e chiama la funzione corrispondente
    if      (strcmp(cmd, "registra")         == 0) cmd_registra(input);         // comando: crea nuovo utente
    else if (strcmp(cmd, "login")            == 0) cmd_login(input);             // comando: accedi
    else if (strcmp(cmd, "profilo")          == 0) cmd_profilo(input);           // comando: vedi profilo
    else if (strcmp(cmd, "aggiorna_profilo") == 0) cmd_aggiorna_profilo(input);  // comando: modifica nome/cognome
    else if (strcmp(cmd, "cambia_password")  == 0) cmd_cambia_password(input);   // comando: cambia password
    else if (strcmp(cmd, "lista_conti")      == 0) cmd_lista_conti(input);       // comando: vedi i conti
    else if (strcmp(cmd, "estratto_conto")   == 0) cmd_estratto_conto(input);    // comando: vedi conto + transazioni
    else if (strcmp(cmd, "preleva")          == 0) cmd_preleva(input);           // comando: preleva soldi
    else if (strcmp(cmd, "invia")            == 0) cmd_invia(input);             // comando: bonifico a un altro conto
    else if (strcmp(cmd, "cerca_utenti")     == 0) cmd_cerca_utenti(input);      // comando: cerca utenti
    else if (strcmp(cmd, "elimina_account")  == 0) cmd_elimina_account(input);   // comando: elimina account
    else { // se il valore di cmd non corrisponde a nessun comando conosciuto
        char out[256];
        json_errore("comando sconosciuto", out, sizeof(out)); // costruisce errore
        puts(out); // lo stampa
    }

cleanup:
    conti_libera(&banca);   // libera tutta la memoria degli array dei conti (incluse le liste di transazioni)
    utenti_libera(&banca);  // libera tutta la memoria dell'array degli utenti

    return 0; // termina il programma con codice di uscita 0 (successo)
} 