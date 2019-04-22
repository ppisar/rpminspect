/*
 * Copyright (C) 2019  Red Hat, Inc.
 * Author(s):  David Shea <dshea@redhat.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include <CUnit/Basic.h>

/* Special exit codes used by automake */
#define EXIT_SKIP       (77)
#define EXIT_HARD_ERROR (99)

/* Defined by the test module */
CU_pSuite get_suite(void);

/* Given a function that returns a test suite, initialize the test registry,
 * run the test suite, cleanup, and exit with the appropriate error code */
int main(void)
{
    CU_pSuite pSuite;
    unsigned int failures;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        fprintf(stderr, "*** Unable to initialize test registry: %s\n", CU_get_error_msg());
        return EXIT_HARD_ERROR;
    }

    pSuite = get_suite();
    if (pSuite == NULL) {
        fprintf(stderr, "*** Unable to initialize test suite: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return EXIT_HARD_ERROR;
    }

    /* run all tests using the CUnit basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    if (CU_basic_run_tests() != CUE_SUCCESS) {
        fprintf(stderr, "*** Error running tests: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return EXIT_HARD_ERROR;
    }

    failures = CU_get_number_of_tests_failed();

    CU_cleanup_registry();

    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
