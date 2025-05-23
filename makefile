calendario.exe: main.o adt_pqueue.o time_functions.o item.o functions.o
	gcc  main.o adt_pqueue.o time_functions.o item.o functions.o -o calendario.exe

main.o: main.c 
	gcc -c main.c

adt_pqueue.o: adt_pqueue.c
	gcc -c adt_pqueue.c

time_functions.o: time_functions.c
	gcc -c time_functions.c

item.o: item.c
	gcc -c item.c

functions.o: functions.c
	gcc -c functions.c

clean:
	rm *.o *.exe