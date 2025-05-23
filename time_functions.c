#ifdef _WIN32               //Se si è su sistemi Windows:
    #include <conio.h>      //In caso include conio.h, header per funzioni di gestione dell'input / output da console
    #define CLEAR "cls"     //Definisce anche la macro CLEAR = alla stringa letterale "cls" per pulire lo schermo
#else           
    //Se si è su sistemi macOS o Linux:
    #include <termios.h>    //header per disabilitare e riabilitare il buffering del terminale
    #include <sys/select.h> //header per leggere da terminale senza bloccare il programma
    #define CLEAR "clear"   //Definisce anche la macro CLEAR = alla stringa letterale "clear" per pulire lo schermo
    
    //------------------------------------------------------------------------------------------------------------------------------------------

    // Funzione per disabilitare buffering del terminale (modalità raw)
    /*
    SPECIFICA SEMANTICA:
    - void (struct termios*) -> void
    
    SPECIFICA SINTATTICA:
    - disabilita_buffer (old)  ->  void
    
    PRE-CONDIZIONI:
    - Puntatore in input valido
    
    POST-CONDIZIONI:
    - Genera una nuova impostazione per il terminale stdin e la imposta come predefinita
    
    SIDE-EFFECTS:
    - Modifica le impostazioni di stdin

    */
    void disabilita_buffer(struct termios *old) {
        struct termios new;                     //Definisce una nuova struct per le impostazioni del terminale
        tcgetattr(STDIN_FILENO, old);           //Salva le impostazioni attuali di stdin nella struttura old
        new = *old;                             //Assegna ai campi della nuova struct i campi di old
        new.c_lflag &= ~(ICANON | ECHO);        //Disabilita nelle nuove impostazioni la lettura riga per riga e l'eco dei caratteri su stdout
        tcsetattr(STDIN_FILENO, TCSANOW, &new); //Imposta immediatamente le nuove impostazioni di stdin come predefinite

    return;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    //Funzione per ripristinare il buffering da terminale
    /*
    SPECIFICA SEMANTICA:
    - void (struct termios*) -> void
    
    SPECIFICA SINTATTICA:
    - ripristina_buffer (old)  ->  void
    
    PRE-CONDIZIONI:
    - Puntatore in input valido
    
    POST-CONDIZIONI:
    - Resetta le impostazioni di stdin utilizzando quelle contenute nel puntatore a struct in input
    
    SIDE-EFFECTS:
    - Modifica le impostazioni di stdin

    */
    void ripristina_buffer(struct termios *old) {
        tcsetattr(STDIN_FILENO, TCSANOW, old);  //Applica immediatamente le vecchie impostazioni contenute in old al terminale stdin
    
    return;
    }

    //------------------------------------------------------------------------------------------------------------------------------------------

    //Funzione per leggere caratteri da terminale senza bloccare il flusso del programma
    /*
    SPECIFICA SEMANTICA:
    - int (void) -> int
    
    SPECIFICA SINTATTICA:
    - kbhit (void)  ->  1: Se c'`un input nel buffer
                    ->  0: Nessun input nel buffer
                    -> -1: In caso di errore
    
    PRE-CONDIZIONI:
    - Nessuna
    
    POST-CONDIZIONI:
    - Verifica se ci sono input nel buffer senza bloccare il programma, se ce ne sono restituisce 1
    
    SIDE-EFFECTS:
    - Legge da stdin

    */
    int kbhit(){
        struct timeval tv = {0L, 0L};   //Imposta timeout a 0 (non blocca il programma)
        fd_set fds;
        FD_ZERO(&fds);                  //Azzera il set
        FD_SET(STDIN_FILENO, &fds);     //Aggiunge stdin al set
        return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    }
#endif

//------------------------------------------------------------------------------------------------------------------------------------------

#include <time.h>       //Libreria per lavore col tempo
#include <stdio.h>      //Libreria per funzioni standard di input / output
#include <stdlib.h>     //Libreria per funzioni di manipolazione della memoria
#include <string.h>     //Libreria per manipolazioen delle stringhe
#include <unistd.h>     //Libreria per implementare funzione di pausa

#include "time_functions.h"

//------------------------------------------------------------------------------------------------------------------------------------------

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
void ottieni_data_oggi(int* ora, int* minuto, int* giorno, int* mese, int* anno, char* giorno_settimana){
    const char* giorni_settimana[] = {                 //Array contenente i giorni della settimana
    "Lunedi'", "Martedi'", "Mercoledi'",
    "Giovedi'", "Venerdi'", "Sabato", "Domenica"
    };
    
    time_t tempo_base;  
    struct tm* tempo;
    time(&tempo_base);  //Prende il tempo_base tramite time()
    tempo = localtime(&tempo_base); //salva nella struct tm* tempo i valori di tempo_base tramite localtime()

    //Usa la struct tempo per riempire le variabili puntate dai puntatori in input
    *ora = tempo->tm_hour;
    *minuto = tempo->tm_min;
    *giorno = tempo->tm_mday;
    *mese = tempo->tm_mon + 1;
    *anno = tempo->tm_year + 1900;

    //Salva il giorno della settimana corrente tramite indice_giorno nella variabile puntata da giorno_settimana
    int indice_giorno = (tempo->tm_wday + 6) % 7;
    int s = strlen(giorni_settimana[indice_giorno]);

    strcpy(giorno_settimana, giorni_settimana[indice_giorno]);
    giorno_settimana[s] = '\0'; 
    
return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE IL NUMERO DELLA SETTIMANA NELL'ANNO CORRENTE (VISIBILE SOLO NEL FILE)
/*
SPECIFICA SINTATTICA:
- static int (struct tm*) -> int

SPECIFICA SEMANTICA:
- settimana_anno (tempo) -> atoi(buffer) = Converte in intero la stringa buffer e la restituisce

PRE-CONDIZIONI:
- Il puntatore in input esiste ed è valido

POST-CONDIZIONI:
- Restituisce il numero della settimana dell'anno corrente secondo il formato ISO

SIDE EFFECT:
- Nessuno
*/
static int settimana_anno(struct tm *tempo) {
    char buffer[3];     //Buffer per contenere la stringa restituita da strftime
    
    //Usa strftime per ottenere il numero della settimana in base al formato ISO
    strftime(buffer, sizeof(buffer), "%U", tempo);  // "%U" inizia la settimana con la domenica
    
return atoi(buffer);                                //Converte la stringa buffer in un intero e lo restituisce

//static int settimana_anno(struct tm *tempo) {
    // Calcola la settimana dell'anno in base al giorno dell'anno (tm_yday)
 //   return (tempo->tm_yday / 7) + 1;    //prende il giorno dell'anno, divide per 7 per ottenere il  numero della settimana
                                        //ed aggiunge 1 per evitare di ottenere un errore come "settimana 0"
//}
}

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
int confronta_settimana(int* nuova_settimana){
    if(nuova_settimana == NULL){    //Controllo validità puntatore in input
        printf("Errore col puntatore passato\n");
        return -1;
    }
    int num_settimana = 0;
    time_t ora = time(NULL);
    struct tm *tempo = localtime(&ora);

    //Richiamo alla funzione per ottenere la settimana corrente
    (*nuova_settimana) = settimana_anno(tempo);

    //Apertura del file dove è scritto il numero della settimana dell'ultimo report
    FILE* fp = fopen("files_txt/num_settimana.txt", "r");
    //Controllo errore apertura file
    if(fp == NULL){
        printf("Errore in apertura file\n");
        return -1;
    }

    //Controllo se file è vuoto o impossibile da leggere
    if(fscanf(fp, "%d", &num_settimana) != 1){
        printf("Impossibile leggere dal file \"num_settimana.txt\", file vuoto.\nOra verrà aggiornato ed il file report azzerato\n");
        fclose(fp);

        fp = fopen("files_txt/num_settimana.txt", "w");
        if(fp == NULL){
            printf("Errore in apertura file\n");
            return -1;
        }

        fprintf(fp, "%d", *nuova_settimana);
        return -1;
    } 

    if(*nuova_settimana != num_settimana){   //Confronta numero settimana corrente con la prima riga scritta nel file num_settimana
        //Se i due numeri non sono uguali, aggiorna il file num_settimana ed azzera il file report_settimanale
        fclose(fp);
        
        //Aggiorna il numero della settimana nel file num_settimana
        fp = fopen("files_txt/num_settimana.txt", "w");
        //Controllo errore apertura file
        if(fp == NULL){
            printf("Errore in apertura file\n");
            return -1;
        }
        fprintf(fp, "%d", *nuova_settimana);
        fclose(fp);

        //Azzera il contenuto del file report settimanale
        fp = fopen("files_txt/report_settimanale.txt", "w");
        if(fp == NULL){
            printf("Errore in apertura file.\n");
            return -1;
        }
        fclose(fp);

        return 1;   //Restituisce 1 se aggiorna il file
    }

    fclose(fp);

return 0;   //Restituisce 0 se non aggiorna il file
}

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
char* cronometro(char* stringa, double* tempo_totale){
    time_t inizio, fine;    //Variabili per calcolare tempo di esecuzione
    
    inizio = time(0);   //Registra l'istante in cui inizia l'esecuzione della funzione
    
    #ifndef _WIN32                      //Disattiva il terminale line buffered se su macOS
        struct termios old_settings;
        disabilita_buffer(&old_settings);
    #endif

    int h = 0, m = 0, s = 0;

    while(1){
        sleep(1);               //Aspetta un secondo prima di eseguire la prossima istruzione
        system(CLEAR);          //Pulisce il terminale

        s+=1;                   //Incrementa il numero dei secondi di 1
        printf("**************************\n*");
        printf("--------%02d:%02d:%02d--------*\n", h, m, s);
        printf("**************************\n");
        printf("Premi un tasto per smettere\n");

        if(s > 59){            //Aggiorna minuti
            m += 1;
            s = 0;
        }

        if(m > 59){            //Aggiorna ore
            h += 1;
            m = 0;
        }

        if(h > 98){            //Controllo tempo massimo (99 ore)
            printf("Raggiunto limite massimo di tempo, uscita dal programma\n");
            break;
        }

        //CONTROLLA SE NEL BUFFER SI TROVA UN QUALSIASI TIPO DI INPUT, SE LO TROVA ALLORA LO LEGGE E INTERROMPE IL CRONOMETRO
        #ifdef _WIN32
            if(_kbhit()){   //Versione per Windows
                _getch();   
                break;
            }
        #else
            if(kbhit()){    //Versione per macOS e Linux
                getchar();   
                break;
            }
        #endif
    }

    sprintf(stringa, "%02d:%02d:%02d", h, m, s);        //Concatena i valori di h, m , s in un'unica stringa letterale
    
    fine = time(0); //Registra l'istante in cui termina l'esecuzione della funzione
    
    //Aggiorna il valore puntato da tempo_totale con il tempo di esecuzione della funzione
    *tempo_totale = difftime(fine, inizio); //difftime() restituisce la differenza in secondi tra fine ed inizio esecuzione
    
    #ifndef _WIN32                          //Ri-abilita il terminale line buffered
        ripristina_buffer(&old_settings);
    #endif

return stringa;
}