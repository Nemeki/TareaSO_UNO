#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <errno.h>
#include "manejo.h"
#include "logica.h"
#include "procesos.h"

int primerTurno = 1;

int main(int argc, char **argv)
{
	DIR* dp = opendir("mazo");
	
	srand(time(NULL));
	if (dp) {
		closedir(dp);
	} else if (ENOENT == errno) {
		crearCarpetas();
		crearColores();
		crearMas();
		crearExtras();
		repartirCartas();
	}
	
	printf("Bienvenido a UNO\n");
	procesos();
	
	//while(checkMazo()) turno(1, &cartasExtra);
	//if(!checkMazo()) printf("\nSe agotaron las cartas...\n");
	return 0;
}
