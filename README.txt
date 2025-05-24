*IMPORTANTE******************************************************************************************************************************************************    
*                                                                                                                                                               *
*   Il programma fa uso di funzioni definite solo sulle macchine Windows o solo su quelle Linux e macOS, nonostante abbia cercato di renderle il più portabili  *
*   possibile, c'è comunque la possibilità che si incorra in problemi sulle macchine Linux e macOS. In caso, lascio riportante qui di seguito le funzioni che   *
*   fanno uso delle funzionalità possibilmente problematiche, di modo che sia possibile disattivarle:                                                           *
*                                                                                                                                                               *
*   - time_functions.c - cronometro() utilizza <conio.h> esclusiva di windows oppure <termios.h> e <sys/select.h> per macOS e Linux                             *
*   - main.c e funztions.c - Utilizzano system(CLEAR) in alcune occasioni, questo va sostituito con system("cls") se su windows, system("clear") se su macOS    *
*                                                                                                                                                               *
*                                                            Se dovessero esserci problemi, ci scusiamo per il disagio. - Lo Sviluppatore (Vuolo Antonio)       *
*                                                                                                                                                               *
*****************************************************************************************************************************************************************
_________________________________________________________________________________________________________________________________________________________________

* Il programma permette di gestire un'agenda scolastica finalizzata al tenere traccia delle attività di studio di uno studente.

Nello specifico, è possibile svolgere 8 operazioni su attività di studio salvate, come suggerito dal menu del programma:

1.  Aggiungere nuove attività di studio. 
    
    E' possibile inserire, per ogni attività di studio:
        - Descrizione
        - Corso di Riferimento
        - Data di Scadenza
        - Tempo Stimato di Completamento
        - Livello di Priorità

    Le attività saranno aggiunte a due strutture dati:
        - Una coda a Priorità (implementata con heap a base 1) per il report settimanale;
        - Un semplice array non ordinato per il file attività;

2.  Stampare a schermo il Report settimanale, riportante le attività in corso, completate o in ritardo per la settimana corrente.
        - Le attività saranno stampate in ordine decrescente di Priorità.

3.  Lavorare su un'attività:

    Alla scelta sarà mostrato un timer durante il quale si suppone lo studente cominci a lavorare sull'attività scelta.
    Dopo aver premuto un tasto qualsiasi, il cronometro si fermerà ed aggiornerà il tempo di lavoro sull'attività in questione.

4.  Stampare tutte le attività attualmente presenti nella coda attività (quelle attualmente in ritardo o in corso)

5.  Permette di controllare lo stato di completamento di un'attività a scelta dell'utente, con percentuale ed una barra di completamento grafica.

6.  Permette di segnare un'attività a scelta dell'utente come completata. 

7. Permette di rimuovere un'attività a scelta dell'utente, sia dalle attività presenti nella coda attività che da quelle nella coda report.

8. Permette di aggiornare il contenuto del file report settimanale ed uscire dal programma.

_________________________________________________________________________________________________________________________________________________________________

La scelta dell'adt (abstract data type) da utilizzare mi è stata abbastanza immediata, visto il mio progetto.

* MOTIVAZIONI PER LA SCELTA DI CODA A PRIORITA' PER IL REPORT SETTIMANALE: 
    -   Non c'era, per me, un reale bisogno di effettuare ricerche mirate (se non per alcune funzioni), vero punto debole di questa struttura dati, ma siccome
        questo programma è ideato per uno studente, ho immaginato non sarebbero state aggiunte attività di studio in una quantità sufficiente da comprometterne 
        significativamente l'efficienza.

    -   Volevo che le attività, unicamente quelle contenute nel file dedicato al report settimanale, venissero stampate per l'utente in ordine, in base alla 
        loro priorità (prima quelle con priorità maggiore), e la struttura dati ideale per ordinare in base ad uno specifico parametro (chiave) è proprio la 
        coda a piorità.

    -   Gli inserimenti sarebbero stati tutti in coda, siccome poi la coda si sarebbe aggiustata da sola in base alla chiave, quindi O(1).

-----------------------------------------------------------------------------------------------------------------------------------------------------------------

* MOTIVAZIONI PER LA SCELTA DELL'ARRAY NON ORDINATO PER LE ATTIVITA':
    -   Principalmente, questo array mi è utile per la gestione delle attività in corso, siccome ho fatto in modo che molte scelte si basassero sul campo ID 
        di una data attività di studio, serviva che questo fosse il più preciso possibile. L'array non è ordinato siccome si sarebbero, in caso, potuti creare
        casi di ID duplicati o mancanti dopo le rimozioni, quindi viene ordinato manualmente ad ogni interazione che potrebbe causare problemi.

    -   Volevo fossero stampate in ordine di ID per una questione di leggibilità e chiarezza, non per piorità, e siccome sarebbero stati eliminati anche elementi
        nel mezzo del mio array, ho preferito utilizzare la seconda coda meramente come un array ed ordinarlo manualmente.

    -   Gli inserimenti sono comunque effettuati in ordine di priorità, ma questa non conta nel caso di questa seconda coda.
    
_________________________________________________________________________________________________________________________________________________________________

* Questo programma è stato sviluppato da Vuolo Antonio, matricola 0512121487, per il progetto del corso di Programmazione e Strutture Dati.