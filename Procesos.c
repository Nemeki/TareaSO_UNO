#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

  pid_t pid;
  int idJugador;
  int p01[2], p10[2], p12[2], p21[2], p23[2], p32[2], p30[2], p03[2];
  

  int procesoseIDJugador(){
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
	return idJugador;
  }
  
  void escribirMensaje(char mensaje[50], int pipe[2]){
	char buffer[SIZE];
	strcpy(buffer, mensaje);
	write( b[1], buffer, strlen(buffer));
	close( b[1] );
  }

  void turnos(int id){
	bool jugando, reversa;
	jugando = TRUE;
	reversa = FALSE;
	if(id == 0){
		//Jugar turno.

		if(reversa == TRUE){
		
		}
	}
	while jugando{
	
	}
  }