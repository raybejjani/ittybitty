/*
 * Lookup for content to be served.
 */

#ifndef __CONTENT_H__
#define __CONTENT_H__

#include "http_dispatch.h"

typedef struct itty_content {
	int length;
	const char* data; 
} itty_content_t;


const itty_content_t* itty_content_get(http_dispatch_verb_t verb, const char* path, int path_length);

#endif /* __CONTENT_H__ */

