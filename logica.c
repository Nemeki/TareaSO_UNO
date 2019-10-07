#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "manejo.h"
#include "logica.h"

int primerTurno;

/*
*	turno(int jugador, int *cartasExtra)
*********
*   Funcion "principal" del programa, representa el turno de un jugador.
*	Obviamente su implementacion se va a adaptar al uso de pipes.
**********
*   Input:
*		int jugador: numero del 1-4, representa el jugador
*		int *cartasExtra: representa el numero de cartas al jugador le puede tocar sacar. 
*  		La idea es que no se pierda entre turnos (variable sujeta a modificaciones).
******
*   Returns:
*       Nada
*****/

void turno(int jugador, int *cartasExtra) {
	FILE* fp;
	char archivoCarta[128];
	int n, accion, boolean = 1;
	int ultimaCarta[3];
	int accionCarta[3];
	char mano[10];
	char** cartas;
	
	switch(jugador) {
		case 1:
			strcpy(mano, "mano 1");
			break;
		case 2:
			strcpy(mano, "mano 2");
			break;
		case 3:
			strcpy(mano, "mano 3");
			break;
		case 4:
			strcpy(mano, "mano 4");
			break;
	}
	
	if(*cartasExtra > 0) {
		printf("\nTe toca sacar %d cartas\n", *cartasExtra);
		for(; *cartasExtra > 0; (*cartasExtra)--)
			tomarCarta(mano);
	}
	
MENU: 
	leerUltima(ultimaCarta);
	
	if(primerTurno) {
		primerTurno--;
		if(ultimaCarta[1] == 0) { //carta +4 y de colores
			if(ultimaCarta[2] == 4) *cartasExtra += ultimaCarta[2];
			ultimaCarta[1] = cambiarColor();
			escribirUltima(ultimaCarta);
		} else if(ultimaCarta[0] == 1) { //cartas +2
			*cartasExtra += ultimaCarta[2];
		} else if(ultimaCarta[0] == 2 && ultimaCarta[2] == 1) { //reversa
			//wip
		} else if(ultimaCarta[0] == 2 && ultimaCarta[2] == 2) { //salto
			printf("\nSe salta tu turno\n");
			return;
		}
	}
	
	printf("\nMano jugador %d:\n", jugador);
	n = leerMano(mano, &cartas);
	
	if(boolean)
		printf("%d.Robar carta\n", n + 1);
	else
		printf("%d.Terminar turno\n", n + 1);
	accion = menuMano(n);
	
	if(accion == n + 1) {
		liberarMemoria(cartas, n);
		if(!boolean) return;
		boolean--;
		tomarCarta(mano);
		goto MENU;
	}
	
	snprintf(archivoCarta, sizeof(archivoCarta), "./%s/%s", mano, cartas[accion - 1]);
	fp = fopen(archivoCarta, "r");
	fscanf(fp, "%d %d %d", &accionCarta[0], &accionCarta[1], &accionCarta[2]);
	fclose(fp);
	
	if(cartaCompatible(accionCarta, ultimaCarta, cartas, accion, cartasExtra, mano)) {
		liberarMemoria(cartas, n);
		if(n == 2) printearUno(jugador);
		if(n == 1) {
			printf("\nFin del juego!\n");
			exit(0);
		}
		return;
	}
	
	printf("\nNo puedes poner esa carta\n");
	strcpy(archivoCarta, "");
	liberarMemoria(cartas, n);
	goto MENU;
}

/*
*	cartaCompatible(int *accionCarta, int *ultimaCarta, char **cartas, int accion, int *cartasExtra, char *mano)
*********
*   Funcion auxiliar para comprobar si una jugada es valida. En pocas palabras, son varios
* 	condicionales juntos que, en caso de que la jugada sea valida, realiza el movimiento de
* 	archivos.
**********
*   Input:
*		int *accionCarta: arreglo de enteros que contiene los numeros de la carta a jugar
*		int *ultimaCarta: arreglo de enteros que contiene los numeros de la ultima carta
* 		char **cartas: puntero que apunta a un arreglo de strings que contiene los archivos de la mano 
* 		int accion: numero de la eleccion del jugador
* 		int *cartasExtra: representa el numero de cartas al jugador le puede tocar sacar
* 		char *mano: nombre de la carpeta de la mano actual
******
*   Returns:
*       1 si es un movimiento valido, 0 en caso contrario
*****/

int cartaCompatible(int *accionCarta, int *ultimaCarta, char **cartas, int accion, int *cartasExtra, char *mano) {
	switch(accionCarta[0]) {
		case 0:
			if(ultimaCarta[0] == 0) {
				if(accionCarta[1] != ultimaCarta[1] && accionCarta[2] != ultimaCarta[2]) break;
			} else {
				if(accionCarta[1] != ultimaCarta[1]) break;
			}
			moverUltima(cartas[accion - 1], mano);
			return 1;
			
		case 1:
			if(accionCarta[1] != 0) {
				if(ultimaCarta[0] != 1 || ultimaCarta[2] == 4) {
					if(accionCarta[1] != ultimaCarta[1]) break;
					moverUltima(cartas[accion - 1], mano);
				} else {
					moverUltima(cartas[accion - 1], mano);
				}
			} else {
				accionCarta[1] = cambiarColor();
				moverUltima(cartas[accion - 1], mano);
				escribirUltima(accionCarta);
			}
			*cartasExtra += accionCarta[2];
			return 1;
			
		case 2:
			if(accionCarta[1] != 0) {
				if(accionCarta[2] == ultimaCarta[2] && ultimaCarta[0] == 2) {
					moverUltima(cartas[accion - 1], mano);
				} else {
					if(accionCarta[1] != ultimaCarta[1]) break;
					moverUltima(cartas[accion - 1], mano);
				}
			} else {
				accionCarta[1] = cambiarColor();
				moverUltima(cartas[accion - 1], mano);
				escribirUltima(accionCarta);
			}
			return 1;
	}
	
	return 0;
}

/*
*	leerMano(char *carpeta, char ***cartas)
*********
*   Funcion auxiliar que hace 2 cosas: retornar el numero de cartas en la mano y
* 	crear un arreglo de strings que contiene el nombre de los archivos. Para lo 
* 	segundo utiliza la direccion de un puntero a arreglo de strings.
**********
*   Input:
*		char *carpeta: mano a analizar
*		char ***cartas: referencia de un puntero a arreglo de strings
******
*   Returns:
*       int n: numero de cartas en mano
*****/

int leerMano(char *carpeta, char ***cartas) {
	struct dirent **archivos;
	char destpath[128];
	int i, n;
	
	snprintf(destpath, sizeof(destpath), "./%s/", carpeta);
	n = scandir(destpath, &archivos, filtro, alphasort);
	*cartas = (char**)malloc(n * sizeof(char*));

	for(i = 0; i < n; i++){
		char carta[128];
		strcpy(carta, destpath);
		strcat(carta, archivos[i]->d_name);
		printf("%d.",i + 1);
		leerCarta(carta);
		
		(*cartas)[i] = (char*)malloc(strlen(archivos[i] -> d_name)+1);
		strcpy((*cartas)[i], archivos[i] -> d_name);
	}
	
	for(i = 0; i < n; i++)
		free(archivos[i]);
	free(archivos);
	
	return n;
}

/*
*	leerUltima(int *ultimaCarta)
*********
*   Funcion que lee y guarda los valores de la ultima carta.
**********
*   Input:
*		int *ultimaCarta: arreglo de enteros que contiene los numeros de la ultima carta
******
*   Returns:
*       Nada
*****/

void leerUltima(int *ultimaCarta) {
	FILE* fp; 
	struct dirent **archivos;
	char destpath[128];
	char carta[128];
	
	snprintf(destpath, sizeof(destpath), "./ultima/");
	scandir(destpath, &archivos, filtro, alphasort);
	strcpy(carta, destpath);
	strcat(carta, archivos[0]->d_name);
	printf("\nUltima carta: ");
	leerCarta(carta);
	
	fp = fopen(carta, "r");
	fscanf(fp, "%d %d %d", &ultimaCarta[0], &ultimaCarta[1], &ultimaCarta[2]);
	fclose(fp);
	
	free(archivos[0]);
	free(archivos);
}

/*
*	menuMano(int n)
*********
*   Funcion auxiliar que imprime el menu y guarda la eleccion del jugador en un turno
**********
*   Input:
*		int n: numero de cartas en mano
******
*   Returns:
*       int accion: eleccion del jugador
*****/

int menuMano(int n) {
	char numstr[64];
	int accion;
	
	printf("Elige una accion: ");
	fgets(numstr, 64, stdin);
	while(!sscanf(numstr, "%d", &accion) || accion < 1 || accion > n + 1) {
		printf("Tiene que ser un numero entre 1 y %d\n", n + 1);
		printf("Elige una accion: ");
		fgets(numstr, 64, stdin);
	}
	return accion;
}

/*
*	escribirUltima(int *cartas)
*********
*   Escribe nuevos valores a la ultima carta; usada por la carta de colores y +4
**********
*   Input:
*		int *cartas: arreglo de enteros con los nuevos valores
******
*   Returns:
*       Nada.
*****/

void escribirUltima(int *cartas) {
	FILE* fp; 
	struct dirent **archivos;
	char destpath[128];
	char carta[128];
	
	snprintf(destpath, sizeof(destpath), "./ultima/");
	scandir(destpath, &archivos, filtro, alphasort);
	strcpy(carta, destpath);
	strcat(carta, archivos[0]->d_name);
	
	fp = fopen(carta, "w");
	fprintf(fp,"%d\n%d\n%d", cartas[0], cartas[1], cartas[2]);
	fclose(fp);
	
	free(archivos[0]);
	free(archivos);
}

/*
*	cambiarColor()
*********
*   Funcion para cambiar el negro por otro color.
**********
*   Input:
*		Ninguno.
******
*   Returns:
*       int color: valor del nuevo color
*****/

int cambiarColor() {
	char numstr[64];
	int color;
	
	printf("\nElige un color: \n");
	printf("1.Azul\n2.Rojo\n3.Verde\n4.Amarillo\n");
	printf("Color: ");
	fgets(numstr, 64, stdin);
	while(!sscanf(numstr, "%d", &color) || color < 1 || color > 4) {
		printf("Tiene que ser un numero entre 1 y 4\n");
		printf("Color: ");
		fgets(numstr, 64, stdin);
	}
	
	return color;
}

/*
*	checkMazo() 
*********
*   Revisa si quedan cartas en el mazo
**********
*   Input:
*		Ninguno
******
*   Returns:
*       int c: 1 si hay cartas, 0 si no hay
*****/

int checkMazo() {
	DIR *dp;
	struct dirent *ep; 
	int c = -2;
	
	dp = opendir("./mazo");
	while ((ep = readdir (dp))) {
		c++;
		if(c > 0) break;
	}
	closedir (dp);
	
	return c;
}

/*
*	printearUno(int j)
*********
*   Printea el anuncio de "uno" cuando a un jugador le queda una carta
**********
*   Input:
*		int j: jugador
******
*   Returns:
*       Nada.
*****/

void printearUno(int j) {
	printf("\n******** ********\n");
	printf(" ***** UNO ***** \n");
	printf("******** ********\n");
	printf("Al jugador %d le queda una carta!\n", j);
}
 
/*
*	liberarMemoria(char **ptr, int n)
*********
*   Funcion auxiliar para liberar el arreglo de strings
**********
*   Input:
*		char **ptr: puntero al arreglo de strings
*		int n: cantidad de strings que tiene el arreglo
******
*   Returns:
*       Nada.
*****/ 
 
void liberarMemoria(char **ptr, int n) {
	for(int i = 0; i < n; i++ )
			free(ptr[i]);
		free(ptr);
}