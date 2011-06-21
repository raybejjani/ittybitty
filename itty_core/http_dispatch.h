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

/*** Dispatch callbacks, provided to dispatch ***/
/*
 * Called for every character in the HTTP request.
 * id - user provided id value that is passed back in callbacks.
 */
void itty_http_dispatch_accumReq(void* id, char c);

/*
 * Called once the HTTP verb is determined.
 * id - user provided id value that is passed back in callbacks.
 */
void itty_http_dispatch_setVerb(void* id, http_dispatch_verb_t verb);

/*
 * Called for every character in the HTTP path.
 * id - user provided id value that is passed back in callbacks.
 */
void itty_http_dispatch_accumPath(void* id, char c);

/*
 * Called once the HTTP version is determined.
 * id - user provided id value that is passed back in callbacks.
 */
void itty_http_dispatch_setHttpVersion(void* id, http_dispatch_http_version_t version);

/*** Dispatch API, provided by dispatch ***/
/*
 * Initialises the parser to it's start state.
 */
void itty_http_dispatch_init(struct http_parser_data *fsm);

/*
 * Runs the parses on the input. Parser carries state.
 * id - user provided id value that is passed back in callbacks.
 */
void itty_http_dispatch_execute(struct http_parser_data *fsm, void* const id, const char *http_data, int len);

/*
 * Convenience function to check if parser is in a finish or error state.
 *
 * returns:  0  Incomplete
 *           1  Complete
 *          -1  Error
 */
int itty_http_dispatch_finish(struct http_parser_data *fsm);

#endif /* __HTTP_DISPATCH_H__ */

