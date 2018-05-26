#include "UDPServer.h"
#include "Serializable.h"

UDPServer::UDPServer(const char * serv, const char * port)
    :socket(serv, port)
{
    pthread_mutex_init(&mutex, 0);
};

UDPServer::~UDPServer()
{
    pthread_mutex_destroy(&mutex);
};

// ----------------------------------------------------------------------------

extern "C" void * _server_thread(void *arg)
{
    UDPServer * server = static_cast<UDPServer *>(arg);

    server->server_thread();

    return 0;
}

// ----------------------------------------------------------------------------

int UDPServer::start()
{
	
    for( int i = 0; i <= THREAD_POOL_SIZE; i++) {
        pthread_t tid;
        pthread_attr_t attr;

        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

        int error = pthread_create(&tid, &attr, _server_thread, static_cast<void*>(this));
        if(error) std::cout << "error creando thread";
    }
    return 0;
}

// ----------------------------------------------------------------------------

void UDPServer::server_thread()
{
	  while(true) {
            char* buffer;
			struct sockaddr cliente;
			socklen_t cliente_len = sizeof(cliente);

			Socket* nSocket;

			socket.recv(buffer,&nSocket);

			add_connection(nSocket);

			do_message(buffer);
     }


}

// ----------------------------------------------------------------------------

void UDPServer::add_connection (Socket * s)
{
	pthread_mutex_lock(&mutex);
	bool encontrado = false;
	std::vector<Socket*>::iterator it = connections.begin();
	
	while (!encontrado && it != connections.end()){
		if(*it == s) encontrado = true;
		else it++;
	}
	
	if(!encontrado) connections.push_back(s);
	else connections.erase(it);
	
	pthread_mutex_unlock(&mutex);
}

// ----------------------------------------------------------------------------

void UDPServer::del_connection (Socket * s)
{
	pthread_mutex_lock(&mutex);
	bool encontrado= false;
		std::vector<Socket*>::iterator it = connections.begin();
	
	while (!encontrado && it != connections.end()){
		if(*it == s) {
			connections.erase (it);
			encontrado = true;
		}else it++;
	}
	if(!encontrado) delete s;
	
	pthread_mutex_unlock(&mutex);
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

