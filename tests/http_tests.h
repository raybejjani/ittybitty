#ifndef __HTTP_TESTS_H_
#define __HTTP_TESTS_H_

#include "http_tests.h"

// Public data
CU_SuiteInfo* http_tests_suite;

// Public functions
int http_tests_init(void);
int http_tests_cleanup(void);

#endif /* __HTTP_TESTS_H_ */

