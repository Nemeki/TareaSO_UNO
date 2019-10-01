void crearColores(); // crea cartas de colores del 0 al 9 (repetidas tienen un -1 al final)
void crearMas(); // crea cartas +2 y +4
void crearExtras(); //crea cartas de reversa, salto y colores (carta negra)
void crearCarpetas(); // crea las carpetas mazo, mano 1, mano 2, mano 3, mano 4 y ultima (carpeta donde va la ultima carta)
void mostrarArchivos(); // printea los archivos de alguna carpeta (en este caso esta puesta para que printee los archivos de mazo)
void leerCarta(char *archivo); // lee una carta (abajo explicacion para las cartas
void moverCarta(char *archivo, char *origen, char *destino); // mueve una carta a una carpeta ej: moverCarta("0 azul.txt", mazo, mano 1);
void moverUltima(char *archivo, char *origen); // lo mismo que moverCarta solo que el destino es la carpeta ultima y si tiene una carta esta se borra (como sale en el enunciado)
void tomarCarta(char *destino); // elige una carta al azar del mazo y la mueve a destino
void repartirCartas(); // reparte 7 cartas al azar a los 4 jugadores y pone una en "ultima"
int contarCartas(char *carpeta); // cuenta los archivos que hay en un carpeta (sin contar "." y "..") ej: contarCartas("mano 1");
int filtro(const struct dirent *entry); // funcion auxiliar para filtrar "." y ".." de los resultados

Las cartas tienen 3 digitos en cada linea.
El primer digito es el tipo de carta:
	0 = carta de 0 a 9
	1 = carta de tipo + (+2 o +4)
	2 = carta de tipo reversa, salto o colores
	
El segundo digito es el color:
	0 = negro (+4 negra y carta de colores)
	1 = azul
	2 = rojo
	3 = verde
	4 = amarillo

El tercer digito depende de lo que sea el primero:
	Primer digito 0 = El tercer digito es el numero de la carta
	Primer digito 1 = El tercer digito es la cantidad de cartas para las cartas mas (solo hay 2 y 4)
	Primer digito 2 = El tercer digito es el tipo de carta 
		0 = carta de colores
		1 = carta de reversa
		2 = carta de salto
		
Ej:
	0 azul.txt 
		0
		1
		0
	
	5 amarillo.txt
		0
		4
		5
		
	+4 negro.txt
		1
		0
		4
		
	+2 amarillo.txt
		1
		4
		2
		
	salto verde.txt
		2
		3
		2
		
	color negro.txt //carta de colores
		2
		0
		0
		