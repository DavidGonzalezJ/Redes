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
//ps -aT     	para ver los threads
//nc -u localhost 8080 			conectarnos al host con udp
class ServerThread {
public:
    ServerThread(int s):sd(s) {};
    virtual ~ServerThread() {};
    void do_message() {
	bool exit= false;
        while(!exit) {
            char buffer[256];
            struct sockaddr src_addr;
            socklen_t addrlen = sizeof(src_addr);
            char host[NI_MAXHOST];
            char serv[NI_MAXSERV];

            size_t bytes = recvfrom(sd, buffer, 80, 0, &src_addr, &addrlen);
            buffer[bytes]='\0';

            if(bytes !=0) {
                getnameinfo(&src_addr, addrlen, host, NI_MAXHOST,
                            serv, NI_MAXSERV, NI_NUMERICHOST);

                std::cout<< bytes << " bytes de " << host << " " << serv << "\n";
            }


            int aux;

            struct tm* ctime;
            time_t tiempo;
            time (&tiempo);
            ctime = localtime(&tiempo);

            switch(buffer[0]) {
            case 't':
                aux = strftime(buffer, 256 ,"%H:%M:%S", ctime);
                sendto(sd, buffer, aux, 0, (struct sockaddr *) &src_addr, addrlen);
                break;
            case 'd':

                aux = strftime(buffer, 256 ,"%Y-%m-%d", ctime);
                sendto(sd, buffer, aux, 0, (struct sockaddr *) &src_addr, addrlen);
                break;
            case 'q':
                exit = true;
                std::cout << "Saliendo...\n";
                break;
            default:
                std::cout << "Comando no soportado " << buffer[0]<< "\n";
                break;
            }
            sleep(10);
        }
    }
private:
    int sd;
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
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(argv[1],argv[2], &hints, &res);

    if (rc !=0 ) {
        std::cout <<"error getaddrinfo(): " << gai_strerror(rc)<< std::endl;
        return -1;
    }

    int sd = socket (res->ai_family, res->ai_socktype,0);

    bind ( sd, res->ai_addr, res->ai_addrlen);
    listen(sd,15);
    freeaddrinfo(res);

    //Inizializar pool de threads

    for( int i = 0; i <= NUM_THREADS; i++) {
        pthread_t tid;
        pthread_attr_t attr;

        ServerThread* st = new ServerThread(sd);

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        pthread_create(&tid, &attr, start_routine, static_cast<void*>(st));
    }
    // Thread Ppal
    char c;
    std::cin >> c;

    return 0;

}
