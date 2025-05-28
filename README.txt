*IMPORTANTE******************************************************************************************************************************************************    
*                                                                                                                                                               *
*   Il programma fa uso di funzioni definite solo sulle macchine Windows o solo su quelle Linux e macOS, nonostante abbia cercato di renderle il più portabili  *
*   possibile, c'è comunque la possibilità che si incorra in problemi sulle macchine Linux e macOS. In caso, lascio riportante qui di seguito le funzioni che   *
*   fanno uso delle funzionalità possibilmente problematiche, di modo che sia possibile disattivarle:                                                           *
*                                                                                                                                                               *
*   - time_functions.c - cronometro() utilizza <conio.h> esclusiva di windows oppure <termios.h> e <sys/select.h> per macOS e Linux                             *
*   - main.c e funztions.c - Utilizzano system(CLEAR) in alcune occasioni, questo va sostituito con system("cls") se su windows, system("clear") se su macOS    *
*   - main.c e time_functions.c - utilizzano sleep(), questa funzione ha una sintassi lievemente diversa su Windows o Linux, quindi potrebbe non funzionare     *
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
    
*SPECIFICHE TECNICHE DELL'IMPLEMENTAZIONE:

    + Tutte le attività inserite saranno salvate in un array di appoggio e nella coda a priorità dedicata al report, saranno aggiornati solamente i file 
        attivita.txt ed attivita_menu.txt.

    + Tutte le attività rimosse saranno salvate immediatamente in array di appoggio e coda a priorità, ma saranno aggiornati solamente i file attivita.txt 
        ed attivita_menu.txt.
    
    + Il file report_settimanale.txt verrà aggiornato solamente al termine dell'esecuzione del programma, con scelta numero 8.
    
    + Le attività completate saranno rimosse dall'array di appoggio, mentre rimarranno visibili nella coda a priorità dedicata al report. Stesso vale per i file.

_________________________________________________________________________________________________________________________________________________________________

* Questo programma è stato sviluppato da Vuolo Antonio, matricola 0512121487, per il progetto del corso di Programmazione e Strutture Dati.