#include <stdio.h>
#include <stdlib.h>
#include <time.h>   //Inclusione libreria <time.h> per ottenere data ed ora correnti.

#include "item.h"

//-------------------------------------------------------------------------------------

struct attivita_studio{
    char* descrizione;      //Descrizione attività di studio
    char* corso;            //Nome del corso
    char data_scadenza[10]; //formato DD/MM/AAAA
    char tempo_stimato[8];  //formato DD:HH:MM
    int priorita;           //Valori da 0 (bassa) a 3 (alta) per livello di priorità
};

//-------------------------------------------------------------------------------------

int aggiungi (void){
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    item new;

    
}

//-------------------------------------------------------------------------------------

int stato_completamento (pqueue q, int id, float tempo){


    
}

//-------------------------------------------------------------------------------------