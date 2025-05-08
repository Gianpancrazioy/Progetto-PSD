#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "functions.h"
#include "item.h"
#include "adt_pqueue.h"
#include "time_functions.h"

int main(void){
    int ora, minuto, giorno, mese, anno;
    char* giorno_settimana = (char*) malloc (sizeof(char) * 8);

    int* o = &ora;
    int* m = &minuto;
    int* g = &giorno;
    int*mon = &mese;
    int* y = &anno;
    ottieni_data_oggi(o, m, g, mon, y, giorno_settimana);

    //COSTRUZIONE INTERFACCIA UTENTE
    printf("*****************************************\n*");
    printf("/\\/\\/\\/\\/\\/\\/|BENVENUTO!|/\\/\\/\\/\\/\\/\\/\\*\n");
    printf("*****************************************\n*");
    printf("/\\/\\/\\/\\/\\/\\/|DATA E ORA|/\\/\\/\\/\\/\\/\\/\\*\n");//*\t\t\t\t\t*\n*");
    printf("*****************************************\n*");
    printf("      [%s - %d/%d/%d - %d:%d]\t*\n*****************************************\n*", giorno_settimana, giorno, mese, anno, ora, minuto);
    
    //printf("\t%s*\n*****************************************\n*", asctime(timeinfo));
    printf("/\\/\\/\\/\\/|ATTIVITA' IN CORSO|/\\/\\/\\/\\/\\*\n*****************************************\n*\t\t\t\t\t*\n");
    //RICHIAMO FUNZIONE PER STAMPARE ATTIVITA' IN CORSO DA FILES
    //stampa_attivita();
    printf("\n");
    printf("*****************************************\n*");
    printf("/\\/\\/\\/\\/|COSA SI VUOLE FARE?|/\\/\\/\\/\\/*\n*****************************************\n*\t\t\t\t\t*\n");
    printf("1) Aggiungere Attivita'.-------+--------*\n*\t\t\t\t\t*\n*---+---2) Generare report settimanale.\t*\n*\t\t\t\t\t*\n*3) Lavorare su un'Attivita'.-----+-----*\n*\t\t\t\t\t*\n*---+---4) Uscire dal Programma.----+---*");
    printf("\n*\t\t\t\t\t*\n");
    printf("*****************************************\n");





return 0;
}