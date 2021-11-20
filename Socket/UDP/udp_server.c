/* Server side implementation of UDP client-server model
 *
 * UDP Server :
 * 1) Create a UDP socket.
 * 2) Bind the socket to the server address.
 * 3) Wait until the datagram packet arrives from the client.
 * 4) Process the datagram packet and send a reply to the client.
 * 5) Go back to Step 3.
 *
 *
 * Necessary Functions :  
 * ------------------------------------------------------------------------------------------------------
 * int socket(int domain, int type, int protocol)
 * 
 * Creates an unbound socket in the specified domain. Returns socket file descriptor.
 * Arguments : 
 *    domain   – Specifies the communication  - domain ( AF_INET for IPv4/ AF_INET6 for IPv6 ) 
 *    type     – Type of socket to be created ( SOCK_STREAM for TCP / SOCK_DGRAM for UDP ) 
 *    protocol – Protocol to be used by the socket. 0 means use default protocol for the address family.  
 * ------------------------------------------------------------------------------------------------------
 * int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
 *
 * Assigns address to the unbound socket.
 * Arguments : 
 *    sockfd  – File descriptor of a socket to be bonded 
 *    addr    – Structure in which address to be bound to is specified 
 *    addrlen – Size of addr structure  
 * ------------------------------------------------------------------------------------------------------
 * ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
 *
 * Send a message on the socket
 * Arguments : 
 *     sockfd    – File descriptor of the socket 
 *     buf       – Application buffer containing the data to be sent 
 *     len       – Size of buf application buffer 
 *     flags     – Bitwise OR of flags to modify socket behavior 
 *     dest_addr – Structure containing the address of the destination 
 *     addrlen   – Size of dest_addr structure  
 * ------------------------------------------------------------------------------------------------------ 
 * ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
 * Receive a message from the socket.
 * Arguments : 
 *     sockfd   – File descriptor of the socket 
 *     buf      – Application buffer in which to receive data 
 *     len      – Size of buf application buffer 
 *     flags    – Bitwise OR of flags to modify socket behavior 
 *     src_addr – Structure containing source address is returned 
 *     addrlen  – Variable in which size of src_addr structure is returned 
 * ------------------------------------------------------------------------------------------------------
 * int close(int fd)
 * Close a file descriptor
 * Arguments:
 * fd – File descriptor
 * 
 * In the below code, the exchange of one hello message between server and client is shown to demonstrate the model. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT     8080
#define MAXLINE 1024

int main(void)
{
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));

	// Filling server information
	servaddr.sin_family      = AF_INET;     // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;  // inet_addr("127.0.0.1");
	servaddr.sin_port        = htons(PORT);

	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int len, n;

	len = sizeof(cliaddr);  //len is value/resuslt

	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len);
	buffer[n] = '\0';
	printf("Client : %s\n", buffer);
	
	sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	printf("Hello message sent.\n"); 

	return 0;
}
