#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "item.h"
#include "functions.h"
#include "time_functions.h"

//-------------------------------------------------------------------------------------

//DEFINIZIONE DELLA STRUTTURA PER ATTIVITA' DI STUDIO
struct attivita_studio{
    int id;                 //Identificatore posizionale dell'attività nell'array
    char* descrizione;      //Descrizione attività di studio
    char* corso;            //Nome del corso
    char* data_scadenza;    //formato DD/MM/AAAA
    char* tempo_stimato;    //formato HH:MM:SS
    char* tempo_passato;    //formato HH:MM:SS
    int priorita;           //Valori da 0 (bassa) a 3 (alta) per livello di priorità
    int stato;              //Valori da -1 a 1 -> (In Ritardo, Completato, In Corso) 
};

//-------------------------------------------------------------------------------------

//FUNZIONE PER CREARE ED ALLOCARE DINAMICAMENTE UN NUOVO ITEM CON PARAMETRI ANNESSI
/*
SPECIFICA SINTATTICA:
- item (void) -> item

SPECIFICA SEMANTICA:
- nuovo_item (void) -> a

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Alloca memoria per un item a, e per tutti i suoi campi, e lo restituisce

SIDE-EFFECTS:
- Stampa a schermo in caso di errore

*/
item nuovo_item(){
    item a = (item) malloc (sizeof(struct attivita_studio));    //Allocazione della struttura
    
    //Allocazione dinamica di tutti i campi
    a->id = 0;                          
    a->corso = (char*) malloc (sizeof(char)*16);
    a->descrizione = (char*) malloc (sizeof(char)*31);
    a->data_scadenza = (char*) malloc (sizeof(char) * 11);
    a->tempo_stimato = (char*) malloc (sizeof(char) * 9);
    a->tempo_passato = (char*) malloc (sizeof(char) * 9);

    if ((!a->descrizione) || (!a->corso) || (!a->data_scadenza) || (!a->tempo_stimato) || (!a->tempo_passato)) {
        printf("Errore allocazione campi item\n");
        // Libera tutto in caso di errore per evitare memory leak
        free(a->corso); free(a->descrizione); free(a->data_scadenza); free(a->tempo_stimato); free(a->tempo_passato);
        free(a);
        return NULL;
    }

    strcpy(a->tempo_passato, "0:0:0");                          //Formattazione di a->tempo_passato a 0:0:0 siccome l'item è nuovo
    a->priorita = 0;
    a->stato = 1;

return a;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PRE DEALLOCARE MEMORIA PER UN ITEM PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- dealloca_item (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- La memoria allocata per i campi dell'item in input viene deallocata

SIDE-EFFECTS:
- Nessuno

*/
void dealloca_item(item a){
    if(a == NULL) return;

    free(a->descrizione);
    free(a->corso);
    free(a->data_scadenza);
    free(a->tempo_stimato);
    free(a->tempo_passato);

    free(a);

return;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER COPIARE UN ITEM PASSATO IN INPUT ALL'INTERNO DEI FILE ATTIVITA
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- scrivi_file_attivita (a) -> void

PRE-CONDIZIONI:
- Nessuna, controlli già effettuati nella funzione

POST-CONDIZIONI:
- Se l'item è valido e l'apertura dei files va a buon fine, avvia un'operazione di scrittura sui files aperti

SIDE-EFFECTS:
- Stampa a schermo in caso di errore
- I files "attivita.txt" e "attivita_menu.txt" vengono aggiornati con il nuovo item scritto in append

*/
void scrivi_file_attivita(item a){
    if(a == NULL){  //Controllo se item != NULL
        printf("Errore, item passato in input non valido\n");
        return;
    }
    //APRE I FILES "attivita.txt" E "attivita_menu.txt" E NE CONTROLLA ERRORE IN APERTURA
    FILE* fp = fopen("files_txt/attivita.txt", "a");
    FILE* fp1 = fopen("files_txt/attivita_menu.txt", "a");
    if((fp == NULL)||(fp1 == NULL)){
        printf("Impossibile aggiungere tempo attività. Errore in apertura file.\n");
        return;
    }

    //Formattazione per file attivita.txt
    fprintf(fp, "%.30s\n%.15s\n%.10s %.8s %.8s %d %d %d\n", a->descrizione, a->corso, a->data_scadenza,
            a->tempo_stimato, a->tempo_passato, a->priorita, a->id, a->stato);
    
    //Formattazione per attivita_menu.txt
    fprintf(fp1, "%.15s\n%.10s %d %d\n", a->descrizione, a->data_scadenza, a->priorita, a->stato); 
    
    fclose(fp);
    fclose(fp1);

return;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE FILE ATTIVITA'
/*
SPECIFICA SINTATTICA:
- int (item, FILE*, FILE*) -> int

SPECIFICA SEMANTICA:
- aggiorna_file_attivita_item (a, fp, fp1)  -> 0: Operazione andata a buon fine
                                            -> 1: Operazione non andata a buon fine

PRE-CONDIZIONI:
- a: item in input valido
- fp: Puntatore a file in input valido
- fp1: Puntatore a file in input valido

POST-CONDIZIONI:
- La funzione restituisce 0 se l'operazione di scrittura su entrambi i file è andata a buon fine, 1 se almeno una scrittura e fallita

SIDE-EFFECTS:
- Scrive i dati di item sui files puntati dai due puntatori in input

*/
int aggiorna_file_attivita_item(item a, FILE* fp, FILE* fp1){
    //Formattazione per file attivita.txt
    if((fprintf(fp, "%.30s\n%.15s\n%.10s %.8s %.8s %d %d %d\n", a->descrizione, a->corso, a->data_scadenza,
            a->tempo_stimato, a->tempo_passato, a->priorita, a->id, a->stato)) < 0) return 1;
    //Formattazione per attivita_menu.txt
    if((fprintf(fp1, "%.15s\n%.10s %d %d\n", a->descrizione, a->data_scadenza, a->priorita, a->stato)) < 0) return 1;
    
return 0;
}

//-------------------------------------------------------------------------------------

//FUNZIONE DI CONTROLLO PER LA CORRETTEZZA DELLA DATA INSERITA DALL'UTENTE
/*
SPECIFICA SINTATTICA:
- int (int, int, int) -> int

SPECIFICA SEMANTICA:
- controlla_data (giorno, mese, anno)   -> 1: Valori non coerenti col formato
                                        -> 0: Valori coerenti col formato

PRE-CONDIZIONI:
- Giorno: Valore compreso tra 1 e 31
- Mese: Valore compreso tra 1 e 12
- Anno: Valore maggiore di 2025 (anno corrente)

POST-CONDIZIONI:
- La funzione prende in input i valori di giorno, mese ed anno e restituisce 0 se sono coerenti, 1 altrimenti

SIDE-EFFECTS:
- Stampa a schermo in caso di errore

*/
static int controlla_data(int giorno, int mese, int anno){

    switch(mese){
        //Controllo per Febbraio
        case 2: if(((anno % 4) == 0) && (((anno % 100) != 0)||(anno % 400) == 0)){      //Controlla l'anno bisestile
                    if(giorno > 29){                                                         
                        printf("Febbraio ha 29 giorni quest'anno, valore non valido\n");
                        return 1;
                    }
                }
                else if(giorno > 28){
                    printf("Febbraio ha al massimo 28 giorni, valore non valido\n");                        
                    return 1;
                }
                return 0;

                break;
                    
        //Controllo per i mesi con 30 giorni (Aprile, Giugno, Settembre, Novembre)
        case 4: case 6: case 9: case 11:                                               
                if(giorno > 30){
                    printf("Non esiste il 31 di questo mese\n");
                    return 1;
                }
                return 0;

                break;

        //Per tutti gli altri casi, la data è valida
        default:    return 0;
    }

return 0;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER REGISTRARE UNA NUOVA ATTIVITA' DI STUDIO
/*
SPECIFICA SINTATTICA:
- item (int) -> item

SPECIFICA SEMANTICA:
- aggiungi (id) -> a

PRE-CONDIZIONI:
- valore dell'id compreso tra 1 ed il massimo valore intero rappresentabile

POST-CONDIZIONI:
- Restituisce un item i cui campi sono dati in input dall'utente. Tramite scrivi_file_attivita() sarà aggiunto a file

SIDE-EFFECTS:
- Stampa a schermo in caso di errore
- Stampa a schermo istruzioni per compilare i campi dell'item
- Legge input da tastiera
- Scrive su file tramite scrivi_file_attivita()

*/
item aggiungi (int id){
    item a = nuovo_item();
    char descrizione[31], corso[16], data[10], ora[8], c;
    int anno, mese, giorno, ore, minuti, secondi, priorita, i = 0, l = 0;

    //iNSERIMENTO DELLA DESCRIZIONE DELL'ATTIVITA' DI STUDIO
    printf("Inserire Descrizione attivita' di studio (max 30 caratteri):\n");               //Prende descrizione attività di studio
    while((c = getchar()) != '\n'){
        descrizione[i] = c;
        i++;
    }
    //Se si sfora il limite di caratteri, si resetta i a 30 e si svuota il buffer
    if(i > 30){
        i = 30;
    }
    a->descrizione = strncpy(a->descrizione, descrizione, i);
    a->descrizione[i] = '\0';
    
    pulisci_buffer();

    i = 0;

    //INSERIMENTO DEL CORSO RELATIVO ALL'ATTIVITA' DI STUDIO
    printf("Inserire Corso attivita' di studio (max 15 caratteri):\n");                     //Prende nome del corso
    while((c = getchar()) != '\n'){
        corso[i] = c;
        i++;
    }
    //Se si sfora il limite di caratteri, si resetta i a 15 e si svuota il buffer
    if(i > 15){
        i = 15;
    }

    strncpy(a->corso, corso, i);
    a->corso[i] = '\0';

    pulisci_buffer();

    //INSERIMENTO DELLA DATA DI SCADENZA
    while(1){
        //INSERIMENTO DEL GIORNO DI SCADENZA CON CONTROLLO INPUT VALIDO
        while(1){
            printf("Inserire Giorno di scadenza attivita' di studio:\n");  
            if(scanf("%d", &giorno) == 1){
                if((giorno >= 1)&&(giorno <= 31)){      //Giorno deve essere compreso tra 1 e 31
                    pulisci_buffer();
                    break;
                }
                else{
                    printf("Valore deve essere compreso tra 1 e 31\n");
                    pulisci_buffer();
                    continue;
                    }
            }
            else{
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }
        }
    
        //INSERIMENTO DEL MESE DI SCADENZA CON CONTROLLO INPUT VALIDO
        while(1){
            printf("Inserire Mese di scadenza attivita' di studio:\n");
            if(scanf("%d", &mese) == 1){
                if((mese >= 1)&&(mese <= 12)){          //Mese deve essere compreso tra 1 e 12
                    pulisci_buffer();
                    break;
                }
                else{
                    printf("Valore deve essere compreso tra 1 e 12\n");
                    pulisci_buffer();
                    continue;
                }
            }
            else{
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }
        }

        //INSERIMENTO DELL'ANNO DI SCADENZA CON CONTROLLO INPUT VALIDO
        while(1){
            printf("Inserire Anno di scadenza attivita' di studio:\n");
            if(scanf("%d", &anno) == 1){
                if(anno >= 2025){                       //Anno non può essere minore dell'anno corrente
                    pulisci_buffer();
                    break;
                }
                else{
                    printf("Anno gia' passato\n");
                    pulisci_buffer();
                    continue;
                }
            }
            else{
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }
        }
        //Controllo data corretta
        if(controlla_data(giorno, mese, anno) == 0) break;
    }
    sprintf(data, "%02d/%02d/%04d", giorno, mese, anno);
    
    strncpy(a->data_scadenza, data, 10);
    a->data_scadenza[10] = '\0';  

    //INSERIMENTO TEMPO STIMATO PER CONCLUDERE L'ATTIVITA'
    int s = 0;

    //PRENDE TEMPO STIMATO PER ATTIVITÀ
    while(1){   
        printf("Inserire Tempo stimato di completamento attivita' di studio.\n");          
        
        //Inserimento ore
        while(1){
            printf("Inserire Ore (max 99): \n");
            if(scanf("%d", &ore) != 1){
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }
            /*else if(getchar() != '\n'){
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }*/
            else if(ore < 0){
                printf("Valore negativo non ammesso\n");
                pulisci_buffer();
                continue;
            }
            else{
                pulisci_buffer();
                break;
            }
        }

        //Inserimento minuti
        while(1){
            printf("Inserire Minuti: \n");
            if(scanf("%d", &minuti) != 1){
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }
            else if(minuti < 0){
                printf("Valore negativo non ammesso\n");
                pulisci_buffer();
                continue;
            }
            else{
                pulisci_buffer();
                break;
            }
        }

        //Inserimento Secondi
        while(1){
            printf("Inserire Secondi: \n");
            if(scanf("%d", &secondi) != 1){
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }
            else if(minuti < 0){
                printf("Valore negativo non ammesso\n");
                pulisci_buffer();
                continue;
            }
            else{
                pulisci_buffer();
                break;
            }
        }

        //Controllo secondi maggiori di 59, in caso aumenta minuti
        while(secondi > 59){
            secondi -= 60;
            s++;
        }
        minuti += s;
        if(secondi < 0) secondi = 0;

        s = 0;

        //Controllo minuti maggiori di 59, in caso aumenta le ore
        while(minuti > 59){
            minuti -= 60;
            s++;  
        }
        ore += s;
        if(minuti < 0) minuti = 0;

        //Se le ore superano le 99 a fine ciclo, le imposta a 99
        if(ore > 99) ore = 99;

        break;
    }
    //Crea un'unica stringa con sprintf contenente i valori di ore, minuti e secondi
    sprintf(ora, "%02d:%02d:%02d", ore, minuti, secondi);

    strncpy(a->tempo_stimato, ora, 9);
    a->tempo_stimato[9] = '\0';

    printf("Inserire valore di Priorita' attivita' di studio:\n-0 = No priorita'\n-1 = priorita' bassa\n"
            "-2 = priorita' media\n-3 = priorita' alta\n");     //Prende valore priorità
    while(1){
        //Controllo valore non valido
        if(scanf("%d", &priorita) != 1){
            printf("Valore non valido\n");
            continue;
        }
        if((priorita >= 0)&&(priorita <= 3)){
            a->priorita = priorita;
            break;
        }
        else    
            printf("Il valore deve essere compreso tra 0 e 3\n");
    }

    //Assegna al valore dell'id dell'item l'id passato in input
    a->id = id;

    //Richiama la funzione per trascrivere l'item su file attività
    scrivi_file_attivita(a);

return a;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE LO STATO DI UN ITEM PASSATO IN INPUT A 0 (COMPLETATA)
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- aggiorna_attivita_completata (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- Il campo "stato" dell'item in input viene aggiornato a 0

SIDE-EFFECTS:
- Nessuno

*/
void aggiorna_attivita_completata(item a){
    a->stato = 0;

return;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER AGGIORNARE LO STATO DI UN ITEM PASSATO IN INPUT A -1 (RITARDO)
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- aggiorna_attivita_ritardo (a) -> void

PRE-CONDIZIONI:
- Item a in input è un puntatore valido

POST-CONDIZIONI:
- Aggiorna il campo "stato" dell'item in input a -1  

SIDE-EFFECTS:
- Nessuno

*/
void aggiorna_attivita_ritardo(item a){
    a->stato = -1;

return;
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER VERIFICARE LO STATO DI COMPLETAMENTO DI UN ITEM PASSATO IN INPUT E, IN CASO, AGGIORNARLO
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- stato_completamento_item (a)  -> -1: Attività in ritardo
                                ->  0: Attività completata 
                                ->  1: Attività in corso

PRE-CONDIZIONI:
- Item a in input è un puntatore valido

POST-CONDIZIONI:
- Mostra lo stato di completamento dell'attività basandosi sulla percentuale ottenuta da tempo_passato e tempo_stimato dell'item 
    in input. Se l'attività risulta ancora in corso, allora restituisce 1, se invece risulta completata (percentuale del 100%), 
    allora chiede all'utente se l'attività è stata completata nel tempo previsto o meno. 
    Se l'attività è stata completata, restituisce 0, altrimenti -1

SIDE-EFFECTS:
- Stampa a schermo una barra di avanzamento con percentuale tramite funzione mostra_barra_avanzamento()
- Stampa a schermo istruzioni per input
- Prende input da tastiera 

*/
int stato_completamento_item (item a){
    char tempo1[9], tempo2[9];
    int ore, minuti, secondi;
    double t1, t2, percentuale;

    //Salva tempo passato e stimato dell'item in due array di caratteri
    strcpy(tempo1, a->tempo_stimato);
    strcpy(tempo2, a->tempo_passato);

    sscanf(tempo1, "%d:%d:%d", &ore, &minuti, &secondi);
    t1 = ((ore * 3600) + (minuti * 60) + (secondi));

    sscanf(tempo2, "%d:%d:%d", &ore, &minuti, &secondi);
    t2 = ((ore * 3600) + (minuti * 60) + (secondi));

    //Calcola la percentuale di completamento basandosi sui due valori precedenti
    percentuale = (double)((t2 / t1) * 100);

    //Se la percentuale è 100%
    if(percentuale >= 100.00){
        mostra_barra_avanzamento(100.00);
        char c = 0;
        
        //Chiede se l'attività è stata completata nel tempo previsto
        printf("Wow! Sembra tu abbia studiato per il tempo che avevi stimato!\nHai completato l'attivita'??\t(Y / N)\n");
        while(1){
            if((scanf(" %c", &c) != 1)){
                printf("Valore non valido\n");
                pulisci_buffer();
                continue;
            }

            switch(c){
                //Se si, restituisce 0
                case 'y': case 'Y': return 0;

                //Se no, restituisce -1
                case 'n': case 'N': return -1;
                
                default :   printf("Valore non valido\n");
                            continue;
            }
        }
    }
    else
        //Se la percentuale è meno del 100%, chiama solo la funzione per mostrare la barra di avanzamento
        mostra_barra_avanzamento(percentuale);

//Restituisce di default 1 (attività in corso)
return 1;    
}

//-------------------------------------------------------------------------------------

//FUNZIONE PER SCRIVERE UN ITEM IN INPUT SU FILE REPORT PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- void (item, FILE*) -> void

SPECIFICA SEMANTICA:
- scrivi_file_report_item (a, fp) -> void

PRE-CONDIZIONI:
- a: Puntatore ad item valido
- fp: Puntatore a file valido

POST-CONDIZIONI:
- Avvia un'operazione di scrittura dell'item su file in input secondo una determinata formattazione

SIDE-EFFECTS:
- Stampa tutti i campi dell'item in input sul file di testo passato in input, secondo una formattazione ben precisa

*/
void scrivi_file_report_item(item a, FILE* fp){
        fprintf(fp, "%.30s\n%.15s\n%.10s %.8s %.8s %d %d %d\n", a->descrizione, a->corso, a->data_scadenza, 
                a->tempo_stimato, a->tempo_passato, a->priorita, a->id, a->stato);

return;
}

//-------------------------------------------------------------------------------------

//FUNZIONE CHE AGGIORNA IL TEMPO DI LAVORO NELL'ITEM PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- int (item, double) -> int

SPECIFICA SEMANTICA:
- modifica_tempo (a, tempo_totale)  -> 0 : Operazione andata a buon fine
                                    -> 1 : Operazione non andata a buon fine

PRE-CONDIZIONI:
- a: Puntatore ad item valido
- tempo_totale: Valore compreso tra 0 ed il valore double massimo rappresentabile

POST-CONDIZIONI:
- Aggiorna il campo "tempo_passato" dell'item in input sommandoci il valore di tempo_totale. Restituisce 0 se va a buon fine, 1 altrimenti

SIDE-EFFECTS:
- Nessuno

*/
int modifica_tempo(item a, double tempo_totale){
    char tempo_passato[9];
    int ore = 0, minuti = 0, secondi = 0;

    //Prende la stringa contenuta in a->tempo_passato, salva i valori di ore, minuti e secondi e li somma (convertiti in secondi)
    //al tempo_totale, che è già in secondi
    sscanf(a->tempo_passato, "%d:%d:%d", &ore, &minuti, &secondi);
    tempo_totale += ((ore * 3600) + (minuti * 60) + secondi);

    //Converte tempo_totale in ore, minuti e secondi
    ore = (int)tempo_totale / 3600;
    minuti = ((int)tempo_totale % 3600) / 60;
    secondi = (int)tempo_totale % 60;

    //Ne crea una stringa unica e la salva in a->tempo_passato
    sprintf(tempo_passato, "%d:%d:%d", ore, minuti, secondi);
    if(strcpy(a->tempo_passato, tempo_passato) == NULL) return 1;   //Restituisce 1 se la strcpy non va a buon fine

return 0;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE LA PRIORITA' DELL'ITEM IN INPUT
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- ottieni_priorità (a) -> a->priorita

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- Restituisce il valore del campo "priorita" dell'item in input

SIDE-EFFECTS:
- Nessuno

*/
int ottieni_priorita(item a){
    return a->priorita;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER STAMPARE I CAMPI DI UN ITEM PASSATO IN INPUT
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- stampa_item (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item in input valido

POST-CONDIZIONI:
- Stampa a schermo i campi dell'item a in input, il campo "stato" è rappresentato da una stringa aggiornata in base al suo valore numerico

SIDE-EFFECTS:
- Stampa a schermo i dati contenuti nei campi dell'item in input

*/
void stampa_item(item a){
    char s[11];

    //Formatta s in base all'intero presente nella variabile a->stato
    if(a->stato == 1)
        strcpy(s, "In Corso");
    else if(a->stato == -1)
        strcpy(s, "In Ritardo");
    else
        strcpy(s, "Completata");

    printf("\nDescrizione: - - - ->[%s]\nCorso: - - - - - - ->[%s]\nData di Scadenza:- ->[%s]\nTempo Stimato: - - ->"
            "[%s]\nTempo di Lavoro: - ->[%s]\nPriorita': - - - - ->[%d]\nID:- - - - - - - - ->[%d]\nStato: - - - - "
            "- - ->[%s]\n", a->descrizione, a->corso, a->data_scadenza, a->tempo_stimato, 
            a->tempo_passato, a->priorita, a->id, s);
            printf("-------+---------+---------+---------+---------+---------");    

return;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER CREARE UN ITEM A PARTIRE DAI VALORI IN INPUT
/*
SPECIFICA SINTATTICA:
- item (char*, char*, char*, char*, char*, int, int, int) -> item

SPECIFICA SEMANTICA:
- inserisci_item (descrizione, corso, data_scadenza, tempo_stimato, tempo_passato, priorita, id, stato) -> a

PRE-CONDIZIONI:
- descrizione: Puntatore Valido
- corso: Puntatore Valido
- data_scadenza: Puntatore Valido
- tempo_stimato: Puntatore Valido
- tempo_passato: Puntatore Valido
- priorita: Valore intero compreso tra 0 e 3
- id: Valore intero compreso tra 0 ed il numero massimo di elementi nella coda attività
- stato: Valore intero compreso tra -1 e 1

POST-CONDIZIONI:
- La funzione inizializza un nuovo item assegnando ai suoi campi i valori passati in input e lo restituisce

SIDE-EFFECTS:
- Nessuno

*/
item inserisci_item(char* descrizione, char* corso, char* data_scadenza, char* tempo_stimato, char* tempo_passato, int priorita, int id, int stato){
    item a = nuovo_item();
    
    a->descrizione = strcpy(a->descrizione, descrizione);
    a->corso = strcpy(a->corso, corso);
    a->data_scadenza = strcpy(a->data_scadenza, data_scadenza);
    a->tempo_stimato = strcpy(a->tempo_stimato, tempo_stimato);
    a->tempo_passato = strcpy(a->tempo_passato, tempo_passato);
    a->priorita = priorita;
    a->id = id;
    a->stato = stato;

return a;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE PER COPIARE UN ITEM IN UN ALTRO
/*
SPECIFICA SINTATTICA:
- item (item) -> item

SPECIFICA SEMANTICA:
- copia_item (a) -> b

PRE-CONDIZIONI:
- Puntatore ad item a passato in input deve essere valido

POST-CONDIZIONI:
- Alloca un item b, copia in esso il valore di ogni campo dell'item a e lo restituisce

SIDE-EFFECTS:
- Nessuno

*/
item copia_item(item a){
    item b = nuovo_item();

    b->id = a->id;
    strcpy(b->descrizione, a->descrizione);
    strcpy(b->corso, a->corso);
    strcpy(b->data_scadenza, a->data_scadenza);
    strcpy(b->tempo_passato, a->tempo_passato);
    strcpy(b->tempo_stimato, a->tempo_stimato);
    b->priorita = a->priorita;
    b->stato = a->stato;

return b;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE PER STAMPARE ID ITEMS PER SCELTA MENU
/*
SPECIFICA SINTATTICA:
- void (item) -> void

SPECIFICA SEMANTICA:
- stampa_id_item (a) -> void

PRE-CONDIZIONI:
- Puntatore ad item a in input valido

POST-CONDIZIONI:
- Stampa a schermo il valore di "descrizione" e "id" dell'item in input secondo una formattazione preciso

SIDE-EFFECTS:
- Stampa a schermo

*/
void stampa_id_item(item a){
    printf("Descrizione: \n%s\nID: [%d]\n\n", a->descrizione, a->id);

return;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE AD OTTENERE ID DI UN DATO ITEM
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- ottieni_id_item (a) -> a->id

PRE-CONDIZIONI:
- Puntatore ad item a in input valido

POST-CONDIZIONI:
- Restituisce il valore del campo "id" dell'item passato in input

SIDE-EFFECTS:
- Nessuno

*/
int ottieni_id_item(item a){
    return a->id;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE AD OTTENERE LO STATO DI UN DATO ITEM
/*
SPECIFICA SINTATTICA:
- int (item) -> int

SPECIFICA SEMANTICA:
- ottieni_stato_item (a) -> a->id

PRE-CONDIZIONI:
- Puntatore ad item a in input valido

POST-CONDIZIONI:
- Restituisce il valore del campo "stato" dell'item passato in input

SIDE-EFFECTS:
- Nessuno

*/
int ottieni_stato_item(item a){
    return a->stato;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE A CONFRONTARE 2 ITEMS
/*
SPECIFICA SINTATTICA:
- int (item, item) -> int

SPECIFICA SEMANTICA:
- confronta_item (a, b)   -> 1: I due items sono diversi
                        -> 0: I due items sono uguali

PRE-CONDIZIONI:
- a: Puntatore ad item in input valido
- b: Puntatore ad item in input valido

POST-CONDIZIONI:
- Restituisce 0 se i due item in input hanno i campi confrontati uguali, 1 se sono diversi o se almeno uno dei due è NULL

SIDE-EFFECTS:
- Nessuno

*/
int confronta_item(item a, item b){
    if((a == NULL)||(b == NULL)) return 1;

    if( ((strcmp(a->descrizione, b->descrizione))       == 0)&& //Se i due item hanno questi campi uguali tra di loro, restituisce 0, altrimenti 1
        ((strcmp(a->corso, b->corso))                   == 0)&&
        ((strcmp(a->tempo_stimato, b->tempo_stimato))   == 0)&&
        ((strcmp(a->data_scadenza, b->data_scadenza))   == 0)&&
        (a->priorita == b->priorita))                   return 0;

return 1;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE UTILE AD AGGIORNARE L'ID DI UN ITEM
/*
SPECIFICA SINTATTICA:
- void (item, int) -> void

SPECIFICA SEMANTICA:
- aggiorna_id_ordine_item (a, id) -> void

PRE-CONDIZIONI:
- a: Puntatore ad item valido
- id: Valore intero compreso tra 1 ed il numero di elementi della coda attività

POST-CONDIZIONI:
- Aggiorna il campi "id" dell'item in input con il valode di id

SIDE-EFFECTS:
- Nessuno

*/
void aggiorna_id_ordine_item(item a, int id){
    a->id = id;

return;
}
