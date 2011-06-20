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
	char request[128];
	
	memset(&data, 0, sizeof(data));	
	http_parse_init(&parser);

	// read request
	for(int i = 0; i < sizeof(request); ) {
		printf("%s", request);
		rv = recv(sockfd, &request[i], sizeof(request)-i, 0);
		if(rv == 0 ) { break; }
		else if(rv < 0 && errno != EWOULDBLOCK) { perror("recv"); break; }
		else { i += rv; }
	}

	printf("%s\r\n", data.path);

	rv = itty_http_200(sockfd, index_html, sizeof(index_html)-1);
	if(rv == -1) { perror("itty_http_200"); }

	return itty_status_ok;
}

