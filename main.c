#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "item.h"
#include "adt_pqueue.h"
#include "time_functions.h"

int main(void){
    item a;
    int c, s, id, i = 0;
    int settimana;
    confronta_settimana(&settimana);    //Confronta la settimana dell'anno corrente con il numero della settimana riportato nel file num_settimana

    pqueue p = nuova_coda();    //Alloca una nuova coda a priorità per il file report
    pqueue q = nuova_coda();    //Alloca una nuova coda a priorità per il file attività

    //GENERAZIONE QUEUE CONTENENTE ELEMENTI NEL FILE REPORT SETTIMANALE - TRATTATA COME EFFETTIVA CODA A PRIORITA' ORDINATA PER PRIORITA' DECRESCENTE
    //Controllo dell'errore su apertura file                                
    FILE* fp = fopen("files_txt/report_settimanale.txt", "r");
    if(fp == NULL){
        printf("Errore in apertura file.\n");
        return -1;
    }
    //Se il file report non è vuoto, lo converte in una queue, se lo è la queue sarà vuota
    if(controlla_file_vuoto(fp) == 0)
        ottieni_queue_da_file(p, fp);
    fclose(fp); //Chiude il file report

    //GENERAZIONE QUEUE CONTENENTE TUTTE LE ATTIVITA' - TRATTATA COME UN SEMPLICE ARRAY NON ORDINATO
    //Controllo dell'errore su apertura file
    fp = fopen("files_txt/attivita.txt", "r");
    if(fp == NULL){
        printf("Errore in apertura file.\n");
        return -1;
    }
    //Se il file attività non è vuoto, lo converte in una queue, se lo è la queue sarà vuota
    if(controlla_file_vuoto(fp) == 0)
        ottieni_queue_da_file(q, fp);
    fclose(fp); //Chiude il file attività

    //Chiama funzione per mostrare menu principale
    mostra_menu();

    while(1){
        //CICLO PER SCELTA CORRETTO VALORE DI SCELTA    
        while(1){
            //Controllo coerenza valore in input per switch successivo
            if((scanf("%d", &c) == 1)&&(getchar() == '\n')){
                if((c < 1)||(c > 8)){ 
                    printf("Valore non valido\n");    
                    continue;
                }
                else{
                    break;
                }
            }
            else{
                //Pulisce il buffer in caso di inserimento di caratteri per evitare cicli infiniti
                pulisci_buffer();

                printf("Valore non valido\n");
                continue;
            }
        }
    
    //SWITCH PER LE SCELTE DELL'UTENTE
    switch(c){
        //CASE 1 PERMETTE DI INSERIRE UN NUOVO ITEM
        case 1: pulisci_schermo();
                id = ottieni_id(q);
                if(id == -1){
                    printf("Impossibile aggiungere elemento, problema con ID, riprovare\n");
                    pausa(3);
                    break;
                }
                item a = aggiungi(id);
                if (insert(p, a) != 0) {
                    printf("Errore nell'inserimento dell'elemento nella coda \"report\".\n");
                }

                item b = copia_item(a); //Crea una copia dell'item per inserirla nell'altra lista, evitando di lavorare sullo stesso puntatore

                if (insert(q, b) != 0) {
                    printf("Errore nell'inserimento dell'elemento nella coda \"attivita'\".\n");
                }

                break;
        
        //CASE 2 PERMETTE DI STAMPARE LA QUEUE REPORT SETTIMANALE
        case 2: pulisci_schermo();
                stampa_queue_priorita(p); 
                pausa(7);
                break;

        //CASE 3 PERMETTE DI LAVORARE AD UN'ATTIVITA' E MODIFICARNE IL TEMPO DI LAVORO
        case 3: i = 0;
                while(1){
                    if((!q)||(coda_vuota(q) == 1)){
                        printf("Non ci sono attivita' su cui lavorare\n");
                        i = 1;
                        pausa(2);
                        break;
                    }

                    pulisci_schermo();
                    stampa_id_queue(q); //Stampa id di tutti gli item presenti nella queue attività
                    
                    printf("Segliere l'ID dell'attivita' su cui lavorare\n");
                    
                    //Controllo coerenza valore in input
                    if((scanf("%d", &c) == 1)&&(getchar() == '\n')){
                        if((c < 1)||(c > id)){                          //Valore deve essere positivo e <= del più grande id assegnato
                            printf("Valore non valido\n");    
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        //Pulisce il buffer in caso di inserimento di caratteri per evitare cicli infiniti
                        pulisci_buffer();

                        printf("Valore non valido\n");
                        continue;
                    }
                }
        
                if(i == 1) break;
        
                char stringa[9];
                double tempo_totale = 0;
                cronometro(stringa, &tempo_totale);
                pausa(2);

                printf("Tempo di lavoro: %s\n", stringa);   //Stampa tempo di lavoro su attività scelta

                //Chiama funzione per modificare il tempo di lavoro per l'attività selezionata
                if(modifica_tempo_queue(q, c, tempo_totale) == 1){
                    printf("Errore, impossibile aggiornare tempo, uscita..\n");
                    pausa(3);
                    break;
                }

                break;

        //CASE 4 PERMETTE DI STAMPARE TUTTE LE ATTIVITA' IN ORDINE DI PRIORITA' 
        case 4: pulisci_schermo();
                stampa_queue_priorita(q);
                pausa(7);
                break;
        
        //CASE 5 PERMETTE DI CONTROLLARE STATO COMPLETAMENTO DI UNA DATA ATTIVITA'
        case 5: i = 0;
                while(1){
                    if((!q)||(coda_vuota(q) == 1)){
                        printf("Non ci sono attivita' su cui lavorare\n");
                        i = 1;
                        pausa(2);
                        break;
                    }

                    pulisci_schermo();
                    stampa_id_queue(q); //Stampa id di tutti gli item presenti nella queue attività
                    
                    printf("Segliere l'ID dell'attivita' di cui controllare lo stato\n");
                    
                    //Controllo coerenza valore in input
                    if((scanf("%d", &c) == 1)&&(getchar() == '\n')){
                        if((c < 1)||(c > id)){                          //Valore deve essere positivo e <= del più grande id assegnato
                            printf("Valore non valido\n"); 
                            pulisci_buffer();   
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        //Pulisce il buffer in caso di inserimento di caratteri per evitare cicli infiniti
                        pulisci_buffer();

                        printf("Valore non valido\n");
                        continue;
                    }
                }
        
                if(i == 1) break;

                int z = controlla_stato_attivita(q, c); //Richiama funzione per controllare stato attività
                

                if(z == 0){                             //Se l'attività scelta risulta completata
                    a = ottieni_item_attivita_per_report(q, c);
                    aggiorna_completata(p, a);          //Aggiorna stato completamento nel report settimanale
                    rimuovi_item(q, c);                  //Rimuove l'attività dalla lista delle attività totali
                    }
                else if(z == -1){
                    a = ottieni_item_attivita_per_report(q, c);
                    aggiorna_ritardo(q, a);             //Segna in ritardo nella lista totale
                    aggiorna_ritardo(p, a);             //Lo segna anche nel report
                    aggiorna_file_attivita_queue(q);    //Aggiorna il file attività e menu attività
                    }
                else pausa(3);
                
                break;
        
        //CASE 6 PERMETTE DI AGGIORNARE LO STATO DI UN'ATTIVITA'
        case 6: while(1){
                    if((!q)||(coda_vuota(q) == 1)){
                        printf("Non ci sono attivita' su cui lavorare\n");
                        i = 1;
                        pausa(2);
                        break;
                    }

                    pulisci_schermo();
                    stampa_id_queue(q); //Stampa id di tutti gli item presenti nella queue attività
                    
                    printf("Scegliere l'ID dell'Attivita' di cui Aggiornare lo Stato\n");
                    
                    //Controllo coerenza valore in input
                    if((scanf("%d", &c) == 1)&&(getchar() == '\n')){
                        if((c < 1)||(c > id)){                          //Valore deve essere positivo e <= del più grande id assegnato
                            printf("Valore non valido\n"); 
                            pulisci_buffer();   
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        //Pulisce il buffer in caso di inserimento di caratteri per evitare cicli infiniti
                        pulisci_buffer();

                        printf("Valore non valido\n");
                        continue;
                    }
                }
                a = ottieni_item_attivita_per_report(q, c);
                aggiorna_completata(p, a);          //Aggiorna stato completamento nel report settimanale
                rimuovi_item(q, c);
                aggiorna_id_ordine_queue(q); 
                aggiorna_file_attivita_queue(q);

                printf("Attivita' Completata con Successo! Continua Cosi'!\n");
                pausa(2);

                break;
        
        //CASE 7 PERMETTE DI ELIMINARE UN ITEM DALLE QUEUE REPORT E ATTIVITA'
        case 7: i = 0;
                while(1){
                    if((!q)||(coda_vuota(q) == 1)){
                        printf("Non ci sono attivita' su cui lavorare\n");
                        i = 1;
                        pausa(2);
                        break;
                    }

                    pulisci_schermo();
                    stampa_id_queue(q); //Stampa id di tutti gli item presenti nella queue attività
                    
                    printf("Segliere l'ID dell'attivita' su cui lavorare\n");
                    
                    //Controllo coerenza valore in input
                    if((scanf("%d", &c) == 1)&&(getchar() == '\n')){
                        if((c < 1)||(c > id)){                          //Valore deve essere positivo e <= del più grande id assegnato
                            printf("Valore non valido\n");    
                            continue;
                        }
                        else{
                            break;
                        }
                    }
                    else{
                        //Pulisce il buffer in caso di inserimento di caratteri per evitare cicli infiniti
                        pulisci_buffer();

                        printf("Valore non valido\n");
                        continue;
                    }
                }
                if(i == 1) break;

                a = ottieni_item_attivita_per_report(q, c); //Cerca l'item nella coda attività corrispondente all'id e lo salva in a

                //Rimuove l'item da entrambe le queue
                rimuovi_item(q, c);
                rimuovi_item_report(p, a);

                //Aggiorna entrambe le queue
                aggiorna_id_ordine_queue(q); 
                aggiorna_file_attivita_queue(q);

                break;

        //CASE 8 PERMETTE DI AGGIORNARE FILE REPORT ED USCIRE DAL PROGRAMMA
        case 8: scrivi_file_report_queue(p);
                dealloca_coda(p);
                dealloca_coda(q);

                pulisci_schermo();
                printf("Alla prossima! :D\n");

                return 0;

        default: return 0;
    }

    mostra_menu();
    }

return 0;
}