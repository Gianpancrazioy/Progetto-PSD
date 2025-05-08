#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "time_functions.h"

const char* giorni_settimana[] = {
    "Lunedi'", "Martedi'", "Mercoledi'",
    "Giovedi'", "Venerdi'", "Sabato", "Domenica"
};

//FUNZIONE PER OTTENERE LA DATA ODIERNA
/*
SPECIFICA SINTATTICA:
void (int*, int*, int*, int*, char*) -> void

SPECIFICA SEMANTICA:
ottieni_data_oggi (ora, minuto, giorno, mese, anno, giorno_settimana) -> void

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Nessuna

SIDE EFFECT:
- I valori delle variabili puntate dai puntatori in input saranno modificati nel main
*/
void ottieni_data_oggi(int* ora, int* minuto, int* giorno, int* mese, int* anno, char* giorno_settimana){
    time_t tempo_base;
    struct tm* tempo;

    time(&tempo_base);
    tempo = localtime(&tempo_base);

    *ora = tempo->tm_hour;
    *minuto = tempo->tm_min;
    *giorno = tempo->tm_mday;
    *mese = tempo->tm_mon;
    *anno = tempo->tm_year + 1900;

    int s = strlen(giorni_settimana[tempo->tm_wday - 1]);
    giorno_settimana = (char*) realloc (giorno_settimana, sizeof(char) * s + 1);
    strcpy(giorno_settimana, giorni_settimana[tempo->tm_wday - 1]);
    giorno_settimana[s + 1] = '\0';
    
return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

//FUNZIONE PER OTTENERE IL NUMERO DELLA SETTIMANA NELL'ANNO CORRENTE (VISIBILE SOLO NEL FILE)
/*
SPECIFICA SINTATTICA:
int (struct tm*) -> int

SPECIFICA SEMANTICA: (da finire di modificare commento)*********************************************************************0989y8eur2io
ottieni_data_oggi (ora, minuto, giorno, mese, anno, giorno_settimana) -> void

PRE-CONDIZIONI:
- Nessuna

POST-CONDIZIONI:
- Nessuna

SIDE EFFECT:
- I valori delle variabili puntate dai puntatori in input saranno modificati nel main
*/
static int settimana_anno(struct tm *tempo) {
    // Calcola la settimana dell'anno in base al giorno dell'anno (tm_yday)
    // Prima settimana = dal giorno 0 a 6
    return (tempo->tm_yday / 7) + 1;
}

//------------------------------------------------------------------------------------------------------------------------------------------

void confronta_settimana(){
    time_t ora = time(NULL);
    struct tm *tempo = localtime(&ora);

    int week_number = settimana_anno(tempo);

return;
}

//------------------------------------------------------------------------------------------------------------------------------------------

