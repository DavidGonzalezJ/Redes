#include <string>
#include <unistd.h>
#include <string.h>
#include "Serializable.h"
#include "Socket.h"
#include "UDPServer.h"
//make all

class ChatMessage: public Serializable
{
public:
    ChatMessage(){};

    ChatMessage(const char * n, const std::string m)
    {
		strncpy(nick, n, 8);
		strncpy(message, m, 80);

    };

    void to_bin()
    {
		 //80 del nombre + 8 del nick
        int32_t total = 88 * sizeof(char);
        //Hace el malloc
        alloc_data(total);
        
        //Nos interesa saber donde empiezan las variables dentro del buffer
        char * tmp = _data + sizeof(int32_t); //Tmp apunta al nombre
        
        //Nombre
        memcpy(tmp, (void *)message,80 * sizeof(char));
        tmp += 8 * sizeof(char);
        //Mensaje
        memcpy(tmp, (void *)message,80 * sizeof(char));
        tmp += 80 * sizeof(char);
        
    }

    virtual int from_bin(char * bobj)
    {
		 char * tmp = bobj + sizeof(int32_t);
        //Nombre
        memcpy(message, tmp, 80);
        tmp += 8 * sizeof(char);
        
        memcpy(nick, tmp, 80);
        tmp += 80 * sizeof(char)

    }

    char message[80];

    char nick[8];
};

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

class ChatServer : public UDPServer
{
public:
    ChatServer(const char * s, const char * p): UDPServer(s, p){};

    void do_message(char * buffer)
    {

    }
};

class ChatClient
{
public:
    ChatClient(const char * s, const char * p, const char * n):socket(s, p),
        nick(n){};

    void input_thread()
    {
    }

    void net_thread()
    {
    }

private:
    char nick[8];

    Socket socket;
};

