/*
 * Support & utility functions for ittybitty tests.
 */

#ifndef __ITTY_TESTS_H_
#define __ITTY_TESTS_H_

#include "CUnit.h"

#define ITTY_TEST_ENTRY(func) { __FILE__ ":" #func, func }
#define ITTY_SUITE_ENTRY(suite) { #suite, suite##_init, suite##_cleanup, suite##_tests }

#endif /* __ITTY_TESTS_H_ */

