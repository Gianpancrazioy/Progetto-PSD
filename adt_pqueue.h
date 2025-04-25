typedef struct c_PQ* pqueue;

//FUNZIONE PER CREARE NUOVA CODA A PRIORITÀ
/*
SPECIFICA SINTATTICA:
pqueue (void) -> pqueue

SPECIFICA SEMANTICA:
newPQ (void) -> q

PRECONDIZIONI:
- Nessuna

POSTCONDIZIONI:
- Restituisce un puntatore ad una priority queue "q" allocata dinamicamente.
*/
pqueue newPQ(void);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER ESPANDERE CODA A PRIORITÀ
/*
SPECIFICA SINTATTICA:
pqueue (pqueue) -> pqueue

SPECIFICA SEMANTICA:
expand_heap (q) -> q

PRECONDIZIONI:
- Puntatore in input valido, coda esistente

POSTCONDIZIONI:
- Restituisce un puntatore a priority queue "q" con memoria per l'heap += MAXPQ.
*/
pqueue expand_heap(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CONTROLLARE SE LA CODA A PRIORITÀ È VUOTA 
/*
SPECIFICA SINTATTICA:
int (pqueue) -> int

SPECIFICA SEMANTICA:
emptyPQ (q) -> q->numel

PRECONDIZIONI:
- Puntatore in input valido, coda esistente

POSTCONDIZIONI:
- Restituisce 1 se la coda è vuota, 0 altrimenti.
*/
int emptyPQ(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE L'ELEMENTO DI PRIORITÀ MAGGIORE NELLA CODA 
/*
SPECIFICA SINTATTICA:
item (pqueue) -> item

SPECIFICA SEMANTICA:
getMax (q) -> q->vet[1]

PRECONDIZIONI:
- Nessuna, controllo coda vuota o inesistente già effettuati

POSTCONDIZIONI:
- Restituisce l'item di priorità maggiore nella coda, NULL se la coda è vuota
- Restituisce NULL in caso di coda vuota o inesistente
*/
item getMax(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER ELIMINARE L'ELEMENTO DI PRIORITÀ MAGGIORE NELLA CODA 
/*
SPECIFICA SINTATTICA:
int (pqueue) -> int

SPECIFICA SEMANTICA:
deleteMax (q) -> 0 / 1

PRECONDIZIONI:
- Nessuna, controllo coda vuota o inesistente già effettuati

POSTCONDIZIONI:
- Rimuove l'item di priorità maggiore nella coda, restituisce 0 se operazione riuscita, 1 altrimenti
- Restituisce NULL in caso di coda vuota o inesistente
*/
int deleteMax(pqueue q);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER INSERIRE UN NUOVO ELEMENTO NELL'HEAP 
/*
SPECIFICA SINTATTICA:
int (pqueue, item) -> int

SPECIFICA SEMANTICA:
deleteMax (q, key) -> 0 / 1

PRECONDIZIONI:
- Nessuna, controllo coda piena o inesistente già effettuati

POSTCONDIZIONI:
- Inserisce un nuovo item nella coda, restituisce 0 se operazione riuscita, 1 altrimenti
- Restituisce NULL in caso di coda inesistente o se fallisce realloc in caso di coda piena
*/
int insert(pqueue q, item key);