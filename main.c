#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/select.h>

#include "ittybitty.h"

const char port_default_str[] = "3490";
const int backlog_default = 10;


void sigchld_handler(int s)
{
    while(waitpid(-1, NULL, WNOHANG) > 0);
}

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
    if(sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/*
 * setup_socket - convenience function that sets up a socket for receiving
 * TCP connections. Sets REUSEADDR, port, backlog.\
 *
 * port - listen port. must be between 1-65535.
 * backlog - number of pending TCP connections before they are rejected.
 *
 * returns socket fd on succes, -1 on fail. 
 */
int setup_socket(const char* const port, int backlog) {
    int sockfd; // socket to return, return variable
    int rv; // dummy to hold function returns for error-checking
		struct addrinfo hints, *servinfo, *p;
    int yes=1;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP

		rv = getaddrinfo(NULL, port, &hints, &servinfo);
    if( rv != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        sockfd = -1;
				goto setup_socket_cleanup;
    }
		
    		
		// loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) {
				rv = sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
        if(rv == -1) {
            perror("server: socket");
            continue;
        }
				
				fcntl(sockfd, F_SETFL, O_NONBLOCK);

				setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        if(rv == -1) {
            perror("setsockopt");
						sockfd = -1;
						goto setup_socket_cleanup;
        }

				rv = bind(sockfd, p->ai_addr, p->ai_addrlen);
        if(rv == -1) {
            perror("server: bind");
            continue;
        }

				// socket fully setup, break out.
        break;
    }

    if(p == NULL)  {
        fprintf(stderr, "server: failed to bind\n");
				sockfd = -1;
				goto setup_socket_cleanup;
    }


    if(listen(sockfd, backlog) == -1) {
        perror("listen");
				goto setup_socket_sockerror;
    }

		// All good, skip the sockerror case
		goto setup_socket_cleanup;

setup_socket_sockerror: // error after the socket was opened
	close(sockfd);
	sockfd = -1;

setup_socket_cleanup: // general cleanup
	freeaddrinfo(servinfo); // all done with this structure
	return sockfd;		
}


int main(void)
{
    int sockfd, new_fd;  // listen on sock_fd, new connection on new_fd
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;
    int yes=1;
    char s[INET6_ADDRSTRLEN];
    int rv;
		fd_set sock_select;


		sockfd = setup_socket(port_default_str, backlog_default);
		if(sockfd <= 0) { perror("setup_socket"); exit(1); }

		sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGCHLD, &sa, NULL) == -1) { perror("sigaction"); exit(1); }

    printf("server: waiting for connections...\n");

		// main accept() loop
		FD_ZERO(&sock_select);
		FD_SET(sockfd, &sock_select);
    while(select(sockfd+1, &sock_select, NULL, NULL, NULL) == 1) {
			FD_ZERO(&sock_select);
			FD_SET(sockfd, &sock_select);

			sin_size = sizeof their_addr;
			new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
			if(new_fd == -1) { perror("accept"); continue; }

			inet_ntop(their_addr.ss_family,
					get_in_addr((struct sockaddr *)&their_addr),
					s, sizeof s);
			printf("server: got connection from %s\n", s);

			rv = itty_handle(new_fd);
			if(rv == -1) { perror("itty_handle"); }

			close(new_fd);
    }

    close(sockfd);
		return 0;
}

