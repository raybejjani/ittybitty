/*
 * Parse HTTP requests
 */

#include <stdio.h>
#include <string.h>

#include "http_dispatch.h"

#define BUFLEN 1024

%%{
	machine http_parse;
	access fsm->;

	# Actions
	# sends out every character of the request
	action req_accum {
		itty_http_dispatch_accumReq(id, fc);
	}
	# sets the HTTP verb (GET, POST etc.)
	action verb_get {
		itty_http_dispatch_setVerb(id, HTTP_DISPATCH_VERB_GET);
	}
	# sends out every character of the resrouce path
	action path_accum {
		itty_http_dispatch_accumPath(id, fc);
	}
	# sets the HTTP version 
	action version_1_0 {
		itty_http_dispatch_setHttpVersion(id, HTTP_DISPATCH_HTTP_VERSION_1_0);
	}
	action version_1_1 {
		itty_http_dispatch_setHttpVersion(id, HTTP_DISPATCH_HTTP_VERSION_1_1);
	}


	# Sub-Machines
	http_any = alpha|"_"|"-"; 

	http_endline = "\r" "\n"?;
	http_verb = "GET" @verb_get;
	http_path = (("/" http_any*)+ ("." http_any+)?) $ path_accum;
	http_version = "HTTP/" (("1.0" @version_1_0) | ("1.1" @version_1_1));
	http_header_start =
		http_verb space+ http_path space+ http_version http_endline;

	http_header_option = 
		http_any+ ":" space* (any-http_endline)+ http_endline;

	http_request = http_header_start http_header_option* http_endline;

	# main Machine
	main := (
 		http_request $ req_accum
		);
}%%

%% write data;

void http_parse_init(struct http_parser_data *fsm) {
	%% write init;
}

void http_parse_execute(struct http_parser_data *fsm, void* const id, const char *http_data, int len) {
	const char *p = http_data;
	const char *pe = http_data + len;

	%% write exec;
}

int http_parse_finish(struct http_parser_data *fsm) {
	if ( fsm->cs == http_parse_error )
		return -1;
	if ( fsm->cs >= http_parse_first_final )
		return 1;
	return 0;
}

