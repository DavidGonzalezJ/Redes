#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
 
#define NUM_THREADS 5
//g++ -o ejc fichero.cc  -lpthread
//ejc localhost 8080
//netstat -uan
//ps -aT para ver los threads
//nc -u localhost 8080 	conectarnos al host con udp
class ServerThread {
public:
    ServerThread(int s):sd(s), exit(false) {};
    virtual ~ServerThread() {};
    void do_message() {
        while(!exit) {
            char buf[256];
            //Receive
            ssize_t bytesRec =  recv(sd, &buf, 255, 0);
            if(bytesRec == 0) {
                exit = true;
                std::cout << "Conexión terminada";
            }
            else {
                send(sd, &buf, bytesRec, 0);
				std::cout << pthread_self() << std::endl;
			}
            
        }
    }
private:
    int sd;
    bool exit;
};
extern "C" void *start_routine (void * _st) {
    ServerThread * st = static_cast<ServerThread*>(_st);
    st->do_message	();
    delete st;
    return 0;

}
int main (int argc, char **argv)
{
    struct addrinfo hints;
    struct addrinfo* res;

    //Inicializar socket
    memset((void*) &hints, '\0', sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

    if (rc !=0 ) {
        std::cout <<"error getaddrinfo(): " << gai_strerror(rc)<< std::endl;
        return -1;
    }

    int sd = socket (res->ai_family, res->ai_socktype,0);

    int error = bind ( sd, res->ai_addr, res->ai_addrlen);
    if(error) std::cout << "Error bind";

    error = listen(sd,15);
    if(error) std::cout << "Error listen";

    freeaddrinfo(res);

    while(true) {
		struct sockaddr cliente;
		socklen_t cliente_len = sizeof(cliente);
        int socketThread = accept(sd,(struct sockaddr *) &cliente, &cliente_len);
		
		//Inizializar pool de threads
        pthread_t tid;
        pthread_attr_t attr;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	    ServerThread* st = new ServerThread(socketThread);

        int error = pthread_create(&tid, &attr, start_routine, static_cast<void*>(st));
		if(error) std::cout << "Error thread";
    }

    // Thread Ppal
    char c;
    std::cin >> c;

    return 0;

}
