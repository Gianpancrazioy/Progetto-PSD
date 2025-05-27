#ifndef ITEM_H
#define ITEM_H
typedef struct attivita_studio *item;
#endif

#define NULLITEM 0

#include <stdio.h>

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE LA PRIORITA' DELL'ITEM IN INPUT
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- ottieni_priorità (a) -> a->priorita

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- Restituisce il valore del campo "priorita" dell'item in input

SIDE-EFFECTS:
- Nessuno

*/
int ottieni_priorita(item a);

//-------------------------------------------------------------------------------------

//FUNZIONE PER CREARE ED ALLOCARE DINAMICAMENTE UN NUOVO ITEM CON PARAMETRI ANNESSI
/*
SPECIFICA SINTATTICA:
- item (void) -> item

SPECIFICA SEMANTICA:
- nuovo_item (void) -> a

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Alloca memoria per un item a, e per tutti i suoi campi, e lo restituisce

SIDE-EFFECTS:
- Stampa a schermo in caso di errore

*/
item nuovo_item();

//-------------------------------------------------------------------------------------

//FUNZIONE PRE DEALLOCARE MEMORIA PER UN ITEM PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- dealloca_item (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- La memoria allocata per i campi dell'item in input viene deallocata

SIDE-EFFECTS:
- Nessuno

*/
void dealloca_item(item a);

//-------------------------------------------------------------------------------------

//FUNZIONE PER COPIARE UN ITEM PASSATO IN INPUT ALL'INTERNO DEI FILE ATTIVITA
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- scrivi_file_attivita (a) -> void

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Se l'item è valido e l'apertura dei files va a buon fine, avvia un'operazione di scrittura sui files aperti

SIDE-EFFECTS:
- Stampa a schermo in caso di errore
- I files "attivita.txt" e "attivita_menu.txt" vengono aggiornati con il nuovo item scritto in append

*/
void scrivi_file_attivita(item a);

//-------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE FILE ATTIVITA'
/*
SPECIFICA SINTATTICA:
- int (item, FILE*, FILE*) -> int

SPECIFICA SEMANTICA:
- aggiorna_file_attivita_item (a, fp, fp1)  -> 0: Operazione andata a buon fine
                                            -> 1: Operazione non andata a buon fine

PRE-CONDIZIONI:
- a: item in input valido
- fp: Puntatore a file in input valido
- fp1: Puntatore a file in input valido

POST-CONDIZIONI:
- La funzione restituisce 0 se l'operazione di scrittura su entrambi i file è andata a buon fine, 1 se almeno una scrittura e fallita

SIDE-EFFECTS:
- Scrive i dati di item sui files puntati dai due puntatori in input

*/
int aggiorna_file_attivita_item(item a, FILE* fp, FILE* fp1);

//-------------------------------------------------------------------------------------

//FUNZIONE PER REGISTRARE UNA NUOVA ATTIVITA' DI STUDIO
/*
SPECIFICA SINTATTICA:
- item (int) -> item

SPECIFICA SEMANTICA:
- aggiungi (id) -> a

PRE-CONDIZIONI:
- valore dell'id compreso tra 1 ed il massimo valore intero rappresentabile

POST-CONDIZIONI:
- Restituisce un item i cui campi sono dati in input dall'utente. Tramite scrivi_file_attivita() sarà aggiunto a file

SIDE-EFFECTS:
- Stampa a schermo in caso di errore
- Stampa a schermo istruzioni per compilare i campi dell'item
- Legge input da tastiera
- Scrive su file tramite scrivi_file_attivita()

*/
item aggiungi (int id);

//-------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE LO STATO DI UN ITEM PASSATO IN INPUT A 0 (COMPLETATA)
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- aggiorna_attivita_completata (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- Il campo "stato" dell'item in input viene aggiornato a 0

SIDE-EFFECTS:
- Nessuno

*/
void aggiorna_attivita_completata(item a);

//-------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE LO STATO DI UN ITEM PASSATO IN INPUT A -1 (RITARDO)
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- aggiorna_attivita_ritardo (a) -> void

PRE-CONDIZIONI:
- Item a in input è un puntatore valido

POST-CONDIZIONI:
- Aggiorna il campo "stato" dell'item in input a -1  

SIDE-EFFECTS:
- Nessuno

*/
void aggiorna_attivita_ritardo(item a);

//-------------------------------------------------------------------------------------

//FUNZIONE PER VERIFICARE LO STATO DI COMPLETAMENTO DI UN ITEM PASSATO IN INPUT E, IN CASO, AGGIORNARLO
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- stato_completamento_item (a)  -> -1: Attività in ritardo
                                ->  0: Attività completata 
                                ->  1: Attività in corso

PRE-CONDIZIONI:
- Item a in input è un puntatore valido

POST-CONDIZIONI:
- Mostra lo stato di completamento dell'attività basandosi sulla percentuale ottenuta da tempo_passato e tempo_stimato dell'item 
    in input. Se l'attività risulta ancora in corso, allora restituisce 1, se invece risulta completata (percentuale del 100%), 
    allora chiede all'utente se l'attività è stata completata nel tempo previsto o meno. 
    Se l'attività è stata completata, restituisce 0, altrimenti -1

SIDE-EFFECTS:
- Stampa a schermo una barra di avanzamento con percentuale tramite funzione mostra_barra_avanzamento()
- Stampa a schermo istruzioni per input
- Prende input da tastiera 

*/
int stato_completamento_item(item a);

//-------------------------------------------------------------------------------------

//FUNZIONE PER SCRIVERE UN ITEM IN INPUT SU FILE REPORT PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- void (item, FILE*) -> void

SPECIFICA SEMANTICA:
- scrivi_file_report_item (a, fp) -> void

PRE-CONDIZIONI:
- a: Puntatore ad item valido
- fp: Puntatore a file valido

POST-CONDIZIONI:
- Avvia un'operazione di scrittura dell'item su file in input secondo una determinata formattazione

SIDE-EFFECTS:
- Stampa tutti i campi dell'item in input sul file di testo passato in input, secondo una formattazione ben precisa

*/
void scrivi_file_report_item(item a, FILE* fp);

//-------------------------------------------------------------------------------------

//FUNZIONE CHE AGGIORNA IL TEMPO DI LAVORO NELL'ITEM PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- int (item, double) -> int

SPECIFICA SEMANTICA:
- modifica_tempo (a, tempo_totale)  -> 0 : Operazione andata a buon fine
                                    -> 1 : Operazione non andata a buon fine

PRE-CONDIZIONI:
- a: Puntatore ad item valido
- tempo_totale: Valore compreso tra 0 ed il valore double massimo rappresentabile

POST-CONDIZIONI:
- Aggiorna il campo "tempo_passato" dell'item in input sommandoci il valore di tempo_totale. Restituisce 0 se va a buon fine, 1 altrimenti

SIDE-EFFECTS:
- Nessuno

*/
int modifica_tempo(item a, double tempo_totale);

//-------------------------------------------------------------------------------------

//FUNZIONE PER VERIFICARE LO STATO DI COMPLETAMENTO DI UN ITEM PASSATO IN INPUT E, IN CASO, AGGIORNARLO
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- stato_completamento_item (a)  -> -1: Attività in ritardo
                                ->  0: Attività completata 
                                ->  1: Attività in corso

PRE-CONDIZIONI:
- Item a in input è un puntatore valido

POST-CONDIZIONI:
- Mostra lo stato di completamento dell'attività basandosi sulla percentuale ottenuta da tempo_passato e tempo_stimato dell'item 
    in input. Se l'attività risulta ancora in corso, allora restituisce 1, se invece risulta completata (percentuale del 100%), 
    allora chiede all'utente se l'attività è stata completata nel tempo previsto o meno. 
    Se l'attività è stata completata, restituisce 0, altrimenti -1

SIDE-EFFECTS:
- Stampa a schermo una barra di avanzamento con percentuale tramite funzione mostra_barra_avanzamento()
- Stampa a schermo istruzioni per input
- Prende input da tastiera 

*/
int stato_completamento_item(item a);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER STAMPARE I CAMPI DI UN ITEM PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- stampa_item (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- Stampa a schermo i campi dell'item a in input, il campo "stato" è rappresentato da una stringa aggiornata in base al suo valore numerico

SIDE-EFFECTS:
- Stampa a schermo i dati contenuti nei campi dell'item in input

*/
void stampa_item(item a);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CREARE UN ITEM A PARTIRE DAI VALORI IN INPUT
/*
SPECIFICA SINTATTICA:
- item (char*, char*, char*, char*, char*, int, int, int) -> item

SPECIFICA SEMANTICA:
- inserisci_item (descrizione, corso, data_scadenza, tempo_stimato, tempo_passato, priorita, id, stato) -> a

PRE-CONDIZIONI:
- descrizione: Puntatore Valido
- corso: Puntatore Valido
- data_scadenza: Puntatore Valido
- tempo_stimato: Puntatore Valido
- tempo_passato: Puntatore Valido
- priorita: Valore intero compreso tra 0 e 3
- id: Valore intero compreso tra 0 ed il numero massimo di elementi nella coda attività
- stato: Valore intero compreso tra -1 e 1

POST-CONDIZIONI:
- La funzione inizializza un nuovo item assegnando ai suoi campi i valori passati in input e lo restituisce

SIDE-EFFECTS:
- Nessuno

*/
item inserisci_item(char* descrizione, char* corso, char* data_scadenza, char* tempo_stimato, char* tempo_passato, int priorita, int id, int stato);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER COPIARE UN ITEM IN UN ALTRO
/*
SPECIFICA SINTATTICA:
- item (item) -> item

SPECIFICA SEMANTICA:
- copia_item (a) -> b

PRE-CONDIZIONI:
- Puntatore ad item a passato in input deve essere valido

POST-CONDIZIONI:
- Alloca un item b, copia in esso il valore di ogni campo dell'item a e lo restituisce

SIDE-EFFECTS:
- Nessuno

*/
item copia_item(item a);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE PER STAMPARE ID ITEMS PER SCELTA MENU
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- stampa_id_item (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item a in input valido

POST-CONDIZIONI:
- Stampa a schermo il valore di "descrizione" e "id" dell'item in input secondo una formattazione preciso

SIDE-EFFECTS:
- Stampa a schermo

*/
void stampa_id_item(item a);
//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE AD OTTENERE ID DI UN DATO ITEM
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- ottieni_id_item (a) -> a->id

PRE-CONDIZIONI:
- Puntatore ad item a in input valido

POST-CONDIZIONI:
- Restituisce il valore del campo "id" dell'item passato in input

SIDE-EFFECTS:
- Nessuno

*/
int ottieni_id_item(item a);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE AD OTTENERE LO STATO DI UN DATO ITEM
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- ottieni_stato_item (a) -> a->id

PRE-CONDIZIONI:
- Puntatore ad item a in input valido

POST-CONDIZIONI:
- Restituisce il valore del campo "stato" dell'item passato in input

SIDE-EFFECTS:
- Nessuno

*/
int ottieni_stato_item(item a);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE A CONFRONTARE 2 ITEMS
/*
SPECIFICA SINTATTICA:
- int (item, item) -> int

SPECIFICA SEMANTICA:
- confronta_item (a, b)   -> 1: I due items sono diversi
                        -> 0: I due items sono uguali

PRE-CONDIZIONI:
- a: Puntatore ad item in input valido
- b: Puntatore ad item in input valido

POST-CONDIZIONI:
- Restituisce 0 se i due item in input hanno i campi confrontati uguali, 1 se sono diversi o se almeno uno dei due è NULL

SIDE-EFFECTS:
- Nessuno

*/
int confronta_item(item a, item b);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE AD AGGIORNARE L'ID DI UN ITEM
/*
SPECIFICA SINTATTICA:
- void (item, int) -> void

SPECIFICA SEMANTICA:
- aggiorna_id_ordine_item (a, id) -> void

PRE-CONDIZIONI:
- a: Puntatore ad item valido
- id: Valore intero compreso tra 1 ed il numero di elementi della coda attività

POST-CONDIZIONI:
- Aggiorna il campi "id" dell'item in input con il valode di id

SIDE-EFFECTS:
- Nessuno

*/
void aggiorna_id_ordine_item(item a, int id);