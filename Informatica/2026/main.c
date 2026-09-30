#include <stdio.h> // include printf, fgets, puts
#include <stdlib.h> // include funzioni generiche come malloc/free e conversioni
#include <string.h> // include funzioni per operare sulle stringhe

#include "../include/tipi.h" // definisce tipi usati dal programma
#include "../include/utenti.h" // accesso ai dati e operazioni sugli utenti
#include "../include/conti.h" // accesso ai dati e operazioni sui conti bancari
#include "../include/transazioni.h" // accesso alle transazioni e loro conversione in JSON
#include "../include/file_io.h" // funzioni per leggere e scrivere file
#include "../include/utils.h" // funzioni di utilita generiche come trim e parsing JSON
#include "../include/crypto.h" // funzioni per gestire password e sicurezza

// protocollo: Node.js invia una riga JSON su stdin, il core risponde
// con una riga JSON su stdout e poi finisce il tutto
//
// comandi:
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

StatoBanca banca; // struttura globale che conserva utenti, conti e transazioni

// verifica credenziali inviate in formato JSON e restituisce l'id utente
// se la verifica fallisce, invia un messaggio di errore JSON e ritorna -1
int verifica_credenziali(const char *json) {
    char username[64], password[64]; // buffer per leggere i campi dal JSON
    char out[256]; // buffer per scrivere la risposta JSON di errore

    // legge username e password dal JSON, ritorna false se manca uno dei due
    if (!json_get_str(json, "username", username, sizeof(username)) || // legge username dal JSON
        !json_get_str(json, "password", password, sizeof(password))) { // legge password dal JSON
        json_errore("username o password mancanti", out, sizeof(out));
        puts(out); // manda il messaggio di errore su stdout
        return -1; // indica fallimento
    }

    // controlla le credenziali nel database degli utenti
    int id = utente_login(&banca, username, password);
    if (id < 0) {
        json_errore("credenziali non valide", out, sizeof(out));
        puts(out); // manda il messaggio di errore su stdout
        return -1; // login non valido
    }

    return id; // ritorna l'id dell'utente autenticato
}

// gestisce il comando "registra" e crea un nuovo utente + conto bancario
void cmd_registra(const char *json) {
    char nome[64], cognome[64], password[64], username[64]; // campi utente
    double eta_d = 0, saldo_d = 0; // valori numerici che arrivano dal JSON
    char out[MAX_JSON_OUT]; // buffer per la risposta JSON completa

    // legge i campi obbligatori dal JSON
    if (!json_get_str(json, "nome",     nome,     sizeof(nome))     || // legge il nome dal JSON
           !json_get_str(json, "cognome",  cognome,  sizeof(cognome))  || // legge il cognome dal JSON
        !json_get_str(json, "password", password, sizeof(password)) || // legge la password dal JSON
        !json_get_str(json, "username", username, sizeof(username)) || // legge lo username dal JSON
        !json_get_num(json, "eta",      &eta_d)) { // legge l'eta dal JSON
        json_errore("parametri mancanti (nome, cognome, username, eta, password)", out, sizeof(out));
        puts(out); // invia errore se mancano campi necessari
        return;
    }

    // converte la eta inserita in intero
    int eta   = (int)eta_d;
    // legge il saldo iniziale opzionale, se presente
    json_get_num(json, "saldo_iniziale", &saldo_d);
    int saldo = (int)saldo_d; // converte il saldo in intero

    if (eta < 18) {
        json_errore("eta minima 18 anni", out, sizeof(out));
        puts(out); // invia errore se l'utente è minorenne
        return;
    }

    // verifica che lo username non sia già preso
    if (utente_cerca_username(&banca, username)) {
        json_errore("username già in uso", out, sizeof(out));
        puts(out);
        return;
    }

    // aggiunge l'utente al database e ottiene il suo id
    int id = utente_aggiungi(&banca, username, password, nome, cognome);
    if (id < 0) {
        json_errore("registrazione fallita", out, sizeof(out));
        puts(out);
        return;
    }

    // salva gli utenti su file dopo la creazione
    salva_utenti(&banca);

    // crea un nuovo conto associato al nuovo utente
    int id_conto = conto_apri(&banca, id);
    if (id_conto < 0) {
        json_errore("apertura conto fallita", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = NULL; // inizializza il puntatore al conto
    // cerca il conto creato nell'array dei conti
    for (int i = 0; i < banca.n_conti; i++) { // scorre tutti i conti registrati
        if (banca.conti[i].id == id_conto) { // cerca il conto con l'id appena creato
            c = &banca.conti[i];
            break;
        }
    }

    // se è stato chiesto un saldo iniziale positivo, lo deposita sul conto
    if (saldo > 0 && c) {
        deposita(&banca, c->iban, saldo);
    }

    // salva lo stato aggiornato della banca su file
    salva_dati(&banca);

    // trova l'utente appena creato per generare la risposta JSON
    Utente *u = utente_cerca_id(&banca, id);
    char utente_json[512];
    utente_to_json(u, utente_json, sizeof(utente_json)); // converte l'utente in JSON

    // costruisce la risposta JSON con i dati di utente e conto
    char data_json[1024];
    snprintf(data_json, sizeof(data_json),
             "{\"username\":\"%s\",\"iban\":\"%s\",\"saldo\":%d,\"utente\":%s}",
             username, c ? c->iban : "", c ? c->saldo : 0, utente_json);

    json_ok(data_json, out, sizeof(out)); // genera una risposta di successo
    puts(out); // stampa la risposta su stdout
}

// gestisce il comando "login" e restituisce i dati dell'utente
void cmd_login(const char *json) {
    char out[MAX_JSON_OUT]; // buffer per la risposta JSON

    int id = verifica_credenziali(json); // controlla username/password
    if (id < 0) return; // termina al primo errore

    Utente *u = utente_cerca_id(&banca, id); // trova i dati utente
    char utente_json[512]; // buffer per l'utente convertito in JSON
    utente_to_json(u, utente_json, sizeof(utente_json));

    Conto *c = NULL; // cerca il conto attivo dell'utente
    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            c = &banca.conti[i];
            break;
        }
    }

    char data_json[1024]; // crea il JSON di risposta con conto e utente
    snprintf(data_json, sizeof(data_json),
             "{\"iban\":\"%s\",\"saldo\":%d,\"utente\":%s}",
             c ? c->iban : "", c ? c->saldo : 0, utente_json);

    json_ok(data_json, out, sizeof(out)); // genera risposta OK
    puts(out); // scrive su stdout
}

// gestisce il comando "profilo" e restituisce il profilo dell'utente
void cmd_profilo(const char *json) {
    char out[MAX_JSON_OUT]; // buffer per la risposta JSON

    int id = verifica_credenziali(json); // controlla le credenziali
    if (id < 0) return;

    Utente *u = utente_cerca_id(&banca, id); // trova l'utente
    if (!u) {
        json_errore("utente non trovato", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = NULL; // trova il conto attivo dell'utente
    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            c = &banca.conti[i];
            break;
        }
    }

    char utente_json[512]; // buffer per utente JSON
    utente_to_json(u, utente_json, sizeof(utente_json));

    char data_json[1024]; // buffer per la risposta completa
    snprintf(data_json, sizeof(data_json),
             "{\"utente\":%s,\"iban\":\"%s\",\"saldo\":%d}",
             utente_json, c ? c->iban : "", c ? c->saldo : 0);

    json_ok(data_json, out, sizeof(out)); // genera JSON OK
    puts(out);
}

// gestisce il comando "aggiorna_profilo" per modificare nome e cognome
void cmd_aggiorna_profilo(const char *json) {
    char nome[64], cognome[64]; // nuovi valori per nome e cognome
    char out[256]; // buffer per la risposta

    int id = verifica_credenziali(json); // verifica l'utente
    if (id < 0) return;

    json_get_str(json, "nome", nome, sizeof(nome)); // legge il nuovo nome se presente
    json_get_str(json, "cognome", cognome, sizeof(cognome)); // legge il nuovo cognome se presente

    if (!utente_aggiorna_profilo(&banca, id, nome, cognome)) {
        json_errore("aggiornamento profilo fallito", out, sizeof(out));
        puts(out);
        return;
    }

    salva_utenti(&banca); // salva le modifiche sugli utenti
    json_ok("", out, sizeof(out)); // invia una risposta OK vuota
    puts(out);
}

// gestisce il comando "cambia_password" per aggiornare la password
void cmd_cambia_password(const char *json) {
    char nuova[64]; // nuova password richiesta dal JSON
    char out[256]; // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_str(json, "nuova_password", nuova, sizeof(nuova))) {
        json_errore("nuova_password mancante", out, sizeof(out));
        puts(out);
        return;
    }

    if (!utente_cambia_password(&banca, id, nuova)) {
        json_errore("cambio password fallito", out, sizeof(out));
        puts(out);
        return;
    }

    salva_utenti(&banca); // salva la nuova password sul file
    json_ok("", out, sizeof(out)); // risposta di successo
    puts(out);
}

// gestisce il comando "lista_conti" e ritorna i conti dell'utente
void cmd_lista_conti(const char *json) {
    char out[MAX_JSON_OUT]; // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    char conti_json[MAX_JSON_OUT - 64]; // buffer per l'elenco conti in JSON
    conti_utente_to_json(&banca, id, conti_json, sizeof(conti_json)); // genera JSON dei conti
    json_ok(conti_json, out, sizeof(out)); // crea risposta OK
    puts(out);
}

// gestisce il comando "estratto_conto" per restituire conto + transazioni
void cmd_estratto_conto(const char *json) {
    char iban[35]; // IBAN richiesto
    char out[MAX_JSON_OUT]; // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_str(json, "iban", iban, sizeof(iban))) { // legge l'IBAN richiesto dal JSON
        json_errore("iban mancante", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = conto_cerca_iban(&banca, iban); // trova il conto dall'IBAN
    if (!c || c->id_utente != id) { // controlla che il conto esista e appartenga all'utente
        json_errore("conto non trovato", out, sizeof(out));
        puts(out);
        return;
    }

    char conto_json[256]; // buffer per i dati del conto
    conto_to_json(c, conto_json, sizeof(conto_json)); // converte il conto in JSON

    char tx_json[MAX_JSON_OUT - 512]; // buffer per le transazioni
    transazioni_to_json(c->transazioni, tx_json, sizeof(tx_json)); // converte transazioni in JSON

    char data_json[MAX_JSON_OUT - 256]; // buffer per la risposta completa
    snprintf(data_json, sizeof(data_json),
             "{\"conto\":%s,\"transazioni\":%s}", conto_json, tx_json);

    json_ok(data_json, out, sizeof(out)); // risposta OK con conto e transazioni
    puts(out);
}

// gestisce il comando "preleva" per ritirare soldi dal conto dell'utente
void cmd_preleva(const char *json) {
    double importo_d = 0.0; // importo letto come numero
    char out[256]; // buffer per output

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_num(json, "importo", &importo_d)) { // legge l'importo da prelevare dal JSON
        json_errore("importo mancante", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *c = NULL; // trova il conto attivo dell'utente
    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            c = &banca.conti[i];
            break;
        }
    }

    if (!c) {
        json_errore("nessun conto trovato", out, sizeof(out));
        puts(out);
        return;
    }

    int importo = (int)importo_d; // converte l'importo in intero
    if (!preleva(&banca, c->iban, importo)) {
        json_errore("fondi insufficienti", out, sizeof(out));
        puts(out);
        return;
    }

    salva_dati(&banca); // salva il nuovo saldo su file

    char saldo_json[64]; // buffer per il saldo aggiornato
    snprintf(saldo_json, sizeof(saldo_json), "{\"saldo\":%d}", c->saldo);
    json_ok(saldo_json, out, sizeof(out)); // invia il saldo aggiornato
    puts(out);
}

// gestisce il comando "invia" per trasferire soldi ad un altro conto
void cmd_invia(const char *json) {
    char iban_dest[35]; // IBAN destinatario
    double importo_d = 0.0; // importo da trasferire
    char out[256]; // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    if (!json_get_str(json, "iban_destinatario", iban_dest, sizeof(iban_dest)) || // legge l'IBAN del destinatario
        !json_get_num(json, "importo", &importo_d)) { // legge l'importo da trasferire
        json_errore("parametri mancanti", out, sizeof(out));
        puts(out);
        return;
    }

    Conto *mittente = NULL; // trova il conto del mittente
    for (int i = 0; i < banca.n_conti; i++) { // scorre i conti per trovare quello dell'utente
        if (banca.conti[i].id_utente == id && banca.conti[i].attivo) {
            mittente = &banca.conti[i];
            break;
        }
    }

    if (!mittente) {
        json_errore("nessun conto trovato", out, sizeof(out));
        puts(out);
        return;
    }

    if (strcmp(mittente->iban, iban_dest) == 0) { // controlla che l'IBAN destinatario sia diverso
        json_errore("non puoi inviare a te stesso", out, sizeof(out));
        puts(out);
        return;
    }

    int importo = (int)importo_d; // converte importo in intero
    int esito = bonifico(&banca, mittente->iban, iban_dest, importo); // esegue il bonifico

    if (esito == -2) { // il mittente non ha abbastanza fondi
        json_errore("fondi insufficienti", out, sizeof(out));
        puts(out);
        return;
    }
    if (esito == -3) { // l'IBAN destinatario non è presente nel database
        json_errore("IBAN destinatario non trovato", out, sizeof(out));
        puts(out);
        return;
    }
    if (esito < 0) {
        json_errore("invio fallito", out, sizeof(out));
        puts(out);
        return;
    }

    salva_dati(&banca); // salva il trasferimento sul file

    char saldo_json[64];
    snprintf(saldo_json, sizeof(saldo_json), "{\"saldo\":%d}", mittente->saldo); // saldo aggiornato del mittente
    json_ok(saldo_json, out, sizeof(out));
    puts(out);
}

// gestisce il comando "cerca_utenti" per trovare altri utenti
void cmd_cerca_utenti(const char *json) {
    char query[128]; // stringa di ricerca
    char out[MAX_JSON_OUT]; // buffer per la risposta JSON

    int id_self = verifica_credenziali(json);
    if (id_self < 0) return;

    query[0] = '\0'; // inizializza la stringa di ricerca vuota
    json_get_str(json, "query", query, sizeof(query)); // legge la query se presente

    char arr[MAX_JSON_OUT - 64]; // buffer per l'array di risultati
    int pos = 0; // indice corrente nel buffer
    arr[pos++] = '['; // apre l'array JSON
    int first = 1; // flag per la prima voce

    for (int i = 0; i < banca.n_utenti; i++) {
        Utente *u = &banca.utenti[i]; // utente corrente
        if (!u->attivo || u->id == id_self) continue; // salta utenti inattivi o se stessi

        if (query[0] &&
            !str_contains_ci(u->nome,     query) &&
            !str_contains_ci(u->cognome,  query) &&
            !str_contains_ci(u->username, query)) {
            continue; // salta se l'utente non corrisponde alla query
        }

        Conto *c = NULL; // cerca un conto attivo per l'utente trovato
        for (int j = 0; j < banca.n_conti; j++) {
            if (banca.conti[j].id_utente == u->id && banca.conti[j].attivo) {
                c = &banca.conti[j];
                break;
            }
        }
        if (!c) continue; // salta se l'utente non ha conto attivo

        char entry[256]; // buffer per un singolo risultato JSON
        int elen = snprintf(entry, sizeof(entry),
                            "{\"id\":%d,\"nome\":\"%s\",\"cognome\":\"%s\",\"username\":\"%s\",\"iban\":\"%s\"}",
                            u->id, u->nome, u->cognome, u->username, c->iban);

        if (pos + elen + 4 >= (int)sizeof(arr)) break; // controlla spazio nel buffer
        if (!first) arr[pos++] = ','; // separa gli oggetti con una virgola
        memcpy(arr + pos, entry, elen); // copia il risultato nel buffer
        pos += elen;
        first = 0; // da ora in poi non è più il primo elemento
    }

    arr[pos++] = ']'; // chiude l'array JSON
    arr[pos] = '\0'; // termina la stringa

    json_ok(arr, out, sizeof(out)); // invia i risultati come JSON OK
    puts(out);
}

// gestisce il comando "elimina_account" disattivando utente e conti
void cmd_elimina_account(const char *json) {
    char out[256]; // buffer per la risposta

    int id = verifica_credenziali(json);
    if (id < 0) return;

    for (int i = 0; i < banca.n_conti; i++) {
        if (banca.conti[i].id_utente == id) {
            banca.conti[i].attivo = 0; // disattiva ogni conto dell'utente
        }
    }

    Utente *u = utente_cerca_id(&banca, id); // trova l'utente
    if (u) {
        u->attivo = 0; // disattiva l'utente
    }

    salva_dati(&banca); // salva i conti aggiornati
    salva_utenti(&banca); // salva gli utenti aggiornati

    json_ok("", out, sizeof(out)); // invia una risposta di successo vuota
    puts(out);
}

// funzione principale: legge il JSON da stdin e chiama il comando giusto
int main() {
    memset(&banca, 0, sizeof(StatoBanca)); // inizializza la struttura banca a zero
    utenti_init(&banca); // alloca e prepara l'array utenti
    conti_init(&banca); // alloca e prepara l'array conti
    banca.prossimo_id_utente      = 1; // primo id utente disponibile
    banca.prossimo_id_conto       = 1; // primo id conto disponibile
    banca.prossimo_id_transazione = 1; // primo id transazione disponibile

    carica_dati(&banca); // legge i dati salvati da file

    char input[MAX_INPUT]; // buffer per leggere la riga JSON in ingresso
    if (!fgets(input, sizeof(input), stdin)) { // legge una riga da stdin
        char out[256]; // buffer per risposta di errore
        json_errore("nessun input ricevuto", out, sizeof(out));
        puts(out); // invia errore se non riceve input
        goto cleanup; // salta alla pulizia finale
    }

    str_trim(input); // elimina spazi e newline finali dall'input

    char cmd[64] = {0}; // buffer per leggere il comando
    if (!json_get_str(input, "cmd", cmd, sizeof(cmd))) { // legge il campo cmd dal JSON
        char out[256];
        json_errore("campo cmd mancante", out, sizeof(out));
        puts(out); // errore se manca il campo cmd nel JSON
        goto cleanup;
    }

    // confronta il comando ricevuto e chiama la funzione appropriata
    if      (strcmp(cmd, "registra")         == 0) cmd_registra(input);
    else if (strcmp(cmd, "login")            == 0) cmd_login(input);
    else if (strcmp(cmd, "profilo")          == 0) cmd_profilo(input);
    else if (strcmp(cmd, "aggiorna_profilo") == 0) cmd_aggiorna_profilo(input);
    else if (strcmp(cmd, "cambia_password")  == 0) cmd_cambia_password(input);
    else if (strcmp(cmd, "lista_conti")      == 0) cmd_lista_conti(input);
    else if (strcmp(cmd, "estratto_conto")   == 0) cmd_estratto_conto(input);
    else if (strcmp(cmd, "preleva")          == 0) cmd_preleva(input);
    else if (strcmp(cmd, "invia")            == 0) cmd_invia(input);
    else if (strcmp(cmd, "cerca_utenti")     == 0) cmd_cerca_utenti(input);
    else if (strcmp(cmd, "elimina_account")  == 0) cmd_elimina_account(input);
    else {
        char out[256]; // buffer per errore comando sconosciuto
        json_errore("comando sconosciuto", out, sizeof(out));
        puts(out); // invia errore se il comando non è valido
    }

cleanup:
    conti_libera(&banca); // libera la memoria dei conti al termine
    utenti_libera(&banca); // libera la memoria degli utenti al termine

    return 0; // termina il programma
}
