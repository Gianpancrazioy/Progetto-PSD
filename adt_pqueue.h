#include "item.h"

typedef struct c_PQ* pqueue;

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CREARE UNA NUOVA CODA DI PRIORITÀ.
/*
SPECIFICA SINTATTICA:
- pqueue (void) -> pqueue

SPECIFICA SEMANTICA:
- nuova_coda (void) -> p

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Restituisce un puntatore ad una struttura allocata dinamicamente di tipo pqueue

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
pqueue nuova_coda(void);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER GESTIRE RIALLOCAZIONE DINAMICA DI MEMORIA PER ARRAY DINAMICO.
/*
SPECIFICA SINTATTICA:
- pqueue (pqueue) -> pqueue

SPECIFICA SEMANTICA:
- espandi_heap (p) -> p

PRE-CONDIZIONI:
- Nessuna, controllo puntatore valido già effettuato nella funzione

POST-CONDIZIONI:
- Aggiunge MAXPQ + 1 spazi all'heap

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
pqueue espandi_heap(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CONTROLLARE SE LA CODA È VUOTA.
/*
SPECIFICA SINTATTICA:
- int (pqueue) -> int

SPECIFICA SEMANTICA:
- coda_vuota (p)    -> 1: Se la coda non è vuota 
                    -> 0: Se la coda è vuota

PRE-CONDIZIONI:
- Nessuna, controllo puntatore valido già effettuato nella funzione

POST-CONDIZIONI:
- Restituisce 0 se la coda è vuota, 1 altrimenti

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
int coda_vuota(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE IL MASSIMO ELEMENTO DALLA CODA DI PRIORITÀ.
/*
SPECIFICA SINTATTICA:
- item (pqueue) -> item 

SPECIFICA SEMANTICA:
- ottieni_massimo (p) -> p->vet[1]

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Restituisce il primo elemento della coda (il massimo in un max-heap)

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
item ottieni_massimo(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER ELIMINARE L'ELEMENTO MASSIMO DALLA CODA DI PRIORITÀ.
/*
SPECIFICA SINTATTICA:
- int (pqueue) -> int

SPECIFICA SEMANTICA:
- elimina_massimo (p)    -> 0: In caso di successo
                         -> 1: In caso di errore

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Elimina l'elemento con chiave massima e riaggiusta l'heap di conseguenza

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
int elimina_massimo(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER INSERIRE UN NUOVO ELEMENTO NELL'HEAP.
/*
SPECIFICA SINTATTICA:
- int (pqueue, item) -> int

SPECIFICA SEMANTICA:
- inserimento_coda (p, key)   -> 0: Se va a buon fine
                              -> 1: Se l'inserimento o l'espansione non vanno a buon fine

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati

POST-CONDIZIONI:
- Aggiunge un item in input "key" nella coda in input "p"

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
int inserimento_coda(pqueue q, item key);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER DEALLOCARE LA MEMORIA ASSEGNATA AD UNA CODA PASSATA IN INPUT
/*
SPECIFICA SINTATTICA:
- void (pqueue) -> void

SPECIFICA SEMANTICA:
- dealloca_coda (p) -> void

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati

POST-CONDIZIONI:
- Dealloca la memoria allocata per la coda

SIDE-EFFECTS:
- Tutti gli item contenuti nella coda saranno deallocati assieme alla coda
- Stampa su schermo in caso di errore

*/
void dealloca_coda(pqueue p);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE CHE STAMPA UNA CODA PASSATA IN INPUT IN ORDINE DI PRIORITA' SENZA MODIFICARLA
/*
SPECIFICA SINTATTICA:
- void (pqueue) -> void

SPECIFICA SEMANTICA:
- stampa_queue_priorita (p) -> void

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Stampa il contenuto della coda in ordine di chiave (priorità) senza modificare la coda in input p

SIDE-EFFECTS:
- Stampa su schermo in caso di errore
- Stampa a schermo tramite stampa_item() tutti gli item della coda in ordine di priorità

*/
void stampa_queue_priorita(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER TRASCRIVERE IL FILE IN INPUT IN UNA CODA A PRIORITA'
/*
SPECIFICA SINTATTICA:
- void (pqueue, FILE*) -> void

SPECIFICA SEMANTICA:
- ottieni_queue_da_file (p, fp) -> void

PRE-CONDIZIONI:
- p: Nessuna, controlli già effettuati nella funzione
- fp: Il file deve essere formattato secondo un ordine preciso

POST-CONDIZIONI:
- Genera una coda a priorità (attività di studio) basandosi su un file preso in input 

SIDE-EFFECTS:
- Stampa su schermo in caso di errore
- Legge da file

*/
void ottieni_queue_da_file(pqueue p, FILE* fp);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER SCRIVERE IL CONTENUTO DELLA QUEUE REPORT SUL FILE REPORT
/*
SPECIFICA SINTATTICA:
- void (pqueue) -> void

SPECIFICA SEMANTICA:
- scrivi_file_report_queue (p) -> void

PRE-CONDIZIONI:
- p: Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Passa gli item della coda p input alla funzione per scriverne il contenuto all'interno del file "report_settimanale.txt"

SIDE-EFFECTS:
- Stampa su file "report_settimanale.txt" tutti gli item contenuti nella coda tramite scrivi_file_report_item()
- Stampa su schermo in caso di errore

*/
void scrivi_file_report_queue(pqueue p);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE ID DA ASSEGNARE ALLA PROSSIMA ATTIVITA'
/*
SPECIFICA SINTATTICA:
- int (pqueue) -> int

SPECIFICA SEMANTICA:
- ottieni_id (p)    -> -1: Se la coda in input risulta inesistente
                    -> p->numel + 1: Il numero da assegnare al prossimo intero nella coda

PRE-CONDIZIONI:
- p: Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Restituisce l'id da assegnare nuovo elemento da inserire (es. numel = 6, id nuovo elemento = 7)

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
int ottieni_id(pqueue p);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE (UTILE PER SCELTA NEL MENU) PER STAMPARE L'ID DELLE ATTIVITA' PRESENTI NELLA CODA
/*
SPECIFICA SINTATTICA:
- void (pqueue) -> void

SPECIFICA SEMANTICA:
- stampa_id_queue (p) -> void

PRE-CONDIZIONI:
- p: Puntatore in input valido

POST-CONDIZIONI:
- Passa tutti gli item della coda alla funzione stampa_id_item() per stamparne dei campi

SIDE-EFFECTS:
- Stampa a schermo alcuni parametri da ogni item della coda in input tramite stampa_id_item()

*/
void stampa_id_queue(pqueue p);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE ENTRAMBI I FILE ATTIVITA
/*
SPECIFICA SINTATTICA:
- int (pqueue) -> int

SPECIFICA SEMANTICA:
. aggiorna_file_attivita_queue (p) -> -1: Se il puntatore in input non è valido
                                   ->  0: Se l'operazione di sovrascrittura file va a buon fine 
                                   ->  1: Se aggiorna_file_attivita_item() fallisce

PRE-CONDIZIONI:
- p: Nessuna, controllo già effettuato nella funzione

POST-CONDIZIONI:
- Passa ogni item contenuto nella coda p ed i puntatori ad "attivita.txt" e "attivita_menu.txt"
     alla funzione aggiorna_file_attivita_item() che si occuperà della scrittura su file

SIDE-EFFECTS:
- Aggiorna i files "attivita.txt" e "attivita_menu.txt" con gli elementi della coda p in input
- Stampa su schermo in caso di errore

*/
int aggiorna_file_attivita_queue(pqueue p);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE IL TEMPO DI LAVORO PER LE VARIE ATTIVITA' NELLA CODA
/*
SPECIFICA SINTATTICA:
- int (pqueue, int, double) -> int

SPECIFICA SEMANTICA:
- modifica_tempo_queue (q, id, tempo_totale) -> -1: Se il puntatore o id in input non è valido
                                             ->  0: Se le modifiche vanno a buon fine
                                             ->  1: Se modifica_tempo() o aggiorna_file_attivita_queue() falliscono

PRE-CONDIZIONI:
- p: Nessuna, controllo già effettuato nella funzione
- id: Nessuna, controllo già effettuato nella funzione
- tempo_totale: valore > 0 && valore < limite massimo double

POST-CONDIZIONI:
- La funzione passa l'item della coda q in input corrispondente all'id in input alla funzione "modifica_tempo()", che
     ne modifica il campo "tempo_passato" con il "tempo_totale", passato anch'esso in input 

SIDE-EFFECTS:
- Il campo "tempo_passato" dell'item corrispondente all'id in input sarà sovrascritto da "tempo_totale"
- Modifica il "tempo_passato" dell'item tramite la funzione modifica_tempo()
- Aggiorna i files "attivita.txt" e "attivita_menu.txt" con gli elementi della coda p in input
- Stampa su schermo in caso di errore

*/
int modifica_tempo_queue(pqueue q, int id, double tempo_totale);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CONTROLLARE LO STATO DELL'ATTIVITA' CORRISPONDENTE ALL'ID IN INPUT
/*
SPECIFICA SINTATTICA:
- int (pqueue, int) -> int

SPECIFICA SEMANTICA:
- controlla_stato_attivita (p)     -> -1: Se stato_completamento_item() restituisce -1
                                   ->  0: Se stato_completamento_item() restituisce 0
                                   ->  1: Se stato_completamento_item() restituisce 1

PRE-CONDIZIONI:
- p: Nessuna, controllo già effettuato nella funzione
- id: Nessuna, controllo già effettuato nella funzione

POST-CONDIZIONI:
- La funzione passa l'item della coda q in input corrispondente all'id in input alla funzione stato_completamento_item
     che ne verifica lo stato e restituisce -1 se in ritardo, 0 se completata, 1 se in corso

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
int controlla_stato_attivita(pqueue q, int id);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE STATO DI RITARDO DI UN'ATTIVITA'
/*
SPECIFICA SINTATTICA:
- void (pqueue, item) -> void

SPECIFICA SEMANTICA:
- aggiorna_ritardo (p, a) -> void

PRE-CONDIZIONI:
- Puntatori ad item e coda in input validi

POST-CONDIZIONI:
- Passa in input l'item a e tutti gli item della coda p a confronta_item()
     in base all'output di confronta_item(), viene eseguita aggiorna_attivita_ritardo()

SIDE-EFFECTS:
- Il campo "stato" dell'attività nella coda sarà sovrascritto con -1 (In Ritardo) tramite aggiorna_attivita_ritardo()
     se il confronto tra essa e l'item in input restituisce 0

*/
void aggiorna_ritardo(pqueue p, item a);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE PER AGGIORNARE ATTIVITA' NELLA CODA REPORT
/*
SPECIFICA SINTATTICA:
item (pqueue, int) -> item

SPECIFICA SEMANTICA:
- ottieni_item_attivita_per_report (q, c) -> q->vet[c]

PRE-CONDIZIONI:
- q: Puntatore valido
- c: valore compreso tra 1 e q->numel

POST-CONDIZIONI:
- Restituisce l'item corrispondente al valore c in input

SIDE-EFFECTS:
- Nessuno

*/
item ottieni_item_attivita_per_report(pqueue q, int c);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE LO STATO DI COMPLETAMENTO DI UN'ATTIVITA'
/*
SPECIFICA SINTATTICA:
- void (pqueue, item) -> void

SPECIFICA SEMANTICA:
- aggiorna_completata (p, a) -> void

PRE-CONDIZIONI:
- Puntatori ad item e coda in input validi

POST-CONDIZIONI:
- Passa in input l'item a e tutti gli item della coda p a confronta_item()
     in base all'output di confronta_item(), viene eseguita aggiorna_attivita_completata()

SIDE-EFFECTS:
- Il campo "stato" dell'attività nella coda sarà sovrascritto con 0 (Completata) tramite aggiorna_attivita_ritardo()
     se il confronto tra essa e l'item in input restituisce 0

*/
void aggiorna_completata(pqueue p, item a);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE ORDINE DEGLI ID DOPO LA RIMOZIONE DI UN'ATTIVITA'
/*
SPECIFICA SINTATTICA:
- void (pqueue) -> void

SPECIFICA SEMANTICA:
- aggiorna_id_ordine_queue (q) -> void

PRE-CONDIZIONI:
- Puntatore a coda q valido

POST-CONDIZIONI:
- Passa tutti gli item contenuti in q (ed il relativo indice) alla funzione aggiorna_id_ordine_item(), che ne aggiorna l'id

SIDE-EFFECTS:
- Il valore dell'id degli item passati in input ad aggiorna_id_ordine_item() sarà sovrascritto da i

*/
void aggiorna_id_ordine_queue(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER RIMUOVERE UN'ATTIVITA' DALLA CODA
/*
SPECIFICA SINTATTICA:
- void (pqueue, int) -> void

SPECIFICA SEMANTICA:
- rimuovi_item (q, id) -> void

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Rimuove l'elemento corrispondente all'id passato in input dalla queue q

SIDE-EFFECTS:
- Stampa su schermo in caso di errore
- Aggiorna l'ordine degli id nell'array dopo la rimozione tramite aggiorna_id_ordine_queue
- Aggiorna il file attività tramite aggiorna_file_attivita_queue()
- Dealloca ultimo elemento dell'array (quello da eliminare)

*/
void rimuovi_item(pqueue q, int id);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER RIMUOVERE UN'ATTIVITA' DALLA CODA REPORT
/*
SPECIFICA SINTATTICA:
- void (pqueue, item) -> void

SPECIFICA SEMANTICA:
- rimuovi_item (p, a) -> void

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Confronta ogni elemento di p con l'item a in input, se confronta_item() restituisce 0, allora rimuove l'item corrispondente
     nella coda report, poi lo dealloca, aggiorna gli id degli item nella coda

SIDE-EFFECTS:
- Stampa su schermo in caso di errore
- Aggiorna l'ordine degli id nell'array dopo la rimozione tramite aggiorna_id_ordine_queue
- Dealloca ultimo elemento dell'array (quello da eliminare)

*/
void rimuovi_item_report(pqueue p, item a);
