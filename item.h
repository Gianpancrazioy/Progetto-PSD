#ifndef ITEM_H
#define ITEM_H
typedef struct attivita_studio *item;
#endif

#include "adt.h"

#define NULLITEM 0

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*Funzione che permetta di aggiungere in ADT "attivita_studio" descrizione, nome corso, data scadenza, tempo stimato e priorità di un'attività.

SPECIFICA SINTATTICA:
- int (list) -> int

SPECIFICA SEMANTICA:
- aggiungi (l) -> n

PRECONDIZIONI:
- La lista passata in input esiste, il puntatore è valido

POSTCONDIZIONI:
- La funzione aggiungerà un item alla lista "l", poi restituirà "n = 1" se c'è stato un errore, "n = 0" in caso di aggiunta riuscita

EFFETTI COLLATERALI:
- La lista in input sarà modificata con l'aggiunta di una nuova attività di studio.

*/
int aggiungi (lista l);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*Funzione per visualizzare stato completamento di una data attività in base a "tempo_stimato".

SPECIFICA SINTATTICA:
- int (list, int, float) -> int

SPECIFICA SEMANTICA:
- stato_completamento (l, id, tempo) -> n

PRECONDIZIONI:
- La lista passata in input esiste, il puntatore è valido
- Il valore di "tempo" è positivo

POSTCONDIZIONI:
- La funzione prende in input un la lista "l", l'identificativo "id" e la durata di un'attività "tempo", trova l'attività in base alla posizione
    nella lista e compara "tempo" con "tempo_stimato", stampando la percentuale di completamento dell'attività "stato".
*/
int stato_completamento (lista l, int id, float tempo);

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

/*Funzione per generare report settimanali"

SPECIFICA SINTATTICA:
- void (list) -> void

SPECIFICA SEMANTICA:
- genera_report (l) -> void

PRECONDIZIONI:
- La lista passata in input esiste, il puntatore è valido

POSTCONDIZIONI:
- La funzione prende in input un la lista "l" e crea un file chiamato "report_seettimana.txt", nel quale scrive descrizione, nome corso e stato completamento.

*/
void genera_report(lista l);