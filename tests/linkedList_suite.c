#include "suites.h"

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

  /* list should be empty */
  is_empty = LDSC_empty(my_linked_list);
  ck_assert_int_eq(is_empty, EMPTY);

  /* MANUAL SIZE ADJUSTMENT */
  my_linked_list->length = 3;

  /* list should NOT be empty */
  is_empty = LDSC_empty(my_linked_list);
  ck_assert_int_eq(is_empty, NOT_EMPTY);
  
  LDSC_delete(my_linked_list, NULL);
} END_TEST

/* TEST CASE EMPTY END */

/**************************************************/

/* TEST CASE APPEND START */

START_TEST(append_null_params) {
  /* should return error value with NULL structure */
  int status = 0;
  int* data = malloc(sizeof(int));
  *data = 13;

  status = LDSC_append(NULL, data);
  ck_assert_int_eq(status, LDSC_ERROR);

  LDSC_structure* my_linked_list = LDSC_linked_list_init();
  status = LDSC_append(my_linked_list, NULL);
  ck_assert_int_eq(status, LDSC_ERROR);

  free(data);
  LDSC_delete(my_linked_list, NULL);
} END_TEST

START_TEST(append) {
  LDSC_structure* my_linked_list = LDSC_linked_list_init();
  int status = 0;
  int* data_1 = malloc(sizeof(int));
  int* data_2 = malloc(sizeof(int));
  *data_1 = 13;
  *data_2 = 17;

  status = LDSC_append(my_linked_list, data_1);
  ck_assert_int_eq(status, 0);

  status = LDSC_append(my_linked_list, data_2);
  ck_assert_int_eq(status, 0);

  Node* head = my_linked_list->head;
  Node* tail = my_linked_list->tail;
  ck_assert_int_eq(*(int*)head->data_ptr, *data_1);
  ck_assert_int_eq(*(int*)tail->data_ptr, *data_2);
  ck_assert_ptr_eq(head->next, tail);

  LDSC_delete(my_linked_list, NULL);
} END_TEST

/* TEST CASE APPEND END */

/**************************************************/

/* TEST CASE PREPEND START */

START_TEST(prepend_null_params) {
  /* should return error value with NULL structure */
  int status = 0;
  int* data = malloc(sizeof(int));
  *data = 13;

  status = LDSC_prepend(NULL, data);
  ck_assert_int_eq(status, LDSC_ERROR);

  LDSC_structure* my_linked_list = LDSC_linked_list_init();
  status = LDSC_prepend(my_linked_list, NULL);
  ck_assert_int_eq(status, LDSC_ERROR);

  free(data);
  LDSC_delete(my_linked_list, NULL);
} END_TEST

START_TEST(prepend) {
  LDSC_structure* my_linked_list = LDSC_linked_list_init();
  int status = 0;
  int* data_1 = malloc(sizeof(int));
  int* data_2 = malloc(sizeof(int));
  *data_1 = 13;
  *data_2 = 17;

  status = LDSC_prepend(my_linked_list, data_1);
  ck_assert_int_eq(status, 0);

  status = LDSC_prepend(my_linked_list, data_2);
  ck_assert_int_eq(status, 0);

  /* manally checking if the structure is as expected */
  Node* head = my_linked_list->head;
  Node* tail = my_linked_list->tail;
  ck_assert_int_eq(*(int*)head->data_ptr, *data_2);
  ck_assert_int_eq(*(int*)tail->data_ptr, *data_1);
  ck_assert_ptr_eq(head->next, tail);

  LDSC_delete(my_linked_list, NULL);
} END_TEST

/* TEST CASE PREPEND END */

/**************************************************/

/* TEST CASE INSERT START */

START_TEST(insert_invalid_params) {
  /* should return error value with NULL structure */
  int status = 0;
  int* data = malloc(sizeof(int));
  *data = 13;

  status = LDSC_insert(NULL, data, 0);
  ck_assert_int_eq(status, LDSC_ERROR);

  LDSC_structure* my_linked_list = LDSC_linked_list_init();
  status = LDSC_insert(my_linked_list, NULL, 0);
  ck_assert_int_eq(status, LDSC_ERROR);

  status = LDSC_insert(my_linked_list, data, 1);
  ck_assert_int_eq(status, LDSC_INVALID_INDEX);

  status = LDSC_insert(my_linked_list, data, -2);
  ck_assert_int_eq(status, LDSC_INVALID_INDEX);

  free(data);
  LDSC_delete(my_linked_list, NULL);
} END_TEST

START_TEST(insert) {
  int status = 0;
  int elem_count = 3;
  int* data_tracker[3];
  
  /* append like inserts */
  LDSC_structure* my_linked_list_1 = LDSC_linked_list_init();
  for (int i = 0; i < elem_count; i++) {
    int* new_data = malloc(sizeof(int));
    *new_data = i;
    data_tracker[i] = new_data;
    status = LDSC_insert(my_linked_list_1, new_data, i);
    ck_assert_int_eq(status, 0);
  }
  ck_assert_ptr_eq(data_tracker[0], my_linked_list_1->head->data_ptr);
  ck_assert_ptr_eq(data_tracker[1], my_linked_list_1->head->next->data_ptr);
  ck_assert_ptr_eq(data_tracker[2], my_linked_list_1->tail->data_ptr);
  LDSC_delete(my_linked_list_1, NULL);

  /* prepend like inserts */
  LDSC_structure* my_linked_list_2 = LDSC_linked_list_init();
  for (int i = 0; i < elem_count; i++) {
    int* new_data = malloc(sizeof(int));
    *new_data = i;
    data_tracker[i] = new_data;
    status = LDSC_insert(my_linked_list_2, new_data, 0);
    ck_assert_int_eq(status, 0);
  }
  ck_assert_ptr_eq(data_tracker[2], my_linked_list_2->head->data_ptr);
  ck_assert_ptr_eq(data_tracker[1], my_linked_list_2->head->next->data_ptr);
  ck_assert_ptr_eq(data_tracker[0], my_linked_list_2->tail->data_ptr);
  LDSC_delete(my_linked_list_2, NULL);

  /* negative and middle insert */
  LDSC_structure* my_linked_list_3 = LDSC_linked_list_init();
  for(int i = 0; i < elem_count; i++) {
    int* new_data = malloc(sizeof(int));
    *new_data = i;
    data_tracker[i] = new_data;
  }
  LDSC_insert(my_linked_list_3, data_tracker[0], 0);
  LDSC_insert(my_linked_list_3, data_tracker[1], -1);
  LDSC_insert(my_linked_list_3, data_tracker[2], 1);

  ck_assert_ptr_eq(data_tracker[0], my_linked_list_3->head->data_ptr);
  ck_assert_ptr_eq(data_tracker[2], my_linked_list_3->head->next->data_ptr);
  ck_assert_ptr_eq(data_tracker[1], my_linked_list_3->tail->data_ptr);
  LDSC_delete(my_linked_list_3, NULL);
} END_TEST

/* TEST CASE INSERT END */

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

  TCase* tc_append = tcase_create("append");
  tcase_add_test(tc_append, append_null_params);
  tcase_add_test(tc_append, append);
  suite_add_tcase(linkedList_suite, tc_append);

  TCase* tc_prepend = tcase_create("prepend");
  tcase_add_test(tc_prepend, prepend_null_params);
  tcase_add_test(tc_prepend, prepend);
  suite_add_tcase(linkedList_suite, tc_prepend);

  TCase* tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, insert_invalid_params);
  tcase_add_test(tc_insert, insert);
  suite_add_tcase(linkedList_suite, tc_insert);

  TCase* tc_remove = tcase_create("remove");
  suite_add_tcase(linkedList_suite, tc_remove);

  TCase* tc_get = tcase_create("get");
  suite_add_tcase(linkedList_suite, tc_get);

  TCase* tc_front = tcase_create("front");
  suite_add_tcase(linkedList_suite, tc_front);

  TCase* tc_back= tcase_create("back");
  suite_add_tcase(linkedList_suite, tc_back);

  return linkedList_suite;
}

