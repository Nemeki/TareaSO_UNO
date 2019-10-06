#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

  pid_t pid;
  int turno;
  int p01[2], p10[2], p12[2], p21[2], p23[2], p32[2], p30[2], p03[2];
  

  int procesosYTurnos(){
	turno = 0;
	pid = fork();
	pipe(p01);

	if(pid == 0){
		turno = 1;
		pid = fork();
		if(pid == 0){
			turno = 2;
			pid = fork();
		}
	}
	else{
		turno = 0;
	}
	return turno;
  }
  