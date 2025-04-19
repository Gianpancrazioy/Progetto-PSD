#ifndef ITEM_H
#define ITEM_H
typedef struct attivita_studio *item;
#endif

#include <"adt.h">

#define NULLITEM 0

/*Funzione che permetta di aggiungere in ADT "attività di studio"

SPECIFICA SINTATTICA:
- int (list) -> int

SPECIFICA SEMANTICA:
- aggiungi (l) -> n

PRECONDIZIONI:
- La lista passata in input esiste, il puntatore è valido

POSTCONDIZIONI:
- La funzione aggiungerà un item alla lista "l", poi restituirà "n = 1" se c'è stato un errore, "n = 0" in caso di aggiunta riuscita

*/
int aggiungi (lista l);

/*Funzione per visualizzare stato completamento in base a tempo stimato"

SPECIFICA SINTATTICA:
- int (list, int, float) -> int

SPECIFICA SEMANTICA:
- stato_completamento (l, id, tempo) -> n

PRECONDIZIONI:
- La lista passata in input esiste, il puntatore è valido
- Il valore di "tempo" è positivo

POSTCONDIZIONI:
- La funzione prende in input un la lista "l" e l'identificativo "i"d", trova l'attività in base alla posizione nella lista e compara
    "tempo" con "tempo_stimato", stampando la percentuale di completamento dell'attività "stato" e se l'attività è completata ("n" = 0),
    in corso ("n" = 1), in ritardo ("n = 2")

*/
int stato_completamento (lista l, int id, float tempo);

/*Funzione per generare report settimanali"

SPECIFICA SINTATTICA:
- int (list, int) -> int

SPECIFICA SEMANTICA:
- genera_report (l) -> stato

PRECONDIZIONI:
- La lista passata in input esiste, il puntatore è valido

POSTCONDIZIONI:
- La funzione prende in input un la lista "l" e l'identificativo "i"d", trova l'attività in base alla posizione nella lista e compara il
    tempo trascorso col tempo stimato, restituendo un intero uguale alla percentuale di completamento dell'attività "stato"

*/