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

Socket::Socket(const char * address, const char * port):sd(-1)
{
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

