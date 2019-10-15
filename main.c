#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <unistd.h> 
#include <errno.h>
#include "manejo.h"
#include "logica.h"
#define P1 (pid1 > 0 && pid2 > 0 && pid3 > 0)
#define P2 (pid1 == 0)
#define P3 (pid1 > 0 && pid2 == 0)
#define P4 (pid1 > 0 && pid2 > 0 && pid3 == 0)

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
	int i;
	int arguments[5];
	arguments[0] = 1; //jugador que le toca
	arguments[1] = 0; //cartas extras
	arguments[2] = 0; //salto?
	arguments[3] = 0; //reversa?
	arguments[4] = 0; //termino?
	
	pid_t pid1, pid2, pid3;
	int tubo_1_2[2];
	int tubo_2_1[2];
	int tubo_1_3[2];
	int tubo_3_1[2];
	int tubo_1_4[2];
	int tubo_4_1[2];
	
	pid1 = pid2 = pid3 = 0;
	
	pipe(tubo_1_2);
	pipe(tubo_2_1);
	pipe(tubo_1_3);
	pipe(tubo_3_1);
	pipe(tubo_1_4);
	pipe(tubo_4_1);
	
	turno(&arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
	printf("\nSoy P1!!\n");
	
	pid1 = fork();
	if(pid1 > 0) pid2 = fork();
	if(pid1 > 0 && pid2 > 0) pid3 = fork();
	if(P1) {
		close(tubo_2_1[1]);
		close(tubo_3_1[1]);
		close(tubo_4_1[1]);
	} else if(P2) {
		close(tubo_1_2[1]);
	} else if(P3) {
		close(tubo_1_3[1]);
	} else if(P4) {
		close(tubo_1_4[1]);
	}
	
	if(P1) {
		if(arguments[0] == 2) {
			for(i = 0; i < 5; i++) write(tubo_1_2[1], &arguments[i], sizeof(int));
		} else {
			for(i = 0; i < 5; i++) write(tubo_1_4[1], &arguments[i], sizeof(int));
		}
	}
	
	while(checkMazo()) {
		if(P1) {
			switch(arguments[0]) { //de donde leer
				case 2:
					for(i = 0; i < 5; i++) read(tubo_2_1[0], &arguments[i], sizeof(int));
					break;
				case 3:
					for(i = 0; i < 5; i++) read(tubo_3_1[0], &arguments[i], sizeof(int));
					break;
				case 4:
					for(i = 0; i < 5; i++) read(tubo_4_1[0], &arguments[i], sizeof(int));
					break;
			}
		EMERGENCYEXIT:
			if(arguments[4] || !checkMazo()) { //finalizacion
				arguments[4] = 1;
				for(i = 0; i < 5; i++) {
					write(tubo_1_2[1], &arguments[i], sizeof(int));
					write(tubo_1_3[1], &arguments[i], sizeof(int));
					write(tubo_1_4[1], &arguments[i], sizeof(int));
				}
				break;
			}
			
			switch(arguments[0]) { //hacia donde escribir
				case 1:
					turno(&arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
					if(arguments[4] || !checkMazo()) goto EMERGENCYEXIT;
					if(arguments[0] == 2) {
						for(i = 0; i < 5; i++) write(tubo_1_2[1], &arguments[i], sizeof(int));
					} else {
						for(i = 0; i < 5; i++) write(tubo_1_4[1], &arguments[i], sizeof(int));
					}
					printf("\nSoy P1!!\n");
					break;
				case 2:
					for(i = 0; i < 5; i++) write(tubo_1_2[1], &arguments[i], sizeof(int));
					break;
				case 3:
					for(i = 0; i < 5; i++) write(tubo_1_3[1], &arguments[i], sizeof(int));
					break;
				case 4:
					for(i = 0; i < 5; i++) write(tubo_1_4[1], &arguments[i], sizeof(int));
					break;
			}
		} else if(P2) {
			for(i = 0; i < 5; i++) read(tubo_1_2[0], &arguments[i], sizeof(int));
			if(arguments[4]) break;
			turno(&arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
			for(i = 0; i < 5; i++) write(tubo_2_1[1], &arguments[i], sizeof(int));
			printf("\nSoy P2!!\n");
		} else if(P3) {
			for(i = 0; i < 5; i++) read(tubo_1_3[0], &arguments[i], sizeof(int));
			if(arguments[4]) break;
			turno(&arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
			for(i = 0; i < 5; i++) write(tubo_3_1[1], &arguments[i], sizeof(int));
			printf("\nSoy P3!!\n");
		} else if(P4) {
			for(i = 0; i < 5; i++) read(tubo_1_4[0], &arguments[i], sizeof(int));
			if(arguments[4]) break;
			turno(&arguments[0], &arguments[1], &arguments[2], &arguments[3], &arguments[4]);
			for(i = 0; i < 5; i++) write(tubo_4_1[1], &arguments[i], sizeof(int));
			printf("\nSoy P4!!\n");
		}
	}
	
	if(P1) {
		close(tubo_2_1[0]);
		close(tubo_3_1[0]);
		close(tubo_4_1[0]);
		close(tubo_1_2[0]);
		close(tubo_1_3[0]);
		close(tubo_1_4[0]);
		close(tubo_1_2[1]);
		close(tubo_1_3[1]);
		close(tubo_1_4[1]);
		if(!checkMazo()) printf("\nSe agotaron las cartas...\n");
	} else if(P2) {
		close(tubo_1_2[0]);
		close(tubo_2_1[0]);
		close(tubo_2_1[1]);
	} else if(P3) {
		close(tubo_1_3[0]);
		close(tubo_3_1[0]);
		close(tubo_3_1[1]);
	} else if(P4) {
		close(tubo_1_4[0]);
		close(tubo_4_1[0]);
		close(tubo_4_1[1]);
	}
	
	return 0;
}