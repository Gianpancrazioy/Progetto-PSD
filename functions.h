#include <stdio.h>

//FUNZIONE PER PULIRE IL BUFFER
/*
SPECIFICA SINTATTICA:
- void (void) -> void

SPECIFICA SEMANTICA:
- pulisci_buffer (void) -> void

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Svuota il buffer dei caratteri da eventuali caratteri rimasti all'interno, fino a trovare un newline ('\n') o un end-of-file (EOF)

SIDE-EFFECTS:
_ Legge da stdin

*/
void pulisci_buffer();

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER PULIRE LO SCHERMO
/*
SPECIFICA SINTATTICA:
- void (void) -> void

SPECIFICA SEMANTICA:
- pulisci_schermo (void) -> void

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Utilizza il comando system(CLEAR), adattato sia a Windows che Linux / macOS, per pulire il terminale in fase di stampa

SIDE-EFFECTS:
- Pulisce il terminale stdout tramite un comando system()

*/
void pulisci_schermo();

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER MOSTRAREGRAFICAMENTE UNA PERCENTUALE DI AVANZAMENTO PASSATA IN INPUT TRAMITE BARRA DI CARICAMENTO GRAFICA
/*
SPECIFICA SINTATTICA:
- void (double) -> void

SPECIFICA SEMANTICA:
- mostra_barra_caricamento (percentuale) -> void

PRE-CONDIZIONI:
- percentuale in input è un valore compreso tra 0 e 100

POST-CONDIZIONI:
- Stampa a schermo una barra di caricamento con annessa percentuale di completamento ottenuta in base al valore di percentuale in input

SIDE-EFFECTS:
- Stampa a schermo una barra di caricamento grafica con valore della percentuale di completamento

*/
void mostra_barra_avanzamento(double percentuale);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CONTROLLARE SE IL FILE PASSATO IN INPUT E' VUOTO
/*
SPECIFICA SINTATTICA:
- int (FILE*) -> int

SPECIFICA SEMANTICA:
- controlla_file_vuoto (fp)     -> 0: Se il file non è vuoto
                                -> 1: Se il file è vuoto

PRE-CONDIZIONI:
- Puntatore a file in input valido

POST-CONDIZIONI:
- Legge il primo carattere da un file in input, se c == EOF, chiude il file e restituisce 1, altrimenti fa rewind() per 
    riportare il puntatore all'inizio del file e restituisce 0

SIDE-EFFECTS:
- Legge da file in input
- Fa rewind del file da cui ha letto

*/
int controlla_file_vuoto(FILE* fp);

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER MOSTRARE IL MENU PRINCIPALE
/*
SPECIFICA SINTATTICA:
- void (void) -> void

SPECIFICA SEMANTICA:
- mostra_menu (void) -> void

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Stampa a schermo un menu con varie informazioni per l'utente e formattazione personalizzata

SIDE-EFFECTS:
- Stampa a schermo un menu
- Stampa data e ora odierne tramite ottieni_data_oggi()
- Pulisce il terminale stdout tramite pulisci_schermo()
- Stampa da file tramite stampa_attivita_menu()

*/
void mostra_menu(void);