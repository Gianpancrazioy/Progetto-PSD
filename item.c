#include <stdio.h>
#include <stdlib.h>

#include "item.h"

struct attivita_studio{
    char* descrizione;      //Descrizione attività di studio
    char* corso;            //Nome del corso
    char[10] data_scadenza; //formato DD/MM/AAAA
    char[8] tempo_stimato;  //formato DD:HH:MM
    int priorita;           //Valori da 0 (bassa) a 3 (alta) per livello di priorità
};