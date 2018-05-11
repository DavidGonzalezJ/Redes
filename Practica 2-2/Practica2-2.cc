#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv) {
	bool exit = false;
	struct addrinfo *result;
	struct addrinfo hints;
	memset((void *) &hints, '\0', sizeof(struct addrinfo));
	struct sockaddr cliente;
	socklen_t cliente_len = sizeof(cliente);
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
	   
	  size_t bytes = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &cliente,
	      &cliente_len);
	  buffer[bytes]='\0';

	if(bytes !=0){
		getnameinfo(&cliente, cliente_len, host, NI_MAXHOST,
	      serv, NI_MAXSERV, NI_NUMERICHOST);

	  std::cout<< bytes << " bytes de " << host << " " << serv << "\n";
	}
		

	int aux;

	struct tm* ctime;
	time_t tiempo;
	time (&tiempo);
	ctime = localtime(&tiempo);

	switch(buffer[0]){
		case 't':
			aux = strftime(buffer, 256 ,"%H:%M:%S", ctime);
			sendto(sd, buffer, aux, 0, (struct sockaddr *) &cliente, cliente_len);		
		break;
		case 'd':			

			aux = strftime(buffer, 256 ,"%Y-%m-%d", ctime);
			sendto(sd, buffer, aux, 0, (struct sockaddr *) &cliente, cliente_len);
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
	freeaddrinfo(result);


    return 0;
}


