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
	hints.ai_socktype = SOCK_STREAM;

	size_t rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	size_t sd = socket(result->ai_family, result->ai_socktype, 0);

	bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);
	listen(sd, 5);
	char buffer[256];
	int i =0;
	int c;


	while (1) {
	  size_t cliente_sd = accept(sd, (struct sockaddr *) &cliente, &cliente_len);
	  
	  getnameinfo((struct sockaddr *) &cliente, cliente_len, host, 
	      NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
	  std::cout << "Conexión desde Host: "<<host << "Puerto: "<< serv << "\n";
	  size_t c;
	  do {
		c = recv(cliente_sd, buffer, 255, 0);
		send(cliente_sd, buffer, c, 0);
	  } while ( c > 0);
 	  
	  if(c ==0) std::cout << "Conexión terminada \n";
	}

	freeaddrinfo(result);


    return 0;
}


