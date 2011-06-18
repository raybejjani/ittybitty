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


#include "ittybitty.h"

const char http_header_default[] = "\
HTTP/1.0 200 OK\r\n\
Content-Type: text/html\r\n\
Content-Length: 241\r\n\
\r\n\
";

const char html_default[] = "\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\
<title>Ittybitty Welcome page</title>\
</head>\
<body>\
Welcome to Ittybitty!\
</body>\
";

itty_status_t itty_handle(int sockfd) {
	int rv;
	char request[1024];
	// read request
	for(int i = 0; i < sizeof(request); ) {
		printf("%s", request);
		rv = recv(sockfd, &request[i], sizeof(request)-i, 0);
		if(rv == 0 ) { break; }
		else if(rv < 0 && errno != EWOULDBLOCK) { perror("recv"); break; }
		else { i += rv; }
	}
	
	// write out response
	rv = send(sockfd, http_header_default, strlen(html_default), 0);
	if(rv == -1) { perror("send"); }
	rv = send(sockfd, html_default, strlen(html_default), 0);
	if(rv == -1) { perror("send"); }

	return itty_status_ok;
}

