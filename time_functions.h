//FUNZIONE PER OTTENERE LA DATA ODIERNA
/*
SPECIFICA SINTATTICA:
void (int*, int*, int*, int*, int*, char*) -> void

SPECIFICA SEMANTICA:
ottieni_data_oggi (ora, minuto, giorno, mese, anno, giorno_settimana) -> void

PRE-CONDIZIONI:
- ora: Puntatore in input valido
- minuto: Puntatore in input valido
- giorno: Puntatore in input valido
- mese: Puntatore in input valido
- anno: Puntatore in input valido
- giorno_settimana: Puntatore in input valido

POST-CONDIZIONI:
- Salva nelle variabili puntate dai puntatori in input i valori di ora, minuto, giorno, mese e anno presi da struct_tm,
    mentre salva il giorno della settimana corrispondente a indice_giorno in giorno_settimana

SIDE EFFECT:
- I valori delle variabili puntate dai puntatori in input saranno modificati nel main
*/
void ottieni_data_oggi(int* ora, int* minuto, int* giorno, int* mese, int* anno, char* giorno_settimana);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CONFRONTARE LA SETTIMANA CORRENTE CON QUELLA DELL'ULTIMO FILE REPORT
/*
SPECIFICA SINTATTICA:
int (void) -> int

SPECIFICA SEMANTICA:
confronta_settimana (void)  -> -1:  In caso di errore in apertura files
                            ->  0:  In caso di conclusione della funzione senza aggiornamento file
                            ->  1:  In caso di conclusione della funzione con aggiornamento file

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Restituisce 1 se la settimana è diversa da quella dell'ultimo report, 0 altrimenti.
- Oltretutto, se i valori sono diversi, azzera il report ed aggiorna il numero nel file num_settimana

SIDE-EFFECT:
- Stampa a schermo in caso di errore
- Scrittura su file in caso di aggiornamento del file
- Lettura da file

*/
int confronta_settimana(int* nuova_settimana);

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER FAR PARTIRE CRONOMETRO E PRENDERE TEMPO DI LAVORO TOTALE IN UNA SESSIONE
/*
SPECIFICA SINTATTICA:
char* (char*, double*) -> char*

SPECIFICA SEMANTICA:
cronometro (stringa, tempo_totale) -> stringa

PRE-CONDIZIONI:
- I puntatori in input sono validi

POST-CONDIZIONI:
- Stampa il tempo secondo per secondo fino a quando la funzione kbhit() non rileva un carattere nel buffer 
    e restituisce la stringa composta da ORE:MINUTI:SECONDI di lavoro

SIDE-EFFECT:
- Stampa a schermo il valore del tempo secondo per secondo con formattazione personalizzata
- La stringa in input viene modificata
- Il valore di tempo_totale nella funzione caller viene modificato
*/
char* cronometro(char* stringa, double* tempo_totale);