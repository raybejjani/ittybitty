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

// Private functions prototypes
static void test_fail(void);
static void test_pass(void);
static CU_TestInfo http_tests_tests[];

// Public data
CU_SuiteInfo suite[] = {
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
	ITTY_TEST_ENTRY(test_fail),
	ITTY_TEST_ENTRY(test_pass),
	CU_TEST_INFO_NULL,
};


static void test_fail(void) {
	CU_FAIL();
}

static void test_pass(void) {
	CU_PASS();
}


