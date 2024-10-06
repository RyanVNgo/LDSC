#include "test_suites.h"

#include <stdlib.h>
#include <time.h>

#include <check.h>

#include "LDSC.h"

#include "../src/factory.h"
#include "../src/type_masks.h"

/****************************** Test Cases ******************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  LDSC_structure* my_linked_list = LDSC_linked_list_init();

  int id = my_linked_list->id;
  int length = my_linked_list->length;
  void* head = my_linked_list->head;
  void* tail = my_linked_list->tail;

  ck_assert_int_eq(id, LinkedList_ID);
  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  LDSC_delete(my_linked_list, NULL);
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
  LDSC_structure* my_linked_list = LDSC_linked_list_init();

  /* list should be empty */
  int length = LDSC_length(my_linked_list);
  ck_assert_int_eq(length, 0);

  /* manually changing length */
  int new_length = 22;
  my_linked_list->length = new_length;

  /* list should have length of new_length */
  length = LDSC_length(my_linked_list);
  ck_assert_int_eq(length, new_length);
  
  LDSC_delete(my_linked_list, NULL);
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
  LDSC_structure* my_linked_list = LDSC_linked_list_init();
  int is_empty = 0;

  is_empty = LDSC_empty(my_linked_list);
  ck_assert_int_eq(is_empty, EMPTY);

  /* MANUAL SIZE ADJUSTMENT */
  my_linked_list->length = 3;

  is_empty = LDSC_empty(my_linked_list);
  ck_assert_int_eq(is_empty, NOT_EMPTY);
  
  LDSC_delete(my_linked_list, NULL);
} END_TEST

/* TEST CASE EMPTY END */

/****************************** Suite Definition ******************************/

/* SUITE DEFINITION */

Suite* LDSC_linkedList_suite() {
  srand(time(NULL));

  Suite *linkedList_suite;
  linkedList_suite = suite_create("LDSC_linkedList");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(linkedList_suite, tc_core);
  
  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, length);
  tcase_add_test(tc_length, length_null_structure);
  suite_add_tcase(linkedList_suite, tc_length );
  
  TCase* tc_empty = tcase_create("empty");
  tcase_add_test(tc_empty, empty);
  tcase_add_test(tc_empty, empty_null_structure);
  suite_add_tcase(linkedList_suite, tc_empty);

  return linkedList_suite;
}

