/*
 * HTTP Dispatcher public API
 */

#ifndef __HTTP_DISPATCH_H__
#define __HTTP_DISPATCH_H__

typedef enum {
	HTTP_DISPATCH_HTTP_VERSION_1_0,
	HTTP_DISPATCH_HTTP_VERSION_1_1,
} http_dispatch_http_version_t;

typedef enum {
	HTTP_DISPATCH_VERB_GET,
} http_dispatch_verb_t;

struct http_parser_data
{
	int cs; // parser state
};

// Dispatch callbacks, provided to dispatch
void itty_http_dispatch_accumReq(void* id, char c);
void itty_http_dispatch_setVerb(void* id, http_dispatch_verb_t verb);
void itty_http_dispatch_accumPath(void* id, char c);
void itty_http_dispatch_setHttpVersion(void* id, http_dispatch_http_version_t version);
// Dispatch APIi, provided by dispatch
void http_parse_init(struct http_parser_data *fsm);
void http_parse_execute(struct http_parser_data *fsm, void* const id, const char *http_data, int len);
int http_parse_finish(struct http_parser_data *fsm);

#endif /* __HTTP_DISPATCH_H__ */

