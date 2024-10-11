#include "suites.h"

#include <check.h>

#include "LDSC.h"

#include "../src/factory.h"
#include "../src/type_masks.h"

/****************************** Test Cases ******************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  LDSC_structure* my_queue = LDSC_queue_init();

  int id = my_queue->id;
  int length = my_queue->length;
  void* head = my_queue->head;
  void* tail = my_queue->tail;

  ck_assert_int_eq(id, Queue_ID);
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  LDSC_delete(my_queue, NULL);
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
  LDSC_structure* my_queue = LDSC_queue_init();

  /* list should be empty */
  int length = LDSC_length(my_queue);
  ck_assert_int_eq(length, 0);

  /* manually changing length */
  int new_length = 22;
  my_queue->length = new_length;

  /* list should have length of new_length */
  length = LDSC_length(my_queue);
  ck_assert_int_eq(length, new_length);
  
  LDSC_delete(my_queue, NULL);
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
  LDSC_structure* my_queue = LDSC_queue_init();
  int is_empty = 0;

  is_empty = LDSC_empty(my_queue);
  ck_assert_int_eq(is_empty, EMPTY);

  /* MANUAL SIZE ADJUSTMENT */
  my_queue->length = 3;

  is_empty = LDSC_empty(my_queue);
  ck_assert_int_eq(is_empty, NOT_EMPTY);
  
  LDSC_delete(my_queue, NULL);
} END_TEST

/* TEST CASE EMPTY END */

/****************************** Suite Definition ******************************/

Suite* LDSC_queue_suite() {
  Suite *queue_suite;
  queue_suite = suite_create("LDSC_queue");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(queue_suite, tc_core);

  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, length_null_structure);
  tcase_add_test(tc_length, length);
  suite_add_tcase(queue_suite, tc_length);

  TCase* tc_empty = tcase_create("empty");
  tcase_add_test(tc_empty, empty);
  tcase_add_test(tc_empty, empty_null_structure);
  suite_add_tcase(queue_suite, tc_empty);

  return queue_suite;
}

