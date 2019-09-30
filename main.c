#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

void crearColores();
void crearMas();
void crearExtras();
void crearCarpetas();
void mostrarArchivos();
void leerCarta(char *archivo);
void moverCarta(char *archivo, char *origen, char *destino);
void moverUltima(char *archivo, char *origen);
void tomarCarta(char *destino);
void repartirCartas();
int contarCartas(char *carpeta);
int filtro(const struct dirent *entry);

int main(int argc, char **argv)
{
	srand(time(NULL));
	crearCarpetas();
	crearColores();
	crearMas();
	crearExtras();
	repartirCartas();
	
	return 0;
}

void crearColores() {
	FILE *fp;
	int i, j, k;
	char color[15];
	
	for(i = 1; i < 5; i++) {
		switch(i) {
			case 1:
				strcpy(color, "azul");
				break;
			case 2:
				strcpy(color, "rojo");
				break;
			case 3:
				strcpy(color, "verde");
				break;
			case 4:
				strcpy(color, "amarillo");
				break;
		}
		
		char buffer[64]; 
		snprintf(buffer, sizeof(char) * 64, "./mazo/%i %s.txt", 0, color);
		fp = fopen(buffer, "w+");
		fprintf (fp,"%d\n%d\n%d", 0, i, 0);
		fclose(fp);
		
		for(k = 0; k < 2; k++) {
			if(k == 1) strcat(color, "-1");
			for(j = 1; j < 10; j++) {
				char buffer[64]; 
				snprintf(buffer, sizeof(char) * 64, "./mazo/%i %s.txt", j, color);
				fp = fopen(buffer, "w+");
				fprintf (fp,"%d\n%d\n%d", 0, i, j);
				fclose(fp);
			}
		}
	}
}

void crearMas() {
	FILE *fp;
	int i, j;
	char color[15];
	
	for(i = 1; i < 5; i++) {
		char buffer[64];
		
		if(i > 1)
			snprintf(buffer, sizeof(char) * 64, "./mazo/+4 negro-%d.txt", i - 1);
		else
			snprintf(buffer, sizeof(char) * 64, "./mazo/+4 negro.txt");
		fp = fopen(buffer, "w+");
		fprintf (fp,"%d\n%d\n%d", 1, 0, 4);
		fclose(fp);
		
		switch(i) {
			case 1:
				strcpy(color, "azul");
				break;
			case 2:
				strcpy(color, "rojo");
				break;
			case 3:
				strcpy(color, "verde");
				break;
			case 4:
				strcpy(color, "amarillo");
				break;
		}
		
		for(j = 0; j < 2; j++) {
			if(j == 1) strcat(color, "-1");
			char buffer[64]; 
			snprintf(buffer, sizeof(char) * 64, "./mazo/+2 %s.txt", color);
			fp = fopen(buffer, "w+");
			fprintf (fp,"%d\n%d\n%d", 1, i, 2);
			fclose(fp);
		}
	}
}

void crearExtras() {
	FILE *fp;
	int i, j;
	char color[15];
	
	for(i = 1; i < 5; i++) {
		char buffer[64];
		
		if(i > 1)
			snprintf(buffer, sizeof(char) * 64, "./mazo/color negro-%d.txt", i - 1);
		else
			snprintf(buffer, sizeof(char) * 64, "./mazo/color negro.txt");
		fp = fopen(buffer, "w+");
		fprintf (fp,"%d\n%d\n%d", 2, 0, 0);
		fclose(fp);
		
		switch(i) {
			case 1:
				strcpy(color, "azul");
				break;
			case 2:
				strcpy(color, "rojo");
				break;
			case 3:
				strcpy(color, "verde");
				break;
			case 4:
				strcpy(color, "amarillo");
				break;
		}
		
		for(j = 0; j < 2; j++) {
			if(j == 1) strcat(color, "-1");
			char buffer[64];
			char buffer2[64];
			
			snprintf(buffer, sizeof(char) * 64, "./mazo/reversa %s.txt", color);
			fp = fopen(buffer, "w+");
			fprintf (fp,"%d\n%d\n%d", 2, i, 1);
			fclose(fp);
			
			snprintf(buffer2, sizeof(char) * 64, "./mazo/salto %s.txt", color);
			fp = fopen(buffer2, "w+");
			fprintf (fp,"%d\n%d\n%d", 2, i, 2);
			fclose(fp);
		}
	}
}

void crearCarpetas() {
	mkdir("./mazo", 0777);
	mkdir("./mano 1", 0777);
	mkdir("./mano 2", 0777);
	mkdir("./mano 3", 0777);
	mkdir("./mano 4", 0777);
	mkdir("./ultima", 0777);
}

void mostrarArchivos() {
	DIR *dp;
	struct dirent *ep; 
	dp = opendir("./mazo");
	
	if (dp != NULL) {
		while ((ep = readdir (dp))) {
			puts (ep->d_name);
		}
		closedir (dp);
	}
}

void moverCarta(char *archivo, char *origen, char *destino) {
	char srcpath[128];
	char destpath[128];
	
	snprintf (srcpath, sizeof(srcpath), "./%s/%s", origen, archivo);
	snprintf (destpath, sizeof(destpath), "./%s/%s", destino, archivo);
	rename(srcpath, destpath);
}

void leerCarta(char *archivo) {
	int carta[3];
	char color[15];
	FILE* fp; 
	
	fp = fopen(archivo, "r");
	fscanf(fp, "%d %d %d", &carta[0], &carta[1], &carta[2]);
	fclose(fp);
	
	switch(carta[1]) {
		case 0:
			strcpy(color, "negro");
			break;
		case 1:
			strcpy(color, "azul");
			break;
		case 2:
			strcpy(color, "rojo");
			break;
		case 3:
			strcpy(color, "verde");
			break;
		case 4:
			strcpy(color, "amarillo");
			break;
	}
	
	switch(carta[0]) {
		case 0:
			printf("Carta %d %s\n", carta[2], color);
			break;
		case 1:
			printf("Carta +%d %s\n", carta[2], color);
			break;
		case 2:
			switch(carta[2]) {
				case 0:
					printf("Carta de colores\n");
					break;
				case 1:
					printf("Carta de reversa %s\n", color);
					break;
				case 2:
					printf("Carta de salto %s\n", color);
					break;
			}
			break;
	}
}

int contarCartas(char *carpeta) {
	DIR *dp;
	struct dirent *ep; 
	char destpath[128];
	int c = -2;
	
	snprintf(destpath, sizeof(destpath), "./%s", carpeta);
	dp = opendir(destpath);
	
	while ((ep = readdir (dp))) {
		c++;
	}
	closedir (dp);
	
	return(c);
}

void moverUltima(char *archivo, char *origen) {
	DIR *dp;
	struct dirent *ep;
	char srcpath[265];
	
	dp = opendir("./ultima");
	
	while ((ep = readdir (dp))) {
		if(strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
			snprintf(srcpath, sizeof(srcpath), "./ultima/%s", ep->d_name);
			remove(srcpath);
		}
	}
	
	closedir (dp);
	moverCarta(archivo, origen, "ultima");
}

void tomarCarta(char *destino) {
	int i, k, n;
	struct dirent **archivos;
	
	n = scandir("./mazo", &archivos, filtro, alphasort);
	k = rand() % n;
	
	moverCarta(archivos[k]->d_name, "mazo", destino);
	
	for(i = 0; i < n; i++)
		free(archivos[i]);
	free(archivos);
}

int filtro(const struct dirent *entry) {
   return(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0);
}

void repartirCartas() {
	int i, j;
	
	tomarCarta("ultima");
	
	for(i = 1; i < 5; i++) {
		char destino[10];
		switch(i) {
			case 1:
				strcpy(destino, "mano 1");
				break;
			case 2:
				strcpy(destino, "mano 2");
				break;
			case 3:
				strcpy(destino, "mano 3");
				break;
			case 4:
				strcpy(destino, "mano 4");
				break;
		}
		
		for(j = 0; j < 7; j++)
			tomarCarta(destino);
	}
}