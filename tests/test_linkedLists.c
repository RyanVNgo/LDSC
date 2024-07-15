#include <stdlib.h>

#include "test_linkedLists.h"
#include <LDSC.h>
#include <check.h>

// TEST CASE CORE START

START_TEST(linkedList_init) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

// TEST CASE CORE END 

// TEST CASE APPEND START 

START_TEST(linkedList_null_list_append) {
  int testData = 17;
  LDSC_linkedList_append(NULL, (void*)&testData);
} END_TEST

START_TEST(linkedList_null_data_append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  LDSC_linkedList_append(myLL, NULL);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_empty_append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 1);
  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_eq(head, tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_nonempty_append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };

  LDSC_linkedList_append(myLL, (void*)&testData[0]);
  LDSC_node* initHead = LDSC_linkedList_head(myLL);
  LDSC_node* initTail = LDSC_linkedList_tail(myLL);
  for (int i = 1; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, nodeCount);
  ck_assert_ptr_ne(head, tail);
  ck_assert_ptr_eq(initHead, head);
  ck_assert_ptr_ne(initTail, tail);

  free(myLL);
} END_TEST

// TEST CASE APPEND END

// TEST CASE PREPEND START

START_TEST(linkedList_null_list_prepend) {
  int testData = 17;
  LDSC_linkedList_prepend(NULL, (void*)&testData);
} END_TEST

START_TEST(linkedList_null_data_prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  LDSC_linkedList_prepend(myLL, NULL);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_empty_prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_prepend(myLL, (void*)&testData);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 1);
  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_eq(head, tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_nonempty_prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };

  LDSC_linkedList_prepend(myLL, (void*)&testData[0]);
  LDSC_node* initHead = LDSC_linkedList_head(myLL);
  LDSC_node* initTail = LDSC_linkedList_tail(myLL);
  for (int i = 1; i < nodeCount; i++)
    LDSC_linkedList_prepend(myLL, (void*)&testData[i]);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, nodeCount);
  ck_assert_ptr_ne(head, tail);
  ck_assert_ptr_ne(initHead, head);
  ck_assert_ptr_eq(initTail, tail);

  free(myLL);
} END_TEST

// TEST CASE PREPEND END

// TEST CASE GET START

START_TEST(linkedList_null_list_get) {
  int index = 0;
  void* dataPtrOut = LDSC_linkedList_get(NULL, index);
  ck_assert_ptr_null(dataPtrOut);
} END_TEST

START_TEST(linkedList_neg_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);
  int index = -1;
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);
  ck_assert_ptr_null(dataPtrOut);
  free(myLL);
} END_TEST

START_TEST(linkedList_length_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);
  int index = LDSC_linkedList_length(myLL);
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);
  ck_assert_ptr_null(dataPtrOut);
  free(myLL);
} END_TEST

START_TEST(linkedList_greater_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);
  int index = LDSC_linkedList_length(myLL) + 1;
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);
  ck_assert_ptr_null(dataPtrOut);
  free(myLL);
} END_TEST

START_TEST(linkedList_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };

  int i;
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int dataOut[nodeCount];
  for (i = 0; i < nodeCount; i++)
    dataOut[i] = *(int*)LDSC_linkedList_get(myLL, i);

  for (i = 0; i < nodeCount; i++)
    ck_assert_int_eq(testData[i], dataOut[i]);

} END_TEST

// TEST CASE GET END 

// SUITE DEFINITION

Suite* LDSC_linkedList_suite() {
  Suite *s;
  s = suite_create("LDSC_linkedList");

  TCase* tc_core = tcase_create("Core");
  tcase_add_test(tc_core, linkedList_init);
  suite_add_tcase(s, tc_core);

  TCase* tc_insert = tcase_create("Append");
  tcase_add_test(tc_insert, linkedList_null_list_append);
  tcase_add_test(tc_insert, linkedList_null_data_append);
  tcase_add_test(tc_insert, linkedList_empty_append);
  tcase_add_test(tc_insert, linkedList_nonempty_append);
  suite_add_tcase(s, tc_insert);

  TCase* tc_prepend = tcase_create("Prepend");
  tcase_add_test(tc_prepend, linkedList_null_list_prepend);
  tcase_add_test(tc_insert, linkedList_null_data_prepend);
  tcase_add_test(tc_insert, linkedList_empty_prepend);
  tcase_add_test(tc_insert, linkedList_nonempty_prepend);
  suite_add_tcase(s, tc_prepend);

  TCase* tc_get= tcase_create("Get");
  tcase_add_test(tc_get, linkedList_null_list_get);
  tcase_add_test(tc_get, linkedList_neg_index_get);
  tcase_add_test(tc_get, linkedList_length_index_get);
  tcase_add_test(tc_get, linkedList_greater_index_get);
  tcase_add_test(tc_get, linkedList_get);
  suite_add_tcase(s, tc_get);


  return s;
}
