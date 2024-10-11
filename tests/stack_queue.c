#include "suites.h"

#include <stdlib.h>

#include <check.h>

#include "LDSC.h"

#include "../src/factory.h"
#include "../src/type_masks.h"

/****************************** Test Cases ******************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  LDSC_structure* my_stack = LDSC_stack_init();

  int id = my_stack->id;
  int length = my_stack->length;
  void* head = my_stack->head;

  ck_assert_int_eq(id, Stack_ID);
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);

  LDSC_delete(my_stack, NULL);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE LENGTH START */

START_TEST(length_null_structure) {
  /* should return error value with NULL structure */
  int length = LDSC_length(NULL);
  ck_assert_int_eq(length, LDSC_ERROR);
} END_TEST

START_TEST(length) {
  LDSC_structure* my_stack = LDSC_stack_init();

  /* list should be empty */
  int length = LDSC_length(my_stack);
  ck_assert_int_eq(length, 0);

  /* manually changing length */
  int new_length = 22;
  my_stack->length = new_length;

  /* list should have length of new_length */
  length = LDSC_length(my_stack);
  ck_assert_int_eq(length, new_length);
  
  LDSC_delete(my_stack, NULL);
} END_TEST

/* TEST CASE LENGTH END */

/**************************************************/

#define EMPTY 1
#define NOT_EMPTY 0

/* TEST CASE EMPTY START */

START_TEST(empty_null_structure) {
  /* should return error value with NULL structure */
  int is_empty = LDSC_empty(NULL);
  ck_assert_int_eq(is_empty, LDSC_ERROR);
} END_TEST

START_TEST(empty) {
  LDSC_structure* my_stack = LDSC_stack_init();
  int is_empty = 0;

  is_empty = LDSC_empty(my_stack);
  ck_assert_int_eq(is_empty, EMPTY);

  /* MANUAL SIZE ADJUSTMENT */
  my_stack->length = 3;

  is_empty = LDSC_empty(my_stack);
  ck_assert_int_eq(is_empty, NOT_EMPTY);
  
  LDSC_delete(my_stack, NULL);
} END_TEST

/* TEST CASE EMPTY END */

/**************************************************/

/* TEST CASE PUSH START */

START_TEST(push_invalid_params) {
  LDSC_structure* my_stack = LDSC_stack_init();
  int* data = malloc(sizeof(int));
  int status = 0;

  /* should return error value with NULL structure */
  status = LDSC_push(NULL, data);
  ck_assert_int_eq(status, LDSC_ERROR);

  status = LDSC_push(my_stack, NULL);
  ck_assert_int_eq(status, LDSC_ERROR);

  free(data);
  LDSC_delete(my_stack, NULL);
} END_TEST

START_TEST(push) {

} END_TEST

/* TEST CASE PUSH END */

/****************************** Suite Definition ******************************/

Suite* LDSC_stack_suite(void) {
  Suite *stack_suite;
  stack_suite = suite_create("LDSC_stack");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(stack_suite, tc_core);

  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, length_null_structure);
  tcase_add_test(tc_length, length);
  suite_add_tcase(stack_suite, tc_length);

  TCase* tc_empty = tcase_create("empty");
  tcase_add_test(tc_empty, empty_null_structure);
  tcase_add_test(tc_empty, empty);
  suite_add_tcase(stack_suite, tc_empty);

  TCase* tc_push = tcase_create("push");
  tcase_add_test(tc_push, push_invalid_params);
  tcase_add_test(tc_push, push);
  suite_add_tcase(stack_suite, tc_push);

  return stack_suite;
}
