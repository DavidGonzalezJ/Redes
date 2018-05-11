#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
void ejercicio4(){
	
	time_t seconds;
    seconds = time (NULL);
 
    	printf ("Numero de horas desde el 1 de Enero de 1970 es %ld \n", seconds);
	printf ("La hora (GMT 0)es: %ld:%ld:%ld \n", (seconds/3600)%24,(seconds/60)%60, seconds%60);
	printf(ctime(&seconds));
}

void ejercicio5(){
	struct timespec tiempo, tiempoF;
	double iT, fT;
	if(clock_gettime(CLOCK_REALTIME, &tiempo) == -1){
		perror("Fallo en el tiempo inicio");
		exit( EXIT_FAILURE );
	}
	iT = tiempo.tv_sec * pow(10,9);
	for(int i = 0; i < 10000; i++){}
	if(clock_gettime(CLOCK_REALTIME, &tiempoF) == -1){
		perror("Fallo en el tiempo final");
		exit( EXIT_FAILURE );
		} 
	fT = (tiempoF.tv_nsec - tiempo.tv_nsec)* pow(10,-9);
	//fT -= iT;
	printf("Tarda en hacer 10000 iteraciones %lf segundos\n", fT);
	
}

void ejercicio6(){
	char s[100];
	struct tm* ctime;
	time_t tiempo;
	
	time (&tiempo);
	ctime = localtime(&tiempo);
	
	strftime(s, 100 ,"Estamos en el año %Y\nHoy es %A, %H:%M\n", ctime);
	printf("%s", s);	
}

int main() {

	ejercicio4();
	ejercicio5();
	ejercicio6();
    return 1;
}
