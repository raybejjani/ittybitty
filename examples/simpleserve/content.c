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

#include "content.h"


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

const itty_content_t files[] = {
	{.length = sizeof(index_html)-1, .data = index_html},
	{.length = sizeof(foo_html)-1, .data = foo_html},
};

#define MATCH_PATH(path, content_path) \
	(memcmp(path, content_path, sizeof(content_path)-1) == 0)

const itty_content_t* itty_content_get(http_dispatch_verb_t verb, const char* path, int path_length) {
	// TODO: This is bad, overflows will abound.
	if(MATCH_PATH(path, "/foo.html")) { return &files[1]; }
	if(MATCH_PATH(path, "/index.html")) { return &files[0]; }
	if(MATCH_PATH(path, "/")) { return &files[0]; }
	if(MATCH_PATH(path, "")) { return &files[0]; }
	return NULL;
}

