void turno(int *jugador, int *cartasExtra, int *salto, int *reversa, int *termino);
void leerUltima(int *ultimaCarta);
void escribirUltima(int *cartas);
void liberarMemoria(char **ptr, int n);
void printearUno(int j);
int cartaCompatible(int *accionCarta, int *ultimaCarta, char **cartas, int accion, int *cartasExtra, char *mano, 
					int *jugador, int *salto, int *reversa);
int cambiarColor();
int menuMano(int n);
int checkMazo();
int leerMano(char *carpeta, char ***cartas);
int proximoJugador(int actual, int reversa);
