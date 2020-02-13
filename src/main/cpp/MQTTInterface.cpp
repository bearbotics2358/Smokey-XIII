
#include <MQTTInterface.h>
#include <cstdio>
#include <cstring>

#include <signal.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h> // strerror()
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h> // random(), exit
#include <errno.h>
#include <Prefs.h>

#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h> // inet_ntoa
#include <arpa/inet.h> // inet_ntoa
#include <fcntl.h> // fcntl
#include <limits.h> // INT_MAX

/* mqtt_bridge - bridge between a TCP hub server and an MQTT broker

	 Messages in on the TCP connection are published to the MQTT broker
	 Messages from the MQTT broker are sent out on the TCP connection(s)

	 TCP Protocol
	 <topic>,<message>

	 For now, it only subscribes to Vision topic PI/CV/SHOOT/DAT

	 The TCP server receives connections from clients.  The connections to the
	 clients are kept open (up to a max MAX_BROWSER connections).
	 
	 A new connection received when there are already MAX_BROWSER
	 connections open will cause the oldest connection to be closed.
	 
	 This process defaults to port 9122.  If a port is provided on
	 the command line, this port will be used for all connections.
	 
*/



double MQTTInterface::gettime_d(){
	// return time in seconds as a double
	double t0;
	struct timeval tv0;

	gettimeofday(&tv0, NULL);
	t0 = 1.0 * tv0.tv_sec + (1.0 * tv0.tv_usec) / 1000000.0;
	// printf("seconds: %ld\n", tv0.tv_sec);
	// printf("usecs:   %ld\n", tv0.tv_usec);
	// printf("time:    %lf\n", t0);

	return t0;
}

int MQTTInterface::GetString()
{
	// returns true for a good character read, otherwise return false
	// Really dumb, look at calling loop for full functionality
	int numread;
	char c;
	int fGood = false;

	if(sock.status == SOCK_OPEN) {
		// printf("waiting to read ...");
		numread = read(sock.sock, &c, 1);
		// printf("(%2.2X) %c\n", c, c);


		if(numread < 0) {
			printf("error reading from input socket: %d\n", numread);
		} else {
			// Ok, read a character
			if((c == CR) || (c == LF)) {
				fGood = true;
			} else {
				// Good character
				rxbuf[rxbuf_index] = c;
				rxbuf_index++;
				// Need to ensure buffer does not overflow (which shouldnt happen anyway, but oh well)
				if(rxbuf_index >= RXBUF_MAX) {
					rxbuf_index = RXBUF_MAX - 1;
				}
			}
		}
	}
	
	return fGood;
}

void MQTTInterface::PutString(char *s)
{
	int i;
	char sout[MAXLEN + 2];
	int ret;

	// printf("Send string to [%d:%d]: *%s*\n", i, sock, s);

	// append a CRLF
	strcpy(sout, s);
	i = strlen(s);
	sout[i] = CR;
	sout[i + 1] = LF;
	sout[i + 2] = 0;

	// Now send to mqtt bridge
	if(sock.status == SOCK_OPEN) {
		ret = write(sock.sock, sout, strlen(sout));
		if(ret < 0) {
			printf("error(%d) writing to socket: %s\n", ret, strerror(errno));
		}
	}
}


void MQTTInterface::SignalHandler(int signum)
{
	printf("Caught signal %d\n", signum);
	fflush(stdout);
}

// Build string based on MQTT message and send to TCP client
void MQTTInterface::bot2tcp(char *topic, char *msg)
{
	char s1[255];

	sprintf(s1, "%s,%s", topic, msg);
	
	printf("Sending '%s' to TCP client\n", s1);
	PutString(s1);
}

// Parse string into topic and msg and sent to mqtt broker
void MQTTInterface::tcpReceived(char * smsg)
{
	char topic[255];
	char msg[255];
	char *p1;

	// parse smsg, breaking into topic and msg at the ","
	p1 = strtok(smsg, ",");
	strcpy(topic, p1);
	p1 = strtok(NULL, ",");
	strcpy(msg, p1);
	printf("From mqtt bridge: topic: %s  msg: %s\n", topic, msg);
	
	VisionMessageFilter(topic, msg);
}

void MQTTInterface::VisionMessageFilter(char* topic, char* msg) 
{
	char buf[255];

	if(!strcmp(topic, "PI/CV/SHOOT/DATA")){
		memset(buf, 0, 255*sizeof(char));
		/* Copy N-1 bytes to ensure always 0 terminated. */
		memcpy(buf, msg, 254*sizeof(char));
		float distance = 0;
		float angle = 0;
		sscanf(buf, "%f %f", &distance, &angle);
		targetDistance = distance;
		targetAngle = angle;
		printf("vision data is %f in and %f degrees\n", distance, angle);
	}
}

void MQTTInterface::cleanup(void)
{	
	closesock(sock);
}

void MQTTInterface::ClawVision()
{
	bot2tcp("/camera/controls/claw/", "vision");
}
void MQTTInterface::ClawViewing()
{ 
	bot2tcp("/camera/controls/claw/", "view");
}
void MQTTInterface::ClawOff()
{
	bot2tcp("/camera/controls/claw/", "off");
}
void MQTTInterface::CargoVision()
{
	bot2tcp("/camera/controls/cargo/", "vision");
}
void MQTTInterface::CargoViewing()
{
	bot2tcp("/camera/controls/cargo/", "view");
}
void MQTTInterface::CargoOff() 
{
	bot2tcp("/camera/controls/cargo/", "off");
}


MQTTInterface::MQTTInterface(const char *host, int port)
{
	Init();	
}


MQTTInterface::~MQTTInterface()
{
	cleanup();
}

void MQTTInterface::Init()
{
	clientport = DEFAULT_PORT;
	char stemp[256];

	// Clear out buffers
	rxbuf_index = 0;
	for(int i = 0; i < RXBUF_MAX; i++) {
		rxbuf[i] = 0;
	}

	/* 
	// We pray we never need this
	// atexit(cleanup);

	// signal(SIGINT, handle_signal);
	// signal(SIGTERM, handle_signal);

	if(signal(SIGPIPE, &SignalHandler) == SIG_ERR) {
		printf("Couldn't register signal handler for SIGPIPE\n");
	}

	if(signal(SIGHUP, &SignalHandler) == SIG_ERR) {
		printf("Couldn't register signal handler for SIGHUP\n");
	}

	*/

	t0 = tnow = gettime_d();
	
	// initialize socket so that cleanup() can determine if they are assigned
	initsock(sock);

	// Initialize TCP connection
	sprintf(stemp, "%d", clientport);

	connectTCPnew(sock, bridge_host, stemp);
}

void MQTTInterface::Update()
{
	
	int i;
	char stemp[256];
	int ret;
	struct timeval timeout;
	int so_error;
	socklen_t len;
	long arg;
	
	fd_set orig_fdset, fdset;
	int nfds = getdtablesize(); // number of file descriptors

	tnow = gettime_d();

	if(sock.status == SOCK_CLOSED) {
		// try to open a connection
		
		// make sure this doesn't run too often
		if(tnow < t0 + 0.5) {
			return;
		}
		t0 = tnow;
		
		// Initialize TCP connection
		sprintf(stemp, "%d", clientport);

		connectTCPnew(sock, bridge_host, stemp);
	}

	if(sock.status == SOCK_CONNECTING) {
		// see if connection is complete

		// make sure this doesn't run too often
		if(tnow < t0 + 0.5) {
			return;
		}
		t0 = tnow;

		printf("socket connecting\n");
		
		FD_ZERO(&fdset);
		FD_SET(sock.sock, &fdset);

		timeout.tv_sec = 0;
		timeout.tv_usec = 100;

		// use select on writeable to see if connection is complete
		ret = select(nfds, NULL, &fdset, NULL, &timeout); 
		if(ret == 0) {
			// timeout - try again next time
			return;
		}
		
		if(ret > 0) { 
			// Socket selected for write
			len = sizeof(so_error);
			ret = getsockopt(sock.sock, SOL_SOCKET, SO_ERROR, &so_error, &len); 
			if(ret < 0) { 
				fprintf(stderr, "Error in getsockopt() %d - %s\n", errno, strerror(errno)); 
				// close the socket and start over
				closesock(sock);
				return;
			}

			// Check the value returned... 
			if(so_error == 0) { 
				// no errors, can continue with socket

				// Set to blocking mode again...
				ret = (arg = fcntl(sock.sock, F_GETFL, NULL));
				if(ret < 0) { 
					fprintf(stderr, "Error fcntl(..., F_GETFL) (%s)\n", strerror(errno)); 
					// close the socket and start over
					closesock(sock);
					return;
				}
				arg &= (~O_NONBLOCK); 
				if( fcntl(sock.sock, F_SETFL, arg) < 0) { 
					fprintf(stderr, "Error fcntl(..., F_SETFL) (%s)\n", strerror(errno)); 
					// close the socket and start over
					closesock(sock);
					return;
				}
				sock.status = SOCK_OPEN;
				
			} else {
				fprintf(stderr, "Socket error in delayed connection() %d - %s\n", so_error, strerror(so_error)); 
				// close the socket and start over
				closesock(sock);
				return;
			}
		} else {
			// error
			printf("connecting select returned an error %s\n", strerror(errno));
			return;
		}
	}

	if(sock.status == SOCK_OPEN) {
		FD_ZERO(&orig_fdset);
		FD_SET(sock.sock, &orig_fdset);
		ret = 0;
		// read all available characters
		while(1) {
			/* Restore watch set as appropriate. */
			bcopy(&orig_fdset, &fdset, sizeof(orig_fdset));

			// need to sleep sometime, so just set timeout to 100 usec
			timeout.tv_sec = 0;
			timeout.tv_usec = 100;
			ret = select(nfds, &fdset, NULL, NULL, &timeout);
			/*  0 - timeout
					>0 - number of file descriptors that are ready
					-1 - error
			*/
			if(ret == 0) {
				// timeout
				break;
			}

			// debug
			if(ret != 0) {
				// printf("select returned %d\n", ret);
			}
		
			if(ret > 0) {
				// process input from TCP connection
				if((sock.status == SOCK_OPEN) && FD_ISSET(sock.sock, &fdset)) {
					// printf("Client has data - fd: %d\n", sock.sock);
					ret = GetString();
					// Did we find a full message?
					if(ret && (rxbuf_index > 0)) {
						// Parse and interpret message from MQTT Bridge
						tcpReceived(rxbuf);
						// Finished message, reset buffer for next message
						rxbuf_index = 0;
					} 
				}
			} else {
				// error
				printf("select returned an error %s\n", strerror(errno));
				break;
			}
		}
	}
	
} 

float MQTTInterface::GetDistance()
{
	return targetDistance;
}

float MQTTInterface::GetAngle()
{
	return targetAngle;
}





