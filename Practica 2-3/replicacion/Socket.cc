#include "Socket.h"
#include "Serializable.h"

#include <string.h>

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// Implementación Socket
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

bool operator== (const Socket &s1, const Socket &s2)
{
	struct sockaddr_in *s1_in = (struct sockaddr_in*)s1.sa;
	struct sockaddr_in *s2_in = (struct sockaddr_in*)s2.sa;
	
	return s1_in.sin_family == s2_in.sin_family && s1_in.sin_addr.s_addr == s2_in.sin_addr.s_addr && s1_in.sin_port == s2_in.sin_port;
}

std::ostream& operator<<(std::ostream& os, const Socket& s)
{
    char host[NI_MAXHOST];
    char serv[NI_MAXSERV];

    getnameinfo((struct sockaddr *) &(s.sa), s.sa_len, host, NI_MAXHOST, serv,
                NI_MAXSERV, NI_NUMERICHOST);

    os << host << ":" << serv;
}

// ----------------------------------------------------------------------------
    /**
     *  Construye el socket UDP con la dirección y puerto dados. Esta función
     *  usara getaddrinfo para obtener la representación binaria de dirección y
     *  puerto.
     *
     *  Además abrirá el canal de comunicación con la llamada socket(2).
     *
     *    @param address cadena que representa la dirección o nombre
     *    @param port cadena que representa el puerto o nombre del servicio
     *
     *  En caso de error lanzar una excepcion std::runtime_error
     */
Socket::Socket(const char * address, const char * port):sd(-1)
{
    struct addrinfo *result;
    struct addrinfo hints;
    memset((void *) &hints, '\0', sizeof(struct addrinfo));

    //UDP
    hints.ai_flags    = AI_PASSIVE; //Devolver 0.0.0.0
    hints.ai_family   = AF_INET; // IPv4
    hints.ai_socktype = SOCK_DGRAM;

    int rc = getaddrinfo(address, port, &hints, &result);
    if(rc!=0) {
        std::cout << "Error getaddrinfo():" << gai_strerror(rc) << std::endl;
        //ERROR
    }

    sd = socket(result->ai_family, result->ai_socktype, 0);
    if(sd == -1) //ERROR

}

// ----------------------------------------------------------------------------

int Socket::bind()
{
    return ::bind(sd, (const struct sockaddr *) &sa, sa_len);
}

// ----------------------------------------------------------------------------

int Socket::send(Serializable * obj, Socket * sock)
{
}

// ----------------------------------------------------------------------------

int Socket::recv(char * buffer, Socket ** sock)
{
}

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

