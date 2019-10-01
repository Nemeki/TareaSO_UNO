# Tarea SO
## Integrantes:

* Beatriz Latorre, rol:
* Ignacio Figueroa, rol: 201773526-0

## Instrucciones de uso:

Ejecutar los siguientes comandos en el terminal:

```bash
make
./uno
```
## Comentarios extra:

1. Como está, el programa deja lista la parte inicial del juego, osea reparte 7 cartas en forma aleatoria a cada jugador y 1 a la zona de la última carta.

2. Cada función tiene una explicación en el main.c, tal vez en el futuro se pondrán algunas funciones en otros archivos para descongestionar el main.c

3. Si quieres comprobar la aleatoriedad de la repartición de cartas, mira cada una de las carpetas, bórralas y corre el programa de nuevo.

## Explicación cartas:

Las cartas tienen 3 dígitos en cada línea.
1. El primer dígito es el tipo de carta:
	* 0 = carta de 0 a 9
	* 1 = carta de tipo + (+2 o +4)
	* 2 = carta de tipo reversa, salto o colores
	
2. El segundo dígito es el color:
	* 0 = negro (+4 negra y carta de colores)
	* 1 = azul
	* 2 = rojo
	* 3 = verde
	* 4 = amarillo

3. El tercer dígito depende de lo que sea el primero:
	* Primer dígito 0 = El tercer dígito es el numero de la carta
	* Primer dígito 1 = El tercer dígito es la cantidad de cartas para las cartas más (solo hay 2 y 4)
	* Primer dígito 2 = El tercer dígito es el tipo de carta 
		* 0 = carta de colores
		* 1 = carta de reversa
		* 2 = carta de salto
		
4. Algunos ejemplos:
	* 0 azul.txt `0 1 0`
	
	* 5 amarillo.txt `0 4 5`
	
	* +4 negro.txt `1 0 4`
		
	* +2 amarillo.txt `1 4 2`
		
	* salto verde.txt `2 3 2`
		
	* color negro.txt `2 0 0`
