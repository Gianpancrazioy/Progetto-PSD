#ifdef _WIN32               //Pulizia schermo in caso di dispositivi Windows
    #include <windows.h>
    #define CLEAR "cls"
#else                       //Pulizia schermo in caso di dispositivi macOS o Linux
    #include <unistd.h>
    #define CLEAR "clear"
#endif

//------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#include "functions.h"
#include "time_functions.h"
#include "adt_pqueue.h"

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER METTERE IN PAUSA IL PROGRAMMA (PORTABILE)
/*
SPECIFICA SINTATTICA:
-   void (int) -> void
SPECIFICA SEMANTICA:
-   pausa (sec) -> void
PRE-CONDIZIONI:
-   sec è un numero intero compreso tra 0 ed il massimo di caratteri interi rappresentabili
POST-CONDIZIONI:
-   mette in pausa il programma per sec secondi
SIDE-EFFETCT:
-   Blocca l'esecuzione del programma per sec secondi
*/
void pausa(int sec){
    #ifdef _WIN32               //Pulizia schermo in caso di dispositivi Windows
        Sleep(sec * 1000);
    #else                       //Pulizia schermo in caso di dispositivi macOS o Linux
        sleep(sec);
    #endif

return;
}

//------------------------------------------------------------------------------------------------------------

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
void pulisci_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

return;
}

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
void pulisci_schermo(){
    system(CLEAR);
    
return;
}

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
void mostra_barra_avanzamento(double percentuale){
    int lunghezza_barra = 50;  // Lunghezza massima della barra
    int riempimento = (int)((percentuale / 100.0) * lunghezza_barra); //Calcola quanto della barra sarà riempito in base alla percentuale in input

    //STAMPA DELLA BARRA DI COMPLETAMENTO
    printf("[");
    for (int i = 0; i < lunghezza_barra; i++) {
        if (i < riempimento)
            printf("#");  // Parte completata
        else
            printf("-");  // Parte mancante
    }
    printf("] %.2f%%\n", percentuale);  //Stampa del valore della percentuale
    
return;
}

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
int controlla_file_vuoto(FILE* fp){
    int c = 0;

    if((c = fgetc(fp)) == EOF){                 //Legge il primo carattere nel file, se restituisce EOF il file è vuoto
        fclose(fp);
        return 1;                               //Restituisce 1 se il file è vuoto
    }

    rewind(fp);                                 //Se non è vuoto, fa rewind del puntatore e restituisce 0

return 0;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER STAMPARE TUTTE LE ATTIVITA' IN CORSO NEL MENU PRINCIPALE
/*
SPECIFICA SINTATTICA:
- static void (void) -> void

SPECIFICA SEMANTICA:
- stampa_attivita_menu (void) -> void

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Stampa a schermo, secondo una formattazione precisa, tutte le attività che legge dal file "attivita_menu.txt" 
    oppure stampa un messaggio se il file è vuoto

SIDE-EFFECTS:
- Stampa a schermo Tutte le attività presenti nel file "attivita_menu.txt" secondo un formato predefinito
- Stampa a schermo se non è presente nessuna attività nel file
- Stamoa a schermo in caso di errore fgets() o sscanf()
- Legge da file

*/
static void stampa_attivita_menu(){
    FILE* fp = fopen("files_txt/attivita_menu.txt", "r");
    if(fp == NULL){
        return;
    }
    if(controlla_file_vuoto(fp) == 1){                  //Chiama funzione per controllare se il file è vuoto
        printf("\n*-+-Nessuna attivita' \t\t\t*\n*\t\t\t\t\t*");      //Se è vuoto stampa "Nessuna attività", chiude il file e ritorna
        fclose(fp);
        return;
    }

    char data[11], status[11];
    int priorita, stato; 

    char buffer[80];                                    //Buffer per leggere dal file
    
    while(1){
        if(fgets(buffer, sizeof(buffer), fp) == NULL) break;            //Legge fino a che il file non è vuoto (fgets restituisce NULL)
            buffer[strcspn(buffer, "\n")] = '\0';                           //Elimina il carattere di ritorno '\n' dalla stringa letta nel buffer
            printf("\n*-+-%s.. \t\t\t*\n*", buffer);                          //Per evitare problemi

            if(fgets(buffer, sizeof(buffer), fp) == NULL) break;            //Stessa lettura per la seconda stringa da leggere
            
            if(sscanf(buffer, "%s %d %d", data, &priorita, &stato) != 3){   //sscanf separa i campi della stringa buffer in 3 variabili
                printf("Errore parsing parametri\n");                       //Gestione dell'errore numero dei parametri in sscanf
                break;
        }
        buffer[strcspn(buffer, "\n")] = '\0';                           
        
        if(stato == 1)                          //Se "Stato" = -1, 0 o 1, scrive "in ritardo", "Completata" o "In Corso" all'interno di status
            strcpy(status, "In Corso");
        else if(stato == -1)
            strcpy(status, "In Ritardo");
        else
            strcpy(status, "Completata");
        
        printf("-+-%.10s - %d - %s\t\t*\n*\t\t\t\t\t*", data, priorita, status);    //Stampa dei parametri con formattazione personalizzata per il menu
        //printf("\n*\t\t\t\t\t*\n")
    }

    fclose(fp);

return;
}

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
void mostra_menu(void){
    int ora, minuto, giorno, mese, anno;
    char* giorno_settimana = (char*) malloc (sizeof(char) * 10);

    ottieni_data_oggi(&ora, &minuto, &giorno, &mese, &anno, giorno_settimana);  //Chiamata a funzione di time_functions per ottenere la data di oggi

    pulisci_schermo();
    //COSTRUZIONE INTERFACCIA UTENTE
    printf("*****************************************\n*");
    printf("/\\/\\/\\/\\/\\/\\/|BENVENUTO!|/\\/\\/\\/\\/\\/\\/\\*\n");
    printf("*****************************************\n*");
    printf("/\\/\\/\\/\\/\\/\\/|DATA E ORA|/\\/\\/\\/\\/\\/\\/\\*\n");
    printf("*****************************************\n*");
    printf("      [%s - %d/%d/%d - %d:%d]\t*\n*****************************************\n*", 
            giorno_settimana, giorno, mese, anno, ora, minuto);    //Stampa data
    printf("/\\/\\/\\/\\/|ATTIVITA' IN CORSO|/\\/\\/\\/\\/\\*\n*****************************************\n*\t\t\t\t\t*");
    //RICHIAMO FUNZIONE PER STAMPARE ATTIVITA' IN CORSO DA FILES
    stampa_attivita_menu();
    
    printf("\n");
    printf("*****************************************\n*");
    printf("/\\/\\/\\/\\/|COSA SI VUOLE FARE?|/\\/\\/\\/\\/*\n*****************************************\n*\t\t\t\t\t*\n");
    printf("*1) Aggiungere Attivita'.-------+-------*\n*\t\t\t\t\t*\n*---+---2) Generare report settimanale.\t*\n*\t\t\t\t\t*\n*"
            "3) Lavorare su un'Attivita'.-----+-----*\n*\t\t\t\t\t*\n*--+--4) Stampare tutte le attivita'\t*\n*\t Per priorita'"
            " decrescente--+---*\n*\t\t\t\t\t*\n*5) Controlla Percentuale\t\t*\n*\tCompletamento---+---+---+---+---*\n*\t\t\t\t\t*\n*----+----"
            "6) Aggiorna Completamento\t*\n*\t\t\tAttivita'.--+---*\n*\t\t\t\t\t*\n*7) Rimuovi un'attivita'.---+---+---+---*\n*\t\t\t\t\t*\n*"
            "----+----+----8) Chiudi l'applicazione.*");
    printf("\n*\t\t\t\t\t*\n");
    printf("*****************************************\n");

return;
}

//------------------------------------------------------------------------------------------------------------


