#include <stdlib.h>
#include <stdio.h>

#include <check.h>
#include <LDSC.h>

#include "LDSC_stack.h"
#include "test_linkedLists.h"
#include "test_stack.h"
#include "test_queue.h"


START_TEST(check) {} END_TEST
Suite* sr_init(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("Check");
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, check);
  suite_add_tcase(s, tc_core);
  return s;
}

int main() {
  printf("\n");
  int numberFailed;
  SRunner *sr;
  
  sr = srunner_create(sr_init());

  srunner_add_suite(sr, LDSC_linkedList_suite());
  srunner_add_suite(sr, LDSC_stack_suite());
  srunner_add_suite(sr, LDSC_queue_suite());

  srunner_run_all(sr, CK_VERBOSE);

  numberFailed = srunner_ntests_failed(sr);
  srunner_free(sr);

  printf("\n");
  return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

