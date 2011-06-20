/*
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "CUnit.h"
#include "itty_tests.h"
#include "http_tests.h"
#include "http_dispatch.h"

// Private functions prototypes
static void http_get_req();
static void http_get_verb();
static void http_get_path();
static void http_get_httpVersion();
static void http_parse_ignoreHeaders();
static CU_TestInfo http_tests_tests[];

// Public data
CU_SuiteInfo suite[] = {
	ITTY_SUITE_ENTRY(http_tests),
	CU_SUITE_INFO_NULL,
};
CU_SuiteInfo* http_tests_suite = suite;

// Public functions
//noop, success
int http_tests_init() {
	return 0;
}
//noop, success
int http_tests_cleanup() {
	return 0;
}


// Private functions and tests
static CU_TestInfo http_tests_tests[] = {
	ITTY_TEST_ENTRY(http_get_req),
	ITTY_TEST_ENTRY(http_get_verb),
	ITTY_TEST_ENTRY(http_get_path),
	ITTY_TEST_ENTRY(http_get_httpVersion),
	ITTY_TEST_ENTRY(http_parse_ignoreHeaders),
	CU_TEST_INFO_NULL,
};


// Data for tests
const char* const get_req_noheaders = "\
GET /path/file.html HTTP/1.0\r\n\
\r\n\
";

const char* const get_req = "\
GET /path/file.html HTTP/1.0\r\n\
From: someuser@somewhere.com\r\n\
User-Agent: useragent/1.0\r\n\
\r\n\
";

struct http_parser_test_data {
	char req[4096];
	http_dispatch_verb_t verb;
	char path[256];
	http_dispatch_http_version_t version;
};

void itty_http_dispatch_accumReq(void* id, char c) {
	struct http_parser_test_data* data = (struct http_parser_test_data*)id;
	data->req[strlen(data->req)] = c;
}

void itty_http_dispatch_setVerb(void* id, http_dispatch_verb_t verb) {
	struct http_parser_test_data* data = (struct http_parser_test_data*)id;
	data->verb = verb;
}

void itty_http_dispatch_accumPath(void* id, char c) {
	struct http_parser_test_data* data = (struct http_parser_test_data*)id;
	char dummy[2];
	dummy[0] = c;
	dummy[1] = '\0';
	strcat(data->path, dummy);
}

void itty_http_dispatch_setHttpVersion(void* id, http_dispatch_http_version_t version) {
	struct http_parser_test_data* data = (struct http_parser_test_data*)id;
	data->version = version;
}

/*
 * Test whether we can extract the request
 */
static void http_get_req() {
	struct http_parser_test_data data;
	struct http_parser_data parser;

	memset(&data, 0, sizeof(data));
	http_parse_init(&parser);

	http_parse_execute(&parser, &data, get_req_noheaders, strlen(get_req_noheaders));

	// Check that we didnt error out
	CU_ASSERT(http_parse_finish(&parser) != -1);
	// Check that we finished
	CU_ASSERT(http_parse_finish(&parser) != 0);
	CU_ASSERT(http_parse_finish(&parser) == 1);
	// check that we grabbed the path
	CU_ASSERT_STRING_EQUAL(data.req, get_req_noheaders);
}

/*
 * Test whether we can extract the GET verb
 */
static void http_get_verb() {
	struct http_parser_test_data data;
	struct http_parser_data parser;
	
	memset(&data, 0, sizeof(data));	
	http_parse_init(&parser);

	http_parse_execute(&parser, &data, get_req_noheaders, strlen(get_req_noheaders));

	// Check that we didnt error out
	CU_ASSERT(http_parse_finish(&parser) != -1);
	// Check that we finished
	CU_ASSERT(http_parse_finish(&parser) != 0);
	CU_ASSERT(http_parse_finish(&parser) == 1);
	// check that we parsed the GET
	CU_ASSERT(data.verb == HTTP_DISPATCH_VERB_GET);
}

/*
 * Test whether we can extract the path
 */
static void http_get_path() {
	struct http_parser_test_data data;
	struct http_parser_data parser;

	memset(&data, 0, sizeof(data));
	http_parse_init(&parser);

	http_parse_execute(&parser, &data, get_req_noheaders, strlen(get_req_noheaders));

	// Check that we didnt error out
	CU_ASSERT(http_parse_finish(&parser) != -1);
	// Check that we finished
	CU_ASSERT(http_parse_finish(&parser) != 0);
	CU_ASSERT(http_parse_finish(&parser) == 1);
	// check that we grabbed the path
	CU_ASSERT_STRING_EQUAL(data.path, "/path/file.html");
}

/*
 * Test whether we can extract the path
 */
static void http_get_httpVersion() {
	struct http_parser_test_data data;
	struct http_parser_data parser;

	memset(&data, 0, sizeof(data));
	http_parse_init(&parser);

	http_parse_execute(&parser, &data, get_req_noheaders, strlen(get_req_noheaders));

	// Check that we didnt error out
	CU_ASSERT(http_parse_finish(&parser) != -1);
	// Check that we finished
	CU_ASSERT(http_parse_finish(&parser) != 0);
	CU_ASSERT(http_parse_finish(&parser) == 1);
	// check that we grabbed the path
	CU_ASSERT_EQUAL(data.version, HTTP_DISPATCH_HTTP_VERSION_1_0);
}

/*
 * Test whether we ignore headers and succeed at parsing
 */
static void http_parse_ignoreHeaders() {
	struct http_parser_test_data data;
	struct http_parser_data parser;

	memset(&data, 0, sizeof(data));
	http_parse_init(&parser);

	http_parse_execute(&parser, &data, get_req, strlen(get_req));

	// Check that we didnt error out
	CU_ASSERT(http_parse_finish(&parser) != -1);
	// Check that we finished
	CU_ASSERT(http_parse_finish(&parser) != 0);
	CU_ASSERT(http_parse_finish(&parser) == 1);
	CU_ASSERT_STRING_EQUAL(data.req, get_req);
}

