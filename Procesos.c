 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include "procesos.h"

 /*
*	 procesos()
*********
*   Crea los procesos con sus pipes y hace los cambios de turnos
**********
*   Input:
*		Ninguno
******
*   Returns:
*       Nada
*****/

void procesos(){
	pid_t pid;
	int idJugador;
	int p01[2], p10[2], p12[2], p21[2], p23[2], p32[2], p30[2], p03[2];
 
	bool jugando, reversa;
	int readbytes;
	char buffer[SIZE];

	jugando = TRUE;
	reversa = FALSE;

	idJugador = 0;
	pipe(p01);
	pipe(p10);
	pipe(p03);
	pipe(p30);
	pid = fork();

	if(pid == 0){
		idJugador = 1;
		close(p01[1]);
		close(p10[0]); 
		pipe(p12);
		pipe(p21);
		pid = fork();
		if(pid == 0){
			idJugador = 2;
			close(p12[1]);
			close(p21[0]);
			pipe(p23);
			pipe(p32);
			pid = fork();
			if(pid == 0){
				close(p23[1]);
				close(p32[0]);
				close(p03[1]);
				close(p30[0]);
				idJugador = 3;	
			}
			else{
				close(p23[0]);
				close(p32[1]);
			}
		}
		else{
			close(p12[0]);
			close(p21[1]);
		}
	}
	else{
		close(p01[0]);
		close(p10[1]);
		close(p03[0]);
		close(p30[1]);
		idJugador = 0;
	}
	
	if(idJugador == 0){
		//Jugar turno.
		//pipe normal
		if(reversa == TRUE){
			strcpy(buffer, "turno acabado");
			write( p03[1], buffer, strlen(buffer));
			close( p03[1]);
			}
		else{
			strcpy(buffer, mensaje);
			write( p01[1], buffer, "turno acabado");
			close( p01[1]);
			}
		}
	while(jugando){
		if(reversa == TRUE){
			switch (idJugador){
				case 0:
					readbytes = read(p10[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p10[0]);
					break;

				case 1:
					readbytes = read(p21[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p21[0]);
					break;

				case 2:
					readbytes = read(p32[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p32[0]);
					break;

				case 3:
					readbytes = read(p03[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p03[0]);
					//borrar despues
					jugando = FALSE;
					break;
				}
			}
		else{
			switch (idJugador){
				case 0:
					readbytes = read(p30[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p30[0]);
					break;

				case 1:
					readbytes = read(p01[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p01[0]);
					break;

				case 2:
					readbytes = read(p12[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p12[0]);
					break;

				case 3:
					readbytes = read(p23[0], buffer, SIZE)
					while( readbytes > 0){
						write(1, buffer, readbytes);
						}
					close(p23[0]);
					//borrar despues
					jugando = FALSE;
					break;
				}
			}
		
		//Jugar

		if(reversa == TRUE){
			switch (idJugador){
				case 0:
					strcpy(buffer, "turno acabado");
					write( p03[1], buffer, strlen(buffer));
					close( p03[1]);
					break;

				case 1:
					strcpy(buffer, "turno acabado");
					write( p10[1], buffer, strlen(buffer));
					close( p10[1]);
					break;

				case 2:
					strcpy(buffer, "turno acabado");
					write( p21[1], buffer, strlen(buffer));
					close( p21[1]);
					break;

				case 3:
					strcpy(buffer, "turno acabado");
					write( p32[1], buffer, strlen(buffer));
					close( p32[1]);
					break;
				}
			}
		else{
			switch (idJugador){
				case 0:
					strcpy(buffer, "turno acabado");
					write( p01[1], buffer, strlen(buffer));
					close( p01[1]);
					break;

				case 1:
					strcpy(buffer, "turno acabado");
					write( p12[1], buffer, strlen(buffer));
					close( p12[1]);
					break;

				case 2:
					strcpy(buffer, "turno acabado");
					write( p23[1], buffer, strlen(buffer));
					close( p23[1]);
					break;

				case 3:
					strcpy(buffer, "turno acabado");
					write( p30[1], buffer, strlen(buffer));
					close( p30[1]);
					break;
				}
			}
		}
	}