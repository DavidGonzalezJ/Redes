#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
int main(int argc, char** argv) {
	struct addrinfo *res;
	struct addrinfo *hints;
	memset((void *) &hints, "\0/", sizeof(struct addreinfo));
	
	hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
	hints.ai_family   = AF_INET; // IPv4
	hints.ai_socktype = SOCK_DGRAM;

	rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if(rc!=0){
			std::cout << "Error getaddrinfo():" << gai_strerror(rc) << std::endl;
			return -1;
	}
	for(struct addrinfo *tmp = res; tmp!=tmp->ai_next){
			char host[NI_MAXHOST];
			char serv[NI_MAXSERV];
			getnameinfo(tmp->ai_addr, tmp->ai_addrlen, host, NI_MAXHOST,
				serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
			std::cout << "Host: " << host << "\n Serv: " << serv << "\n";
	}
	free(res);
	free(hints); 
/*
	
	sd = socket(result->ai_family, result->ai_socktype, 0);

	bind(sd, (struct sockaddr *) result->ai_addr, result->ai_addrlen);

	while (1) {
	  bytes = recvfrom(sd, buffer, 80, 0, (struct sockaddr *) &cliente,
		  &cliente_len);
	  buffer[bytes]='\0'; 
		
	  getnameinfo((struct sockaddr *) &cliente, cliente_len, host, NI_MAXHOST,
		  serv, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

	  printf("Conexión desde Host:%s Puerto:%s\n",host, serv);
	  printf("\tMensaje(%i): %s\n", bytes, buffer);

	  sendto(sd, buffer, bytes, 0, (struct sockaddr *) &cliente, cliente_len);
	}
*/
    return 1;
}
