#include <stdio.h>
#include <stdlib.h>

#include "adt_pqueue.h"  // Inclusione dell'header file per la coda di priorità.
#include "item.h"        // Inclusione dell'header file per l'item.

#define MAXPQ 50         // Definizione della dimensione massima dell'heap.

// Definizione della struttura per la coda di priorità.
struct c_PQ {
     item* vet;          // Array per memorizzare gli elementi dell'heap. Allocazione dinamica.
     item val;           // Valore di ogni elemento.
     int numel;          // Numero attuale di elementi nell'heap.
};

// Dichiarazione delle funzioni statiche per la manipolazione dell'heap.
static void scendi (pqueue q);
static void sali (pqueue q); 

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per creare una nuova coda di priorità.
pqueue newPQ(void){
     pqueue q;

     q = malloc(sizeof(struct c_PQ));         // Allocazione della memoria per la coda.
     if(q == NULL){                           // Controlla Errore allocazionw memoria.
          printf("Errore allocazione memoria in fase di creazione coda.\n");
          return 1;
     }
     
     q->vet = malloc (sizeof(item) * MAXPQ);  // Allocazione della memoria per l'heap.
     if(q == NULL){                           // Controlla Errore allocazionw memoria.
          printf("Errore allocazione spazio per l'heap.\n");
          return 1;
     }
     q->numel = 0;                            // Inizializzazione del numero di elementi a zero.

return q;                                    // Ritorno del puntatore alla coda.
}

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per gestire riallocazione dinamica di memoria per array dinamico.
pqueue expand_heap(pqueue q){

     q->vet = (item*) realloc (q, (sizeof(q->vet)/sizeof(item)) + MAXPQ);  // Rialloca l'array aggiungendo MAXPQ spazi.
     if(q->vet == NULL) return NULL;                                       // Gestione errore realloc.

return q;
}

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per controllare se la coda è vuota.
int emptyPQ(pqueue q){

     if (!q){                                // Verifica se il puntatore è NULL.
          printf("Errore, coda inesistente.\n"); 
          return 1;
     }
return q->numel == 0;                        // Ritorna vero se la coda è vuota.
}

// Funzione per ottenere il massimo elemento dalla coda di priorità.
item getMax(pqueue q){
     if (!q || q->numel == 0){               // Controlla se la coda è vuota o il puntatore è NULL 
          printf("Errore, coda vuota o inesistente.\n");
          return NULL;   
     }

return q->vet[1];                            // Resituisce l'elemento al primo indice (massimo in un max-heap).
}

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per eliminare l'elemento massimo dalla coda di priorità.
item deleteMax(pqueue q){
     
     if (!q || q->numel == 0){          // Controlla se la coda è vuota o il puntatore è NULL.
          printf("Errore, coda vuota o inesistente.\n");
          return 1;
     } 

     q->vet[1] = q->vet[q->numel];      // Sostituisce la radice con l'ultimo elemento.
     q->numel--;                        // Decrementa il numero di elementi.

     scendi(q);                         // Riaggiusta l'heap scendendo l'elemento sostituito.
     
return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per riaggiustare l'heap verso il basso.
static void scendi(pqueue q){
    int temp, n = q->numel, i = 1, pos;

    while (1){
          // Determina la posizione del figlio con il valore più grande.
          if (2*i + 1 <= n)                                                 // Se il nodo corrente ha due figli.
               pos = (q->vet[2*i] > q->vet[2*i + 1]) ? 2*i : 2*i + 1;
          else if (2*i <= n)                                                // Se il nodo corrente ha solo un figlio.
               pos = 2*i;
          else 
               break;                                                       // Se non ha figli, interrompe il ciclo.

          // Scambia i valori se il figlio ha un valore più grande.
          if (q->vet[pos] > q->vet[i]){
               temp = q->vet[i];
               q->vet[i] = q->vet[pos];
               q->vet[pos] = temp;
               i = pos;                                                     // Continua a scendere nell'heap.
          }
          else
               break;                                                       // Termina se non sono necessari altri scambi.
     }

return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per inserire un nuovo elemento nell'heap.
int insert(pqueue q, item key){
     if (!q){                                // Verifica se il puntatore è NULL.
          printf("Errore, coda inesistente.\n"); 
          return 1;
     }                       
     if (((q->numel)%MAXPQ) == 0)            // Controlla se l'heap è pieno, in caso chiama funzioe di espansione heap.
          expand_heap(q);
     if(q == NULL){                          // Controlla se la riallocazione dell'heap è andata a buon fine.
          printf("Errore riallocazione spazio per l'heap nella funzione di inserimento.\n");
          return 1;
     }

     q->numel++;                             // Incrementa il numero di elementi.
     q->vet[q->numel] = key;                 // Inserisce il nuovo elemento all'ultima posizione.

     sali(q);                                // Riaggiusta l'heap risalendo l'elemento inserito.
     return 0;
}

//------------------------------------------------------------------------------------------------------------------------------------------

// Funzione per riaggiustare l'heap verso l'alto.
static void sali(pqueue q){
     int temp, pos = q->numel, i = pos / 2;

     while (pos > 1){
          // Se l'elemento inserito è maggiore del suo genitore, scambia i loro valori.
          if (q->vet[pos] > q->vet[i]){
               temp = q->vet[i];
               q->vet[i] = q->vet[pos];
               q->vet[pos] = temp;
               pos = i;
               i = pos / 2;                   // Continua a salire nell'heap.
          }
          else
               break;                         // Termina se non sono necessari altri scambi.
     }

return;
}