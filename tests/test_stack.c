#include <stdlib.h>

#include "test_stack.h"
#include <LDSC.h>
#include <check.h>

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE CORE START

// TEST CASE CORE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE LENGTH START


// TEST CASE LENGTH END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PUSH START


// TEST CASE PUSH END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE ISEMPTY START



// TEST CASE ISEMPTY END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PEEK START


// TEST CASE PEEK END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE POP START



// TEST CASE POP END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE INTEGRATION START


// TEST CASE INTEGRATION END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// SUITE DEFINITION

Suite* LDSC_stack_suite(void) {
  Suite *s;
  s = suite_create("LDSC_stack");

  TCase* tc_core = tcase_create("core");
  suite_add_tcase(s, tc_core);

  TCase* tc_length = tcase_create("length");
  suite_add_tcase(s, tc_length);

  TCase* tc_push = tcase_create("push");
  suite_add_tcase(s, tc_push);

  TCase* tc_isEmpty = tcase_create("isEmpty");
  suite_add_tcase(s, tc_isEmpty);

  TCase* tc_peek = tcase_create("peek");
  suite_add_tcase(s, tc_peek);

  TCase* tc_pop = tcase_create("pop");
  suite_add_tcase(s, tc_pop);

  TCase* tc_integration = tcase_create("integration");
  suite_add_tcase(s, tc_integration);

  return s;
}
