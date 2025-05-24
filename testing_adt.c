#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "testing_adt.h"
#include "testing_item.h"        // Inclusione dell'header file per l'item.

#define MAXPQ 50         // Definizione della dimensione massima dell'heap.

//------------------------------------------------------------------------------------------------------------------------------------------

//DEFINIZIONE DELLA STRUTTURA PER LA CODA DI PRIORITÀ.
struct c_PQ {
     item* vet;          // Array per memorizzare gli elementi dell'heap. Allocazione dinamica.
     int numel;          // Numero attuale di elementi nell'heap.
};

//------------------------------------------------------------------------------------------------------------------------------------------

//DICHIARAZIONE DELLE FUNZIONI STATICHE PER LA MANIPOLAZIONE DELL'HEAP.
static void scendi (pqueue p);
static void sali (pqueue p); 

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
pqueue nuova_coda(void){
     pqueue p;

     p = malloc(sizeof(struct c_PQ));         // Allocazione della memoria per la coda.
     if(p == NULL){                           // Controlla Errore allocazione memoria.
          printf("Errore allocazione memoria in fase di creazione coda.\n");
          return NULL;
     }
     
     p->vet = malloc (sizeof(item) * MAXPQ);  // Allocazione della memoria per l'heap.
     if(p->vet == NULL){                           // Controlla Errore allocazione memoria.
          printf("Errore allocazione spazio per l'heap.\n");
          return NULL;
     }
     p->numel = 0;                            // Inizializzazione del numero di elementi a zero.

return p;                                    // Ritorno del puntatore alla coda.
}

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
pqueue espandi_heap(pqueue p){
     if(p == NULL){
          printf("Coda non valida, impossibile riallocare spazio\n");
          return NULL;
     }

     p->vet = (item*) realloc (p->vet, sizeof(item) * (p->numel + MAXPQ + 1));  // Rialloca l'array aggiungendo MAXPQ spazi.
     if(p->vet == NULL) return NULL;                                       // Gestione errore realloc.

return p;
}

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
int coda_vuota(pqueue p){
     if (!p){                                // Verifica se il puntatore è NULL.
          printf("Errore, coda inesistente.\n"); 
          return 1;
     }

return p->numel == 0;                        // Restituisce 0 se la coda è vuota.
}

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
item ottieni_massimo(pqueue p){
     if (!p || p->numel == 0){               // Controlla se la coda è vuota o il puntatore è NULL 
          printf("Errore, coda vuota o inesistente.\n");
          return NULL;   
     }

return p->vet[1];                            // Resituisce l'elemento al primo indice (massimo in un max-heap).
}

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
int elimina_massimo(pqueue p){
     
     if (!p || p->numel == 0){          // Controlla se la coda è vuota o il puntatore è NULL.
          printf("Errore, coda vuota o inesistente.\n");
          return 1;
     } 

     p->vet[1] = p->vet[p->numel];      // Sostituisce la radice con l'ultimo elemento.
     p->numel--;                        // Decrementa il numero di elementi.

     scendi(p);                         // Riaggiusta l'heap scendendo l'elemento sostituito.
     
return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER RIAGGIUSTARE L'HEAP VERSO IL BASSO. 
/*
SPECIFICA SINTATTICA:
- static void (pqueue) -> void

SPECIFICA SEMANTICA:
- scendi (p) -> void

PRE-CONDIZIONI:
- Il puntatore in input è valido

POST-CONDIZIONI:
- Riaggiusta l'heap dopo la rimozione di un elemento in ordine di chiave (priorità)

SIDE-EFFECTS:
- Nessuno

*/
static void scendi(pqueue p){
    item temp;
    int n = p->numel, i = 1, pos;

    while (1){
          // Determina la posizione del figlio con il valore più grande.
          if (2*i + 1 <= n)                                                 // Se il nodo corrente ha due figli.
               pos = (ottieni_priorita(p->vet[2*i]) > ottieni_priorita(p->vet[2*i + 1])) ? 2*i : 2*i + 1;
          else if (2*i <= n)                                                // Se il nodo corrente ha solo un figlio.
               pos = 2*i;
          else 
               break;                                                       // Se non ha figli, interrompe il ciclo.

          // Scambia le chiavi se il figlio ha un valore più grande.
          if (ottieni_priorita(p->vet[pos]) > ottieni_priorita(p->vet[i])){
               temp = p->vet[i];
               p->vet[i] = p->vet[pos];
               p->vet[pos] = temp;
               i = pos;                                                     // Continua a scendere nell'heap.
          }
          else
               break;                                                       // Termina se non sono necessari altri scambi.
     }

return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER INSERIRE UN NUOVO ELEMENTO NELL'HEAP.
/*
SPECIFICA SINTATTICA:
- int (pqueue, item) -> int

SPECIFICA SEMANTICA:
- insert (p, key)   -> 0: Se va a buon fine
                    -> 1: Se l'inserimento o l'espansione non vanno a buon fine

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati

POST-CONDIZIONI:
- Aggiunge un item in input "key" nella coda in input "p"

SIDE-EFFECTS:
- Stampa su schermo in caso di errore

*/
int insert(pqueue p, item key){
     if ((!p)||(!key)){                           // Verifica se puntatori a coda o item sono NULL.
          printf("Errore, coda inesistente.\n"); 
          return 1;
     }     
     if (((p->numel)%MAXPQ) == 0)                 // Controlla se l'heap è pieno, in caso chiama funzioe di espansione heap.
          p = espandi_heap(p);
          if(p == NULL){                          // Controlla se la riallocazione dell'heap è andata a buon fine.
               printf("Errore riallocazione spazio per l'heap nella funzione di inserimento.\n");
               return 1;
          }
     
     p->numel++; 
     p->vet[p->numel] = key;                 // Inserisce il nuovo elemento all'ultima posizione.
     sali(p);                                // Riaggiusta l'heap risalendo l'elemento inserito.
     

     return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER RIAGGIUSTARE L'HEAP VERSO L'ALTO. 
/*
SPECIFICA SINTATTICA:
- static void (pqueue) -> void

SPECIFICA SEMANTICA:
- sali (p) -> void

PRE-CONDIZIONI:
- Puntatore in input valido

POST-CONDIZIONI:
- Riaggiusta l'heap verso l'alto dopo l'inserimento di un elemento

SIDE-EFFECTS:
- Nessuno

*/
static void sali(pqueue p){
     item temp;
     int pos = p->numel, i = pos / 2;

     while (pos > 1){
          // Se l'elemento inserito è maggiore del suo genitore, scambia i loro valori.
          if (ottieni_priorita(p->vet[pos]) > ottieni_priorita(p->vet[i])){
               temp = p->vet[i];
               p->vet[i] = p->vet[pos];
               p->vet[pos] = temp;
               pos = i;
               i = pos / 2;                   // Continua a salire nell'heap.
          }
          else
               break;                         // Termina se non sono necessari altri scambi.
     }

return;
}

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
void dealloca_coda(pqueue p){
     if(p == NULL){                     //Controlla se il puntatore è NULL
          printf("Errore, coda non valida, impossibile deallocare memoria\n");
          return;
     }

     for(int i = 1; i <= p->numel; i++){              //Cicla per deallocare tutti gli item nella coda
          if(p->vet[i] == NULL) continue;
          dealloca_item(p->vet[i]);
          p->vet[i] = NULL;             //Evito pending pointers
     }

     free(p->vet);                      //Dealloca la memoria per l'array
     free(p);                           //Dealloca la coda a priorità

return;
}

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
void stampa_queue_priorita(pqueue p){
     if(p == NULL){                     //Controlla se il puntatore è NULL
          printf("Errore, coda vuota o inesistente\n");
          return;
     }
     
     if(coda_vuota(p) == 1){            //Controlla se la coda è vuota
          printf("La coda e' vuota, uscita\n");
          return;
     }
     
     FILE* fp = fopen("test_suite/output1.txt","w");
     
     item max = nuovo_item();           //Alloca memoria per un item temporaneo
     pqueue temp = nuova_coda();        //Alloca memoria per una coda temporanea
     temp->numel = p->numel;            //Assegna a temp->numel il numero di elementi di p

     //PER STAMPARE LA CODA IN ORDINE DI PRIORITA' SENZA MODIFICARE L'ORIGINALE
     for(int i = 1; i <= p->numel; i++){     //Cicla per copiare tutti gli elementi di p in coda temporanea
          temp->vet[i] = copia_item(p->vet[i]);
     }

     while(coda_vuota(temp) != 1){           //Cicla per stampare la coda temporanea in ordine di priorità
          max = ottieni_massimo(temp);           
          scrivi_file_report_item(max, fp);
          elimina_massimo(temp);
     }

     fclose(fp);

     free(max);                         //Dealloca max     
     dealloca_coda(temp);               //dealloca la coda temporanea

return;
}


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

void ottieni_queue_da_file(pqueue p, FILE* fp){
     if(fp == NULL){     //Controlla se il puntatore a file è NULL
          printf("Errore in apertura file.");
          return;
     }
     else if(p == NULL){ //Controlla se il puntatore a coda è NULL
          printf("Coda inesistente\n");
          return;
     }

     //Variabili temporanee
     char descrizione[31], corso[16];
     char temp[80], data_scadenza[11], tempo_stimato[9], tempo_passato[9];
     int priorita, id, stato;

    
     //LEGGE LE RIGHE DEL FILE REPORT
     while(fgets(temp, sizeof(temp), fp) != NULL){          //Se la riga non è vuota esce dal ciclo
        if (temp[0] == '\n' || temp[0] == '\0')
        continue;
          strncpy(descrizione, temp, 31);                   //Copia temp dentro descrizione     
          descrizione[30] = '\0';                           //Impone delimitatore per striga
          descrizione[strcspn(descrizione, "\n")] = '\0';   //Elimina il carattere di newline a fine riga
          
          if(fgets(temp, sizeof(temp), fp) == NULL) break;                   //Stesse operazioni ma con la seconda riga
          strncpy(corso, temp, 16);
          corso[15] = '\0';
          corso[strcspn(corso, "\n")] = '\0';

          if(fgets(temp, sizeof(temp), fp) == NULL) break;                    //Legge terza riga
          
          //Salva con sscanf il valore dei campi (separati appositamente da spazi) all'interno delle variabili temporanee
          if(sscanf(temp, "%10s %8s %8s %d %d %d", data_scadenza, tempo_stimato, tempo_passato, &priorita, &id, &stato) == 6) {
               if(strcmp(tempo_passato, "(null)") == 0)
                    strcpy(tempo_passato, "0:0:0");
               
               //Usa i campi presi dal file report, li passa in input a inserisci_item() per generarne un item e lo inserisce nella queue con insert()
               item a = inserisci_item(descrizione, corso, data_scadenza, tempo_stimato, tempo_passato, priorita, id, stato);
               if(insert(p, a) != 0)    //Controllo errore di inserimento
                    printf("Errore nell'aggiunta dell'item");
          }     
          else //Controllo errore parsing dei parametri per sscanf
               continue;
          
     }

return;
}


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
void scrivi_file_report_queue(pqueue p){
     if(p == NULL){ //Controllo puntatore a coda != NULL
          printf("Coda inesistente\n");
          return;
     }
     FILE* fp = fopen("test_suite/output1.txt", "w");
     if(fp == NULL){     //Controllo puntatore a file != NULL
        printf("Impossibile aggiungere attività al Report. Errore in apertura file.\n");
        return;
     }

     //Cicla per ogni elemento della queue (parte da 1 per l'heap a base 1)
     for(int i = 1; i <= p->numel; i++){
          //Passa l'item i-esimo della queue (ed il puntatore al file dove scrivere) alla funzione scrivi_file_report() 
          scrivi_file_report_item(p->vet[i], fp);
     }

     fclose(fp);

return;
}

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
int ottieni_id(pqueue p){
     if(!p){
          printf("Coda inesistente\n");
          return -1;
     }

     return p->numel + 1;     //Il numero dell'ultimo posto disponibile sarà l'id del nuovo elemento inserito

}

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
void stampa_id_queue(pqueue p){
     for(int i = 1; i <= p->numel; i++){     //Cicla per ogni elemento nella coda
          //Passa l'elemento i-esimo alla funzione di stampa
          stampa_id_item(p->vet[i]);
     }

return;
}

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
int aggiorna_file_attivita_queue(pqueue p){
     if(p == NULL){ //Controllo p != NULL
          printf("Errore aggiornamento attivita', coda inesistente\n");
          return -1;
     }
     //APRE FILES E CONTROLLA ERRORI IN APERTURA
     FILE* fp = fopen("files_txt/attivita.txt", "w");
     FILE* fp1 = fopen("files_txt/attivita_menu.txt", "w");
     if((fp == NULL)||(fp1 == NULL)){
          printf("Impossibile aggiornare tempo attività. Errore in apertura file.\n");
          
          //SE UNO DEI DUE SI APRE, MENTRE L'ALTRO è NULL, CHIUDE QUELLO APERTO E RESTITUISCE -1
          if(fp != NULL) fclose(fp);
          else if(fp1 != NULL) fclose(fp1);
          
          return -1;
     }

     //Cicla per ogni elemento della queue (parte da 1 per l'heap a base 1)
     for(int i = 1; i <= p->numel; i++){
          if (p->vet[i] != NULL) {
               //Passa l'item i-esimo della queue (ed il puntatore al file dove scrivere) alla funzione 
               if(aggiorna_file_attivita_item(p->vet[i], fp, fp1) == 1){
                    fclose(fp);
                    fclose(fp1);
                    
                    return 1;
               }
          }
     }

     fclose(fp);
     fclose(fp1);

return 0;
}

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
int modifica_tempo_queue(pqueue q, int id, double tempo_totale){
     if(q == NULL){ //Controllo p != NULL
          printf("Errore aggiornamento tempo attivita', coda inesistente\n");
          return -1;
     }              //Controlla validità id
     if (id < 1 || id > q->numel) {
          printf("Indice fuori dai limiti della coda: %d\n", id);
          return -1;
     }
     if(modifica_tempo(q->vet[id], tempo_totale) == 1) return 1;
     if(aggiorna_file_attivita_queue(q) == 1) return 1;

return 0;
}

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
int controlla_stato_attivita(pqueue q){
    if(q == NULL){ //Controllo p != NULL
          printf("Errore aggiornamento tempo attivita', coda inesistente\n");
          return -2;
    }        
    FILE* fp = fopen("test_suite/output1.txt", "w");
    for(int i = 1; i <= q->numel; i++){
        double z = stato_completamento_item(q->vet[i]);
            if(z > 100) z = 100;
        fprintf(fp, "%.2f\n", z);
    }

    fclose(fp);

//Se attività ancora in corso restituisce 1
return 1;
}

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
void aggiorna_ritardo(pqueue p, item a){
     //CICLA PER OGNI ELEMENTO NELLA CODA
     for(int i = 1; i <= p->numel; i++){
          if(confronta_item(a, p->vet[i]) == 0){       //Se trova un item uguale all'item a
               aggiorna_attivita_ritardo(p->vet[i]);   //Allora ne aggiorna lo stato
               break;
          }
     }

return;
}

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
item ottieni_item_attivita_per_report(pqueue q, int c){
     return q->vet[c];
}

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
void aggiorna_completata(pqueue p, item a){
     //CICLA PER OGNI ELEMENTO NELLA CODA
     for(int i = 1; i <= p->numel; i++){
          if(confronta_item(a, p->vet[i]) == 0){            //Se trova un item uguale all'item a
               aggiorna_attivita_completata(p->vet[i]);     //Allora ne aggiorna lo stato
               break;
          }
     }

return;
}

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
void aggiorna_id_ordine_queue(pqueue q){
     for(int i = 1; i <= q->numel; i++){
          aggiorna_id_ordine_item(q->vet[i], i);
     }

return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER RIMUOVERE UN'ATTIVITA' DALLA CODA ATTIVITA'
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
void rimuovi_item(pqueue q, int id){
     if(q == NULL){ //Controllo p != NULL
          printf("Errore rimozione attivita', coda inesistente\n");
          return;
     }        
     if (id < 1 || id > q->numel) {     //Controlla validità dell'id
          printf("Indice fuori dai limiti della coda: %d\n", id);
          return;
     }

     //Rimozione item
     item temp = q->vet[id];
     q->vet[id] = q->vet[q->numel];
     q->vet[q->numel] = temp;
     
     dealloca_item(q->vet[q->numel]);
     q->numel--;
     
     aggiorna_id_ordine_queue(q);
     aggiorna_file_attivita_queue(q);

return;
}

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
void rimuovi_item_report(pqueue p, item a){
     if((p == NULL)||(a == NULL)){ //Controllo p != NULL e a != NULL
          printf("Errore rimozione attivita', coda inesistente o attività inesistenti\n");
          return;
     }      
     //CICLA PER OGNI ELEMENTO NELLA CODA
     for(int i = 1; i <= p->numel; i++){
          if(confronta_item(a, p->vet[i]) == 0){            //Se trova un item uguale all'item a
               //Rimozione item
               item temp = p->vet[i];
               p->vet[i] = p->vet[p->numel];
               p->vet[p->numel] = temp;
               
               dealloca_item(p->vet[p->numel]);
               p->numel--;
               
               break;
          }
     }

return;
}