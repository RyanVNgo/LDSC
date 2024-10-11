/** @file   test_main.h
 *  @brief  Program entry point.
 *
 *  @author Ryan V. Ngo
 */

#include <stdlib.h>
#include <stdio.h>

#include <check.h>

#include "suites.h"

/****************************** Suite Runner Init ******************************/

START_TEST(check) {} END_TEST
Suite* sr_init(void) {
  Suite* suite;
  TCase* tc_core;
  suite = suite_create("Check");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, check);
  suite_add_tcase(suite, tc_core);
  return suite;
}

/****************************** Main ******************************/

int main() {
  printf("\n");
  int number_failed;
  SRunner* suite_runner;
  
  suite_runner = srunner_create(sr_init());

  srunner_add_suite(suite_runner, LDSC_linkedList_suite());
  srunner_add_suite(suite_runner, LDSC_stack_suite());
  srunner_add_suite(suite_runner, LDSC_queue_suite());

  srunner_run_all(suite_runner, CK_VERBOSE);

  number_failed = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);

  printf("\n");
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

