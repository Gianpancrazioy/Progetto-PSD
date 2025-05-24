#ifdef _WIN32               //Pulizia schermo in caso di dispositivi Windows
    #include <windows.h>    
    #define CLEAR "cls"
#else                       //Pulizia schermo in caso di dispositivi macOS o Linux
    #include <unistd.h>    
    #define CLEAR "clear"
#endif

//------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "testing_item.h"
#include "testing_adt.h"

//------------------------------------------------------------------------------------------------------------

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

//FUNZIONE CHE GENERA LE CODE BASATE SUI FILES DI INPUT PER I TEST
int genera_code(pqueue p, pqueue p1, pqueue q, pqueue q1){
    FILE* fp;

    //GENERA CODA PER TEST INSERIMENTO                 
    fp = fopen("test_suite/test1_input.txt", "r");
    if(fp == NULL){
        printf("Errore in apertura file.\n");
        return -1;
    }
    //Se il file report non è vuoto, lo converte in una queue, se lo è la queue sarà vuota
    if(controlla_file_vuoto(fp) == 0)
        ottieni_queue_da_file(p, fp);
    fclose(fp); //Chiude il file report


    //GENERA CODA PER TEST PROGRESSO
    fp = fopen("test_suite/test2_input.txt", "r");
    if(fp == NULL){
        printf("Errore in apertura file.\n");
        return -1;
    }
    //Se il file attività non è vuoto, lo converte in una queue, se lo è la queue sarà vuota
    if(controlla_file_vuoto(fp) == 0)
        ottieni_queue_da_file(p1, fp);
    fclose(fp); //Chiude il file attività


    //GENERA CODA TEST RIMOZIONE
    fp = fopen("test_suite/test3_input.txt", "r");
    if(fp == NULL){
        printf("Errore in apertura file.\n");
        return -1;
    }
    //Se il file attività non è vuoto, lo converte in una queue, se lo è la queue sarà vuota
    if(controlla_file_vuoto(fp) == 0)
        ottieni_queue_da_file(q, fp);
    fclose(fp); //Chiude il file attività


    //GENERA CODA TEST PRIORITA'
    fp = fopen("test_suite/test4_input.txt", "r");
    if(fp == NULL){
        printf("Errore in apertura file.\n");
        return -1;
    }
    //Se il file attività non è vuoto, lo converte in una queue, se lo è la queue sarà vuota
    if(controlla_file_vuoto(fp) == 0)
        ottieni_queue_da_file(q1, fp);
    fclose(fp); //Chiude il file attività

return 0;
}

//------------------------------------------------------------------------------------------------------------

//FUNZIONE CHE GENERA FILES ORACOLO PER I TEST
void genera_oracles(){
    FILE* fp;

    //ORACLE TEST 1
    fp = fopen("test_suite/Oracle_test_inserimento.txt", "w");
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");    
    fprintf(fp, "test2_tempo_passato_aggiornato\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "13/06/2025 0:0:3 0:0:3 2 2 0\n");    
    fprintf(fp, "test3 piu di 30 caratteri inse\n");    
    fprintf(fp, "inserimento con\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");    
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");    
    fclose(fp);        

    //INPUT TEST 1
    fp = fopen("test_suite/Test1_input.txt", "w");
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");    
    fprintf(fp, "test2_tempo_passato_aggiornato\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "13/06/2025 0:0:3 0:0:3 2 2 0\n");    
    fprintf(fp, "test3 piu di 30 caratteri inseriti insieme\n");    
    fprintf(fp, "inserimento con tanti caratteri\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");    
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");    
    fclose(fp);
    
//---------------------------------------------------

    //ORACLE TEST 2
    fp = fopen("test_suite/Oracle_test_progresso.txt", "w");
    fprintf(fp, "0.00\n");    
    fprintf(fp, "100.00\n");    
    fprintf(fp, "50.00\n");    
    fprintf(fp, "100.00\n");    
    fclose(fp);
                
    //INPUT TEST 2
    fp = fopen("test_suite/test2_input.txt", "w");
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");    
    fprintf(fp, "test2_tempo_passato_aggiornato\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "13/06/2025 0:0:3 0:0:3 2 2 0\n");    
    fprintf(fp, "test3 piu di 30 caratteri inseriti insieme\n");    
    fprintf(fp, "inserimento con tanti caratteri\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");    
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");    
    fclose(fp);



//----------------------------------------------------

    //ORACLE TEST 3
    fp = fopen("test_suite/Oracle_test_rimozione.txt", "w");    
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");        
    fprintf(fp, "test3 piu di 30 caratteri inse\n");    
    fprintf(fp, "inserimento con\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");    
    fclose(fp);

    //INPUT TEST 3
    fp = fopen("test_suite/test3_input.txt", "w");
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");    
    fprintf(fp, "test2_tempo_passato_aggiornato\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "13/06/2025 0:0:3 0:0:3 2 2 0\n");    
    fprintf(fp, "test3 piu di 30 caratteri inseriti insieme\n");    
    fprintf(fp, "inserimento con tanti caratteri\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");    
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");    
    fclose(fp);

    //----------------------------------------------------

    //ORACLE TEST 4
    fp = fopen("test_suite/Oracle_test_report_priorita.txt", "w");
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");    
    fprintf(fp, "test2_tempo_passato_aggiornato\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "13/06/2025 0:0:3 0:0:3 2 2 0\n");    
    fprintf(fp, "test3 piu di 30 caratteri inse\n");    
    fprintf(fp, "inserimento con\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");    
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");    
    fclose(fp);        

    //INPUT TEST 4
    fp = fopen("test_suite/test4_input.txt", "w");
    fprintf(fp, "test4\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "28/02/2027 2:0:0 4:0:0 0 4 0\n");  
    fprintf(fp, "test3 piu di 30 caratteri inse\n");    
    fprintf(fp, "inserimento con\n");    
    fprintf(fp, "31/04/2026 4:0:0 2:0:0 1 3 -1\n");       
    fprintf(fp, "test1\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "30/05/2025 03:31:15 0:0:0 3 1 1\n");   
    fprintf(fp, "test2_tempo_passato_aggiornato\n");    
    fprintf(fp, "inserimento\n");    
    fprintf(fp, "13/06/2025 0:0:3 0:0:3 2 2 0\n");   
    fclose(fp);   

return;
}

//------------------------------------------------------------------------------------------------------------

int main(void){
    int c, i, ore, minuti, secondi, giorno, mese, anno, priorita, id, stato;
    item a;
    FILE* fp;
    FILE* fp1;
    char buffer1[80], buffer2[80];
    char data[10], tempo1[8], tempo2[8];
    
    pqueue p = nuova_coda();    //Alloca una nuova coda a priorità per il file report
    pqueue q = nuova_coda();    //Alloca una nuova coda a priorità per il file attività
    pqueue p1 = nuova_coda();
    pqueue q1 = nuova_coda();

    genera_oracles();
    genera_code(p, p1, q, q1);

    while(1){
        //CICLO PER SCELTA CORRETTO VALORE DI SCELTA    
        pulisci_schermo();
        printf("*****************************************\n*");
        printf("/\\/\\/\\/\\/\\/\\/|BENVENUTO!|/\\/\\/\\/\\/\\/\\/\\*\n");
        printf("*****************************************\n*");
        printf("/\\/\\/\\/\\/|COSA SI VUOLE FARE?|/\\/\\/\\/\\/*\n*****************************************\n*\t\t\t\t\t*\n");
        printf("*1) Test inserimento attivita'.----+----*\n*\t\t\t\t\t*\n*---+---2) Test Report Settimanale.\t*\n*\t\t\t\t\t*\n*"
                "3) Test Stato Completamento.-----+-----*\n*\t\t\t\t\t*\n*--+--4) Test Rimozione.\t\t*\n*\t\t\t\t\t*\n*\t5) Testare tutta la suite.--+---*\n*\t\t\t\t\t*\n-"
                "---+----+----6) Chiudi l'applicazione. *");
        printf("\n*\t\t\t\t\t*\n");
        printf("*****************************************\n");

        while(1){
            //Controllo coerenza valore in input per switch successivo
            if((scanf("%d", &c) == 1)&&(getchar() == '\n')){
                if((c < 1)||(c > 6)){ 
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
        //CASE 1 PERMETTE DI EFFETTUARE TEST SU INSERIMENTO DI NUOVE ATTIVITA' IN INPUT DA FILE E STAMPA CORRETTA
        //SU FILE REPORT
        case 1: pulisci_schermo();

                int s = 1;

                scrivi_file_report_queue(p);

                fp = fopen("test_suite/Oracle_test_inserimento.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST INSERIMENTO: SUCCESSO\n");
                else
                    printf("TEST INSERIMENTO: FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);

                break;
        
    
        //CASE 2 PERMETTE TESTARE L'AGGIORNAMENTO DEI PROGRESSI
        case 2: pulisci_schermo();
                
                controlla_stato_attivita(p1);


                fp = fopen("test_suite/Oracle_test_progresso.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                s = 1;
                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST PROGRESSO ATTIVITA': SUCCESSO\n");
                else
                    printf("TEST PROGRESSO ATTIVITA': FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);

                break;

        //CASE 3 PERMETTE DI CONTROLLARE LA COMPLETEZZA DEL FILE REPORT
        case 3: pulisci_schermo();

                a = inserisci_item("test2_tempo_passato_aggiornato", "inserimento", "13/06/2025", "0:0:3", "0:0:3", 2, 2, 0);

                rimuovi_item_report(q, a);
                scrivi_file_report_queue(q);

                fp = fopen("test_suite/Oracle_test_rimozione.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                s = 1;
                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST RIMOZIONE: SUCCESSO\n");
                else
                    printf("TEST RIMOZIONE: FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);

                break;

        //CASE 4 PERMETTE DI CONTROLLARE LA STAMPA IN BASE A PRIORITA'
        case 4: pulisci_schermo();
                stampa_queue_priorita(q1);

                fp = fopen("test_suite/Oracle_test_report_priorita.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                s = 1;
                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST STAMPA PER PRIORITA': SUCCESSO\n");
                else
                    printf("TEST STAMPA PER PRIORITA': FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);

                break;

        //CONSENTE DI ESEGUIRE TUTTI I TEST IN UNA VOLTA SOLA
        case 5: pulisci_schermo();
                
                s = 1;

                scrivi_file_report_queue(p);

                fp = fopen("test_suite/Oracle_test_inserimento.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST INSERIMENTO: SUCCESSO\n");
                else
                    printf("TEST INSERIMENTO: FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);


                //CONTROLLO PER TEST 2
                controlla_stato_attivita(p1);   //Test 2

                fp = fopen("test_suite/Oracle_test_progresso.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                s = 1;
                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST PROGRESSO ATTIVITA': SUCCESSO\n");
                else
                    printf("TEST PROGRESSO ATTIVITA': FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);
                
                a = inserisci_item("test2_tempo_passato_aggiornato", "inserimento", "13/06/2025", "0:0:3", "0:0:3", 2, 2, 0);

                rimuovi_item_report(q, a);      //Test 3
                scrivi_file_report_queue(q);

                //CONTROLLO PER TEST 3
                fp = fopen("test_suite/Oracle_test_rimozione.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                s = 1;
                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST RIMOZIONE: SUCCESSO\n");
                else
                    printf("TEST RIMOZIONE: FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);


                stampa_queue_priorita(q1);      //Test 4

                //CONTROLLO PER TEST 4
                fp = fopen("test_suite/Oracle_test_report_priorita.txt", "r");
                fp1 = fopen("test_suite/output1.txt", "r");

                s = 1;
                while (fgets(buffer1, 80, fp) && fgets(buffer2, 80, fp1)) {
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break; 
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }

                    fgets(buffer1, 80, fp); fgets(buffer2, 80, fp1);
                    if (strcmp(buffer1, buffer2) != 0){
                        s = 0;
                        break;
                    }
                }
                
                if(s == 1)
                    printf("TEST STAMPA PER PRIORITA': SUCCESSO\n");
                else
                    printf("TEST STAMPA PER PRIORITA': FALLITO\n");
                
                pausa(2);
                
                fclose(fp);
                fclose(fp1);


                break;

        case 6: pulisci_schermo();
                printf("Buona giornata! :D\n");

                dealloca_coda(p);
                dealloca_coda(p1);
                dealloca_coda(q);
                dealloca_coda(q1);

                return 0;

            }
        }
return 0;
}