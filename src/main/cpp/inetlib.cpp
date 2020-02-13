/* inetlib.c

	 Library of Internet (TCP/IP) C routines

	 created 8/6/01 Bob D'Avello
	 updated 2/24/09 - change errexit in inetlib.h to #define to get rid of 
	 variable argument compilation problems

*/


#include "inetlib.h"
#include <string.h>
#include <stdlib.h>

extern "C" {


	u_short portbase = 0;  // port base, for non-root servers

	/*----------------------------------------------------------------------------
	 * errexit - print an error message and exit
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */
	/*VARARGS1*/
	/*
		int errexit(format, va_alist)
		char *format;
		va_dcl
		{
		va_list args;
		va_start(args);
		// _doprnt(format, args, stderr);
		printf(format, va_alist);
		va_end(args);
		exit(1);
		}
	*/
#define errexit(format, args...) printf(format, args)

	/*----------------------------------------------------------------------------
	 * connectsock - allocate & connect a socket using TCP or UDP
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */

	int connectsock (char *host, char *service, char *protocol)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 * *protocol - name of protocol to use ("tcp" or "udp")
		 */

		struct hostent *phe; // pointer to host information entry
		struct servent *pse; // pointer to service information entry
		struct protoent *ppe; // pointer to protocol information entry
		struct sockaddr_in sin; // an Internet endpoint address
		int s, type;  // socket descriptor and socket type

		bzero((char *)&sin, sizeof(sin));
		sin.sin_family = AF_INET;

		// Map service name to port number
		if((pse = getservbyname(service, protocol)))
			sin.sin_port = pse->s_port;
		else if((sin.sin_port = htons((u_short)atoi(service))) == 0)
			errexit("can't get \"%s\" service entry\n", service);

		// Map host name to IP address, allowing for dotted decimal
		if((phe = gethostbyname(host)))
			bcopy(phe->h_addr, (char *)&sin.sin_addr, phe->h_length);
		else if((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
			errexit("can't get \"%s\" host entry\n", host);

		// Map protocol name to protocol number
		if((ppe = getprotobyname(protocol)) == 0)
			errexit("can't get \"%s\" protocol entry\n", protocol);

		// Use protocol to choose a socket type
		if(strcmp(protocol, "udp") == 0)
			type = SOCK_DGRAM;
		else
			type = SOCK_STREAM;

		// Allocate a socket
		s = socket(PF_INET, type, ppe->p_proto);
		if(s < 0)
			{
				printf("can't create socket: %s\n", strerror(errno));
				close(s);
				s = 0;
			}

		// Connect the socket
		if(connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
			printf("can't connect to %s.%s: %s\n", host, service, strerror(errno));
			close(s);
			s = 0;
		}
		
		return s;
	}





	/*----------------------------------------------------------------------------
	 * connectTCP - connect to a specified TCP service on a specified host
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */

	int connectTCP (char *host, char *service)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 */

		return connectsock(host, service, "tcp");
	}


	/*----------------------------------------------------------------------------
	 * connectUDP - connect to a specified UDP service on a specified host
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */

	int connectUDP (char *host, char *service)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 */

		return connectsock(host, service, "udp");
	}



	/*----------------------------------------------------------------------------
	 * initsock - initialize socket sockinfo structure
	 *----------------------------------------------------------------------------
	 */

	void initsock(sock_info &sock)
	{
		sock.status = SOCK_CLOSED;
		sock.sock = 0;
	}

	/*----------------------------------------------------------------------------
	 * closesock - close socket using sockinfo type
	 *----------------------------------------------------------------------------
	 */

	void closesock(sock_info &sock)
	{
		if(sock.status != SOCK_CLOSED) {
			sock.status = SOCK_CLOSED;
			close(sock.sock);
			sock.sock = 0;
		}
	}

	/*----------------------------------------------------------------------------
	 * connectsocknew - allocate a socket using TCP or UDP
	 * derived from Internetowrking with TCP/IP Volume III
	 * with addition of using a sock_info structure
	 *----------------------------------------------------------------------------
	 */

	void createsocknew(sock_info &sock, char *host, char *service, char *protocol)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 * *protocol - name of protocol to use ("tcp" or "udp")
		 */

		struct hostent *phe; // pointer to host information entry
		struct servent *pse; // pointer to service information entry
		struct protoent *ppe; // pointer to protocol information entry
		int type;  // socket type

		bzero((char *)&sock.addr, sizeof(sock.addr));
		sock.addr.sin_family = AF_INET;

		// Map service name to port number
		if((pse = getservbyname(service, protocol))) {
			sock.addr.sin_port = pse->s_port;
		} else if((sock.addr.sin_port = htons((u_short)atoi(service))) == 0) {
			errexit("can't get \"%s\" service entry\n", service);
		}
		
		// Map host name to IP address, allowing for dotted decimal
		if((phe = gethostbyname(host))) {
			bcopy(phe->h_addr, (char *)&sock.addr.sin_addr, phe->h_length);
		} else if((sock.addr.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE) {
			errexit("can't get \"%s\" host entry\n", host);
		}
		
		// Map protocol name to protocol number
		if((ppe = getprotobyname(protocol)) == 0) {
			errexit("can't get \"%s\" protocol entry\n", protocol);
		}
		
		// Use protocol to choose a socket type
		if(strcmp(protocol, "udp") == 0) {
			type = SOCK_DGRAM;
		} else {
			type = SOCK_STREAM;
		}

		// Allocate a socket and set non-blocking
		sock.sock = socket(PF_INET, type | SOCK_NONBLOCK, ppe->p_proto);
		if(sock.sock < 0)	{
			printf("can't create socket: %s\n", strerror(errno));
			closesock(sock);
		}

	}
	

	/*----------------------------------------------------------------------------
	 * connectsocknew - allocate & connect a socket using TCP or UDP
	 * from Internetowrking with TCP/IP Volume III
	 * with addition of using a sock_info structure
	 *----------------------------------------------------------------------------
	 */

	void connectsocknew (sock_info &sock, char *host, char *service, char *protocol)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 * *protocol - name of protocol to use ("tcp" or "udp")
		 */

		long arg;
		
		createsocknew(sock, host, service, protocol);
		
		// Connect the socket
		if(connect(sock.sock, (struct sockaddr *)&sock.addr, sizeof(sock.addr)) == 0) {
			sock.status = SOCK_OPEN;
			// Set to blocking mode ... 
			arg = fcntl(sock.sock, F_GETFL, NULL); 
			arg &= (~O_NONBLOCK); 
			fcntl(sock.sock, F_SETFL, arg); 
		} else {
			printf("can't connect to %s.%s: (%d) %s\n", host, service, errno, strerror(errno));
			if(errno == EINPROGRESS) {
				printf("setting socket status to SOCK_CONNECTING\n");
				sock.status = SOCK_CONNECTING;
			} else {
				closesock(sock);
			}
		}
		
		return;
	}


	/*----------------------------------------------------------------------------
	 * connectTCPnew - connect to a specified TCP service on a specified host
	 * from Internetowrking with TCP/IP Volume III
	 * with addition of using a sock_info structure
	 *----------------------------------------------------------------------------
	 */

	void connectTCPnew (sock_info &sock, char *host, char *service)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 */

		connectsocknew(sock, host, service, "tcp");
		return;
	}


	/*----------------------------------------------------------------------------
	 * connectUDPnew - connect to a specified UDP service on a specified host
	 * from Internetowrking with TCP/IP Volume III
	 * with addition of using a sock_info structure
	 *----------------------------------------------------------------------------
	 */

	void connectUDPnew (sock_info &sock, char *host, char *service)
	{
		/* *host - name of host to which connection is desired
		 * *service - service associated with desired port
		 */

		connectsocknew(sock, host, service, "udp");
		return;
	}

	/*----------------------------------------------------------------------------
	 * passivesock - allocate & bind a server socket using TCP or UDP
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */

	int passivesock (char *service, char *protocol, int qlen)
	{
		/* *service - service associated with desired port
		 * *protocol - name of protocol to use ("tcp" or "udp")
		 * qlen - maximum server request queue length
		 */

		struct servent *pse; // pointer to service information entry
		struct protoent *ppe; // pointer to protocol information entry
		struct sockaddr_in sin; // an Internet endpoint address
		int s, type;  // socket descriptor and socket type

		bzero((char *)&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = INADDR_ANY;

		// Map service name to port number
		if((pse = getservbyname(service, protocol)))
			sin.sin_port = htons(ntohs((u_short)pse->s_port) + portbase);
		else if((sin.sin_port = htons((u_short)atoi(service))) == 0)
			errexit("can't get \"%s\" service entry\n", service);

		// Map protocol name to protocol number
		if(((ppe = getprotobyname(protocol))) == 0)
			errexit("can't get \"%s\" protocol entry\n", protocol);

		// Use protocol to choose a socket type
		if(strcmp(protocol, "udp") == 0)
			type = SOCK_DGRAM;
		else
			type = SOCK_STREAM;

		// Allocate a socket
		s = socket(PF_INET, type, ppe->p_proto);
		if(s < 0)
			errexit("can't create socket: %s\n", strerror(errno));

		// Bind the socket
		if(bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
			errexit("can't bind to %s port: %s\n", service, strerror(errno));
		if(type == SOCK_STREAM && listen(s, qlen) < 0)
			errexit("can't listen on %s port: %s\n", service, strerror(errno));
		return s;
	}





	/*----------------------------------------------------------------------------
	 * passiveTCP - create a passive socket for use in a UDP server
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */

	int passiveTCP (char *service, int qlen)
	{
		/* *service - service associated with desired port
		 * qlen - maximum server request queue length
		 */

		return passivesock(service, "tcp", qlen);
	}


	/*----------------------------------------------------------------------------
	 * passiveUDP - create a passive socket for use in a UDP server
	 * from Internetowrking with TCP/IP Volume III
	 *----------------------------------------------------------------------------
	 */

	int passiveUDP (char *service)
	{
		/* *service - service associated with desired port
		 */

		return passivesock(service, "udp", 0);
	}

}

