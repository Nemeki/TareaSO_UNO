Integrantes
    Beatriz Latorre
        Rol: 201573543-3
    Ignacio Figueroa
        Rol: 201773526-0
        
Instrucciones de ejecución
Ejecutar los siguientes comandos en el terminal:
    make uno
    make clean
    ./uno
    
Comentarios extra:
    * Todo lo de forks está en main.c, la lógica del juego en logica.c y el manejo en manejo.c.
    * Los procesos tienen la siguiente lógica: P1 (el padre de todos) es el gestionador de turnos, mientras los demás (P2, P3, P4) están constantemente 
            esperando un input en su respectivo PIPE con P1, el cual indica a quién le toca (obviamente también le puede tocar a P1).
    * De todas formas se adjunta un dibujo que facilita el entendimineto de los procesos (pipes.jpg).
    * Cada vez que termina el turno de un jugador, el proceso al que le corresponde printea su nombre (para que sea vea que es legit y que son 4 procesos).
