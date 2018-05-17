#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <unistd.h>

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
	char buffer[256];
	
	hints.ai_family   = AF_INET; // IPv4
	hints.ai_socktype = SOCK_STREAM;

	int rc = getaddrinfo(argv[1], argv[2], &hints, &result);
	
	if(rc!=0){
		std::cout << "Error getaddrinfo():" << gai_strerror(rc) << std::endl;
		return -1;
	}

	int sd = socket(result->ai_family, result->ai_socktype, 0);
	int cn = connect(sd, result->ai_addr,result->ai_addrlen);
	 

    	memset((void*) buffer,'\0', 256);

	while(!exit){
		std::cin.getline(buffer,256);
		if(strcmp(buffer, "q") == 0){
			close(sd);
			exit=true;		
		}
		if(!exit){
			size_t bytesSent = send(sd, buffer, 255, 0);
			size_t bytes = recv(sd, buffer, bytesSent, 0);
			std::cout<< buffer << "\n";
		}
	}
	freeaddrinfo(result);



    return 0;
}
