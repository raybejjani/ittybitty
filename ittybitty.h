/**
 * ittybitty interface header. Include this to be able to call ittybitty
 */

#include <stdint.h>

// User defined functions & structs


// itty defined functions & structs

typedef enum {
	itty_status_ok,	
	itty_status_error,	
} itty_status_t;


/**
 * Given a socket handle will consume a HTTP request and produce the resonse
 */
itty_status_t itty_handle(int sockfd);

