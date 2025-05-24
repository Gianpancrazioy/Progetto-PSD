test: testing.o testing_item.o testing_adt.o
	gcc testing.o testing_item.o testing_adt.o -o test.exe

testing.o: testing.c
	gcc -c testing.c

testing_item.o: testing_item.c
	gcc -c testing_item.c

testing_adt.o: testing_adt.c
	gcc -c testing_adt.c

calendario: main.o adt_pqueue.o time_functions.o item.o functions.o
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