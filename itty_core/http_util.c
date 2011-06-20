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
#include <sys/uio.h>

#include "http_util.h"

/*
 * TODO: Figure out a good way to use writev but refer to const data
 */

// Constants
const char http_header_400[] = "\
HTTP/1.0 400 Bad Request\r\n\
\r\n\
";

const char http_header_404[] = "\
HTTP/1.0 404 Not Found\r\n\
\r\n\
";

const char http_header_200[] = "\
HTTP/1.0 200 OK\r\n\
";

const char http_body_header_start[] = "\
Content-Type: text/html\r\n\
Content-Length: ";

const char http_header_end[] = "\
\r\n\
";


ssize_t itty_http_400(int sockfd) {
	const struct iovec parts[] = {
		{.iov_base = http_header_400, 	.iov_len = sizeof(http_header_400)-1},
		{.iov_base = http_header_end, 	.iov_len = sizeof(http_header_end)-1},
	};
	return writev(sockfd, parts, sizeof(parts)/sizeof(parts[0]));
}

ssize_t itty_http_404(int sockfd) {
	const struct iovec parts[] = {
		{.iov_base = http_header_404, 	.iov_len = sizeof(http_header_404)-1},
		{.iov_base = http_header_end, 	.iov_len = sizeof(http_header_end)-1},
	};
	return writev(sockfd, parts, sizeof(parts)/sizeof(parts[0]));
}

ssize_t itty_http_200(int sockfd, const char* data, int data_len) {
	char content_len_str[128];
	struct iovec parts[] = {
		{.iov_base = http_header_200, 	.iov_len = sizeof(http_header_200)-1},
		{.iov_base = http_body_header_start, 
																		.iov_len = sizeof(http_body_header_start)-1},
		{.iov_base = content_len_str, 	.iov_len = 0},
		{.iov_base = http_header_end, 	.iov_len = sizeof(http_header_end)-1},
		{.iov_base = data, 							.iov_len = data_len},
	};

	snprintf(content_len_str, sizeof(content_len_str), "%d\r\n", data_len);
	parts[2].iov_len = strlen(content_len_str);

	return writev(sockfd, parts, sizeof(parts)/sizeof(parts[0]));
}

