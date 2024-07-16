#include <stdlib.h>

#include "test_stack.h"
#include <LDSC.h>
#include <check.h>

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE CORE START

START_TEST(stack_core) {
  LDSC_stack* myStack = LDSC_stack_init();
  ck_assert_ptr_nonnull(myStack);
} END_TEST

// TEST CASE CORE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PUSH START


// TEST CASE PUSH END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE POP START
// TEST CASE POP END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PEEK START
// TEST CASE PEEK END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE ISEMPTY START
// TEST CASE ISEMPTY END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE SIZE START
// TEST CASE SIZE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// SUITE DEFINITION

Suite* LDSC_stack_suite(void) {
  Suite *s;
  s = suite_create("LDSC_stack");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, stack_core);
  suite_add_tcase(s, tc_core);

  TCase* tc_push = tcase_create("push");
  suite_add_tcase(s, tc_push);

  TCase* tc_pop = tcase_create("pop");
  suite_add_tcase(s, tc_pop);

  TCase* tc_peek = tcase_create("peek");
  suite_add_tcase(s, tc_peek);

  TCase* tc_isEmpty = tcase_create("isEmpty");
  suite_add_tcase(s, tc_isEmpty);

  TCase* tc_size = tcase_create("size");
  suite_add_tcase(s, tc_size);

  return s;
}
