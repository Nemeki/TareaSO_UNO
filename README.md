# Tarea SO
## Integrantes:

* Beatriz Latorre
	* Rol: 201573543-3
* Ignacio Figueroa
	* Rol: 201773526-0

## Instrucciones de ejecución:

Ejecutar los siguientes comandos en el terminal:

```bash
make uno
make clean
./uno
```
## Comentarios de uso:

1. En esta entrega se trabajó en la generación de la lógica del juego. Es posible jugar solo con el jugador 1 (con las reglas como deben ser) y terminar el juego de forma normal (ganando), o terminándose el mazo. Algunas consideraciones:
	* Usar cartas +2 o +4 hace que uno mismo tenga que sacar las cartas en el siguiente turno.
	* La implementación de las cartas de salto y reversa va a depender de la comunicación entre pipes, así que de momento no hacen nada (siguen la mismas reglas de color y tipo).
	* Asimismo, la implementación de la función de turnos está sujeta a cambios y va a depender de los pipes.

2. La implementación de las cartas al inicio (si la primera carta es una carta de colores, carta de salto, etc...) se hizo según las indicaciones del enunciado. Por ejemplo, si la primera carta es un +4, entonces el jugador 1 elige el nuevo color y el siguiente jugador debe sacar 4 cartas (en este caso uno mismo).

3. Modo debug: La primera vez que se corra el programa, se crearán todos los archivos y carpetas correspondientes. Si se corre con las carpetas ya existentes, se jugará de la forma en que se encuentren los archivos en las carpetas. Esto significa que es posible empezar una partida de la forma que se quiera, por ejemplo partir con 2 cartas en la carpeta "mano 1" para probar el término del programa.

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

## Procesos:

Es aun una prueba y deseamos que no sea parte de lo evaluado pero recibir feedback igualmente si es posible