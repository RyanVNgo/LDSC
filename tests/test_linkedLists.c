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
  ck_assert_ptr_eq(head, NULL);
  ck_assert_ptr_eq(tail, NULL);

  free(myLL);
} END_TEST

// TEST CASE CORE END 

// TEST CASE INSERT START 

START_TEST(linkedList_null_list_insert) {
  int testData = 17;
  LDSC_linkedList_insert(NULL, (void*)&testData);
} END_TEST

START_TEST(linkedList_null_data_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  LDSC_linkedList_insert(myLL, NULL);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_eq(head, NULL);
  ck_assert_ptr_eq(tail, NULL);

  free(myLL);
} END_TEST

START_TEST(linkedList_empty_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_insert(myLL, (void*)&testData);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 1);
  ck_assert_ptr_ne(head, NULL);
  ck_assert_ptr_ne(tail, NULL);
  ck_assert_ptr_eq(head, tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_nonempty_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };

  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_insert(myLL, (void*)&testData[i]);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, nodeCount);
  ck_assert_ptr_ne(head, tail);

  free(myLL);
} END_TEST

// TEST CASE INSERT END

// TEST CASE GET START

START_TEST(linkedList_null_list_get) {
  int index = 0;
  void* dataPtrOut = LDSC_linkedList_get(NULL, index);
  ck_assert_ptr_eq(dataPtrOut, NULL);
} END_TEST

START_TEST(linkedList_neg_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_insert(myLL, (void*)&testData);
  int index = -1;
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);
  ck_assert_ptr_eq(dataPtrOut, NULL);
  free(myLL);
} END_TEST

START_TEST(linkedList_length_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_insert(myLL, (void*)&testData);
  int index = LDSC_linkedList_length(myLL);
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);
  ck_assert_ptr_eq(dataPtrOut, NULL);
  free(myLL);
} END_TEST

START_TEST(linkedList_greater_index_get) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_insert(myLL, (void*)&testData);
  int index = LDSC_linkedList_length(myLL) + 1;
  void* dataPtrOut = LDSC_linkedList_get(myLL, index);
  ck_assert_ptr_eq(dataPtrOut, NULL);
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
    LDSC_linkedList_insert(myLL, (void*)&testData[i]);

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

  TCase* tc_insert = tcase_create("Insert");
  tcase_add_test(tc_insert, linkedList_null_list_insert);
  tcase_add_test(tc_insert, linkedList_null_data_insert);
  tcase_add_test(tc_insert, linkedList_empty_insert);
  tcase_add_test(tc_insert, linkedList_nonempty_insert);
  suite_add_tcase(s, tc_insert);

  TCase* tc_get= tcase_create("Get");
  tcase_add_test(tc_get, linkedList_null_list_get);
  tcase_add_test(tc_get, linkedList_neg_index_get);
  tcase_add_test(tc_get, linkedList_length_index_get);
  tcase_add_test(tc_get, linkedList_greater_index_get);
  tcase_add_test(tc_get, linkedList_get);
  suite_add_tcase(s, tc_get);

  return s;
}
