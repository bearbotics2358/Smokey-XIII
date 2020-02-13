/* inetlib.h

	 Library of Internet (TCP/IP) C routines

	 created 8/6/01 Bob D'Avello
	 updated 2/24/09 - change errexit in inetlib.h to #define to get rid of 
	 variable argument compilation problems

*/

#ifndef _INETLIB_H
#define _INETLIB_H

// for connectsock:

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

// following lines not needed, in <netinet/in.h>
// #ifndef INADDR_NONE
// #define INADDR_NONE 0xffffffff
// #endif


#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif

	// previously declared, in <stdio.h>
	// extern char *sys_errlist[];

	// previously declared, in <netinet/in.h>
	// u_short htons();
	// u_long inet_addr();


	// for errexit:

	// #include <varargs.h>
	// #include <stdarg.h>
#include <stdio.h>

	enum e_sock_status {
		SOCK_CLOSED = 0,
		SOCK_CREATED = 1,
		SOCK_CONNECTING = 2,
		SOCK_OPEN = 3,
	} ;
	
	struct sock_info {
		int sock;
		struct sockaddr_in addr;
		enum e_sock_status status;
	} ;
	

	// for passivesock
	extern u_short portbase;  // port base, for non-root servers

	int connectsock (char *host, char *service, char *protocol);
	int connectTCP (char *host, char *service);
	int connectUDP (char *host, char *service);

	void initsock(sock_info &sock);
	void closesock(sock_info &sock);
	void createsocknew(sock_info &sock, char *host, char *service, char *protocol);
	void connectsocknew (sock_info &sock, char *host, char *service, char *protocol);
	void connectTCPnew (sock_info &sock, char *host, char *service);
	void connectUDPnew (sock_info &sock, char *host, char *service);
	
	int passivesock (char *service, char *protocol, int qlen);
	int passiveTCP (char *service, int qlen);
	int passiveUDP (char *service);

#ifdef __cplusplus
}
#endif

#endif _INETLIB_H
