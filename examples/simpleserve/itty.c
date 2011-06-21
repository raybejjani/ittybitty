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

#include "http_dispatch.h"
#include "http_util.h"
#include "ittybitty.h"

// Constants
const char index_html[] = "\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\
<title>Ittybitty Welcome page</title>\
</head>\
<body>\
Welcome to Ittybitty!\
</body>\
\r\n\
";

const char foo_html[] = "\
<head>\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\" />\
<title>Ittybitty Welcome page</title>\
</head>\
<body>\
I pity the foo!\
</body>\
";


// http dispatch data
struct http_parser_data parser;

/*
 * data used by the itty server
 */
struct itty_data {
	http_dispatch_verb_t verb;
	char path[256];
	http_dispatch_http_version_t version;
} data;

// itty functions that have to be implemented
void itty_http_dispatch_accumReq(void* id, char c) {
	struct http_parser_test_data* data = (struct http_parser_test_data*)id;
	printf("%c", c);
}

void itty_http_dispatch_setVerb(void* id, http_dispatch_verb_t verb) {
	struct itty_data* data = (struct itty_data*)id;
	data->verb = verb;
}

void itty_http_dispatch_accumPath(void* id, char c) {
	struct itty_data* data = (struct itty_data*)id;
	data->path[strlen(data->path)] = c;
}

void itty_http_dispatch_setHttpVersion(void* id, http_dispatch_http_version_t version) {
	struct itty_data* data = (struct itty_data*)id;
	data->version = version;
}

itty_status_t itty_handle(int sockfd) {
	int rv;

	// setup parser and data
	memset(&data, 0, sizeof(data));	
	itty_http_dispatch_init(&parser);

	// read request, break out on errors and a successful request read.
	do {
		char request_data[128];
		memset(request_data, 0, sizeof(request_data));

		errno = 0;
		rv = recv(sockfd, request_data, sizeof(request_data), 0);

		if(rv == 0 ) { printf("conn closed"); break; }
		else if(rv < 0 && errno == EAGAIN) { continue; }
		else if(rv < 0 && errno != EWOULDBLOCK) { perror("recv"); break; }
		else {
			printf("executing on (%d:%d) %s\r\n", rv, errno, request_data);
			itty_http_dispatch_execute(&parser, &data, request_data, rv);
		}
	} while(itty_http_dispatch_finish(&parser) == 0);

	// ensure a newline after any possible printing related to parsing
	printf("\r\n");

	// check if we had a parsing error
	if(itty_http_dispatch_finish(&parser) == -1) {
		rv = itty_http_400(sockfd);
		printf("HTTP 400 Bad Request\r\n");
		if(rv == -1) { perror("itty_http_400"); }
	} else {
		printf("Returning %s\r\n", data.path);
		rv = itty_http_200(sockfd, index_html, sizeof(index_html)-1);
		if(rv == -1) { perror("itty_http_200"); }
	}

	return ITTY_STATUS_OK;
}

