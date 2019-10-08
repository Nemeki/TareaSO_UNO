main.o: main.c
	gcc -c main.c -Wall

manejo.o: manejo.c manejo.h
	gcc -c manejo.c -Wall

procesos.o: procesos.c procesos.h
	gcc -c procesos.c -Wall

logica.o: logica.c logica.h
	gcc -c logica.c -Wall
	
uno: main.o manejo.o logica.o procesos.o
	gcc main.o manejo.o logica.o procesos.o -o uno

clean:
	find . -name '*.o' -type f -delete
