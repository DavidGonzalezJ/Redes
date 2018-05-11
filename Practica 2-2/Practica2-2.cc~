#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <math.h>


void ejercicio4(){
	
	time_t seconds;
    	seconds = time (NULL);
	//printf ("%ld:%ld:%ld \n", (seconds/3600)%24,(seconds/60)%60, seconds%60);
}


int main(int argc, char** argv) {
	bool exit = false;
	struct addrinfo *result;
	struct addrinfo hints;
	memset((void *) &hints, '\0', sizeof(struct addrinfo));
	struct sockaddr cliente;
	socklen_t cliente_len;
	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	
	hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
	hints.ai_family   = AF_INET; // IPv4
	hints.ai_socktype = SOCK_DGRAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	if(rc!=0){
		std::cout << "Error getaddrinfo():" << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(result->ai_family, result->ai_socktype, 0);

	bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

	while (!exit) {
	  char buffer[256];
	  char bufferSend[256];
	  
	  int bytes = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &cliente,
	      &cliente_len);
	  buffer[bytes]='\0';
		 
	    
	  getnameinfo((struct sockaddr *) &cliente, cliente_len, host, NI_MAXHOST,
	      serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

	  std::cout<< "Conexión desde Host:" << host << " Puerto: "<< serv <<"\n";

	int aux;
	switch(buffer[0]){
		case 't':
			struct tm* ctime;
			time_t tiempo;

			time (&tiempo);
			ctime = localtime(&tiempo);

			aux = strftime(bufferSend, 256 ,"%Y-%m-%d", ctime);
			sendto(sd, bufferSend, aux, 0, (struct sockaddr *) &cliente, cliente_len);		
		break;
		case 'd':
		break;
		case 'q':
			exit = true;
			std::cout << "Saliendo...\n";
			break;
		default:
			std::cout << "Comando no soportado " << buffer[0]<< "\n";
			break;		
	}
	  
	}

    return 0;
}


