#include <stdlib.h>

#include "test_linkedLists.h"
#include <LDSC.h>
#include <check.h>

// TEST CASE CORE START

START_TEST(linkedList_init) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);
  for (int i = 1; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);
  for (int i = 1; i < nodeCount; i++)
    LDSC_linkedList_prepend(myLL, (void*)&testData[i]);

  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

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
  for (i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int dataOut[nodeCount];
  for (i = 0; i < nodeCount; i++)
    dataOut[i] = *(int*)LDSC_linkedList_get(myLL, i);

  for (i = 0; i < nodeCount; i++)
    ck_assert_int_eq(testData[i], dataOut[i]);

} END_TEST

// TEST CASE GET END

// TEST CASE INSERT START

START_TEST(linkedList_null_list_insert) {
  int testData = 17, index = 0;
  LDSC_linkedList_insert(NULL, (void*)&testData, index);
} END_TEST

START_TEST(linkedList_null_data_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int index = 0;
  LDSC_linkedList_insert(myLL, NULL, index);

  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_neg_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17, index = -1;
  LDSC_linkedList_insert(myLL, (void*)&testData, index);

  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  free(myLL);
} END_TEST

START_TEST(linkedList_greater_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int testDataInsert = 22, index = -1;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);
  int length = LDSC_linkedList_length(myLL);
  ck_assert_int_eq(length, nodeCount);

  free(myLL);
} END_TEST

START_TEST(linkedList_zero_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);
  
  void* initHead = LDSC_linkedList_head(myLL);

  int testDataInsert = 22, index = 0;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);
  void* newHead = LDSC_linkedList_head(myLL);
  int length = LDSC_linkedList_length(myLL);

  ck_assert_int_eq(nodeCount + 1, length);
  ck_assert_ptr_ne(initHead, newHead);

  free(myLL);
} END_TEST

START_TEST(linkedList_length_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);
  
  void* initTail = LDSC_linkedList_tail(myLL);

  int testDataInsert = 22, index = nodeCount;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);
  void* newTail = LDSC_linkedList_tail(myLL);
  int length = LDSC_linkedList_length(myLL);

  ck_assert_int_eq(nodeCount + 1, length);
  ck_assert_ptr_ne(initTail, newTail);

  free(myLL);
} END_TEST

START_TEST(linkedList_other_index_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  void* initHead = LDSC_linkedList_head(myLL);
  void* initTail = LDSC_linkedList_tail(myLL);

  int testDataInsert = 22, index = 2;
  LDSC_linkedList_insert(myLL, (void*)&testDataInsert, index);

  int length = LDSC_linkedList_length(myLL);
  void* newHead = LDSC_linkedList_head(myLL);
  void* newTail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, nodeCount + 1);
  ck_assert_ptr_eq(initHead, newHead);
  ck_assert_ptr_eq(initTail, newTail);

  int dataOut = *(int*)LDSC_linkedList_get(myLL, index);
  int prevDataOut = *(int*)LDSC_linkedList_get(myLL, index - 1);
  int nextDataOut = *(int*)LDSC_linkedList_get(myLL, index + 1);
  ck_assert_int_eq(dataOut, testDataInsert);
  ck_assert_int_eq(prevDataOut, testData[index - 1]);
  ck_assert_int_eq(nextDataOut, testData[index]);

  free(myLL);
} END_TEST

// TEST CASE INSERT END

// TEST CASE REMOVEFIRST START

START_TEST(linkedList_null_list_removeFirst) {
  void* dataOutPtr = LDSC_linkedList_removeFirst(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

START_TEST(linkedList_empty_list_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  void* dataOutPtr = LDSC_linkedList_removeFirst(myLL);
  ck_assert_ptr_null(dataOutPtr);
  free(myLL);
} END_TEST

START_TEST(linkedList_single_item_list_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  int dataOut = *(int*)LDSC_linkedList_removeFirst(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);
  ck_assert_int_eq(testData, dataOut);

  free(myLL);
} END_TEST

START_TEST(linkedList_two_item_list_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 2;
  int testData[] = {
    17,
    9
  };
  LDSC_linkedList_append(myLL, (void*)&testData[0]);
  LDSC_linkedList_append(myLL, (void*)&testData[1]);

  int dataOut = *(int*)LDSC_linkedList_removeFirst(myLL);
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_eq(head, tail);
  ck_assert_int_eq(nodeCount - 1, length);
  ck_assert_int_eq(testData[0], dataOut);
  dataOut = *(int*)LDSC_linkedList_get(myLL, 0);
  ck_assert_int_eq(testData[1], dataOut);

  free(myLL);
} END_TEST

START_TEST(linkedList_removeFirst) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int dataOut = *(int*)LDSC_linkedList_removeFirst(myLL);
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_ne(head, tail);
  ck_assert_int_eq(nodeCount - 1, length);
  ck_assert_int_eq(testData[0], dataOut);
  for (int i = 1; i < nodeCount - 1; i++) {
    dataOut = *(int*)LDSC_linkedList_get(myLL, i-1);
    ck_assert_int_eq(testData[i], dataOut);
  }

  free(myLL);
} END_TEST

// TEST CASE REMOVEFIRST END

// TEST CASE REMOVELAST START

START_TEST(linkedList_null_list_removeLast) {
  void* dataOutPtr = LDSC_linkedList_removeLast(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

START_TEST(linkedList_empty_list_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  void* dataOutPtr = LDSC_linkedList_removeLast(myLL);
  ck_assert_ptr_null(dataOutPtr);
  free(myLL);
} END_TEST

START_TEST(linkedList_single_item_list_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int testData = 17;
  LDSC_linkedList_append(myLL, (void*)&testData);

  int dataOut = *(int*)LDSC_linkedList_removeLast(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);
  ck_assert_int_eq(testData, dataOut);

  free(myLL);
} END_TEST

START_TEST(linkedList_two_item_list_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 2;
  int testData[] = {
    17,
    9
  };
  LDSC_linkedList_append(myLL, (void*)&testData[0]);
  LDSC_linkedList_append(myLL, (void*)&testData[1]);

  int dataOut = *(int*)LDSC_linkedList_removeLast(myLL);
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_eq(head, tail);
  ck_assert_int_eq(nodeCount - 1, length);
  ck_assert_int_eq(testData[1], dataOut);
  dataOut = *(int*)LDSC_linkedList_get(myLL, 0);
  ck_assert_int_eq(testData[0], dataOut);

  free(myLL);
} END_TEST

START_TEST(linkedList_removeLast) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int nodeCount = 3;
  int testData[] = {
    17,
    9,
    19
  };
  for (int i = 0; i < nodeCount; i++)
    LDSC_linkedList_append(myLL, (void*)&testData[i]);

  int dataOut = *(int*)LDSC_linkedList_removeLast(myLL);
  int length = LDSC_linkedList_length(myLL);
  void* head = LDSC_linkedList_head(myLL);
  void* tail = LDSC_linkedList_tail(myLL);

  ck_assert_ptr_nonnull(head);
  ck_assert_ptr_nonnull(tail);
  ck_assert_ptr_ne(head, tail);
  ck_assert_int_eq(nodeCount - 1, length);
  ck_assert_int_eq(testData[nodeCount - 1], dataOut);
  for (int i = 0; i < nodeCount - 1; i++) {
    dataOut = *(int*)LDSC_linkedList_get(myLL, i);
    ck_assert_int_eq(testData[i], dataOut);
  }

  free(myLL);
} END_TEST

// TEST CASE REMOVELAST END

// SUITE DEFINITION

Suite* LDSC_linkedList_suite() {
  Suite *s;
  s = suite_create("LDSC_linkedList");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, linkedList_init);
  suite_add_tcase(s, tc_core);

  TCase* tc_append= tcase_create("append");
  tcase_add_test(tc_append, linkedList_null_list_append);
  tcase_add_test(tc_append, linkedList_null_data_append);
  tcase_add_test(tc_append, linkedList_empty_append);
  tcase_add_test(tc_append, linkedList_nonempty_append);
  suite_add_tcase(s, tc_append);

  TCase* tc_prepend = tcase_create("prepend");
  tcase_add_test(tc_prepend, linkedList_null_list_prepend);
  tcase_add_test(tc_prepend, linkedList_null_data_prepend);
  tcase_add_test(tc_prepend, linkedList_empty_prepend);
  tcase_add_test(tc_prepend, linkedList_nonempty_prepend);
  suite_add_tcase(s, tc_prepend);

  TCase* tc_get = tcase_create("get");
  tcase_add_test(tc_get, linkedList_null_list_get);
  tcase_add_test(tc_get, linkedList_neg_index_get);
  tcase_add_test(tc_get, linkedList_length_index_get);
  tcase_add_test(tc_get, linkedList_greater_index_get);
  tcase_add_test(tc_get, linkedList_get);
  suite_add_tcase(s, tc_get);

  TCase* tc_insert = tcase_create("insert");
  tcase_add_test(tc_insert, linkedList_null_list_insert);
  tcase_add_test(tc_insert, linkedList_null_data_insert);
  tcase_add_test(tc_insert, linkedList_neg_index_insert);
  tcase_add_test(tc_insert, linkedList_greater_index_insert);
  tcase_add_test(tc_insert, linkedList_zero_index_insert);
  tcase_add_test(tc_insert, linkedList_length_index_insert);
  tcase_add_test(tc_insert, linkedList_other_index_insert);
  suite_add_tcase(s, tc_insert);

  TCase* tc_removeFirst = tcase_create("removeFirst");
  tcase_add_test(tc_removeFirst, linkedList_null_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_empty_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_single_item_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_two_item_list_removeFirst);
  tcase_add_test(tc_removeFirst, linkedList_removeFirst);
  suite_add_tcase(s, tc_removeFirst);

  TCase* tc_removeLast= tcase_create("removeLast");
  tcase_add_test(tc_removeLast, linkedList_null_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_empty_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_single_item_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_two_item_list_removeLast);
  tcase_add_test(tc_removeLast, linkedList_removeLast);
  suite_add_tcase(s, tc_removeLast);

  return s;
}

