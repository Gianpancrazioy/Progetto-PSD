#include <stdio.h>
#include <stdlib.h>
#include "adt.h"
#include "item.h"

struct list{
    nodo head;
    nodo tail;
};

struct node{
    int value;
    nodo next;
};

//FUNZIONE PER CREARE UNA NUOVA LISTA:
/*
LISTA (VOID) --> LISTA
newlista (void) --> new

La funzione crea un puntatore a lista "new", lo inizializza a NULL e lo restituisce.
*/
lista newlist() {
    lista new = (lista) malloc(sizeof(struct list));
    if (new == NULL) {
        printf("Errore: memoria insufficiente\n");
        return NULL;
    }

    new->head = NULL;
    new->tail = NULL;

    return new;
}

//FUNZIONE PER AGGIUNGERE UN ELEMENTO IN TESTA AD UNA LISTA:
/*
LISTA (LISTA, INT) --> LISTA
remfirst (l, v) --> 1 oppure 0

La funzione prende in input una lista "l", aggiunge "v" in testa, poi restituisce "0" se l'operazione è riuscita, "1" altrimenti.
*/
int addfirst(lista l, int v) {
    if (l == NULL) {
        printf("Errore: lista non valida\n");
        return 1;
    }

    nodo new = (nodo) malloc(sizeof(struct node));
    if (new == NULL) {
        printf("Errore: memoria insufficiente\n");
        return 1;
    }

    new->value = v;

    if (l->head != NULL) {
        new->next = l->head;
        l->head = new;
    } else {
        new->next = NULL;
        l->head = l->tail = new;
    }

    return 0;
}

//FUNZIONE PER RIMUOVERE IL PRIMO ELEMENTO DA UNA LISTA:
/*
LISTA (LISTA) --> INT
remfirst (l) --> 1 oppure 0

La funzione prende in input una lista "l", controlla che non sia vuota, poi restituisce "0" se l'operazione non è riuscita, "1" altrimenti.
*/
int remfirst(lista l){

    if(l->head==NULL){
        printf("Errore, lista vuota o inesistente\n");
        return 1;
    }

    l->head = l->head->next;

    return 0;
}

//FUNZIONE PER STAMPARE UNA LISTA:
/*
VOID (LISTA) --> VOID
printlist (l) --> VOID

La funzione prende in input una lista "l", controlla che non sia vuota, poi stampa i valori dei singoli nodi (tutti).
*/
void printlist(lista l){

    if(l->head==NULL){
        printf("Errore, lista vuota o inesistente\n");
        return;
    }

    nodo temp = l->head;

    while(temp != NULL){
        printf("[%d]\n", temp->value);
        temp = temp->next;
    }

return;
}

