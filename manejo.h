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