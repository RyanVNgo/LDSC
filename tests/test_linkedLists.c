#include <stdlib.h>
#include <time.h>

#include "LDSC_linkedList.h"
#include "test_linkedLists.h"
#include <check.h>

/**************************************************/

enum Test_constants {
  MAX_DATA_SET_SIZE = 100,
  MAX_INT_VALUE = 100
};

enum Status {
  ERROR = -1,
  FAIL = 0,
  SUCCESS = 1
};

/**************************************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  typedef struct privateData {
    int length;
    void* head;
    void* tail;
  } privateData;

  LDSC_linkedList* myLL = LDSC_linkedList_init();
  ck_assert_ptr_nonnull(myLL);

  privateData* pd = (privateData*)myLL->pd;
  int length = pd->length;
  void* head = pd->head;
  void* tail = pd->tail;

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  myLL->delete(myLL);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE LENGTH START */

START_TEST(length_invalid_params) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int length = myLL->length(NULL);
  ck_assert_int_eq(length, ERROR);
  myLL->delete(myLL);
} END_TEST

START_TEST(length) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int length = myLL->length(myLL);
  ck_assert_int_eq(length, 0);
  myLL->delete(myLL);
} END_TEST

/* TEST CASE LENGTH END */

/**************************************************/

/* TEST CASE EMPTY END */

START_TEST(empty_invalid_params) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int empty = myLL->empty(NULL);
  ck_assert_int_eq(empty, ERROR);
  myLL->delete(myLL);
} END_TEST

START_TEST(empty) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int empty = myLL->empty(myLL);
  ck_assert_int_eq(empty, 1);
  myLL->delete(myLL);
} END_TEST

/* TEST CASE EMPTY END */

/**************************************************/

/* TEST CASE APPEND START */

START_TEST(append_invalid_params) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int status = 0;

  status = myLL->append(NULL, NULL);
  ck_assert_int_eq(status, ERROR);

  status = myLL->append(myLL, NULL);
  ck_assert_int_eq(status, ERROR);

  int testData = 17;
  status = myLL->append(NULL, &testData);
  ck_assert_int_eq(status, ERROR);

  myLL->delete(myLL);
} END_TEST

START_TEST(append) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  for (int i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (int i = 0; i < testDataSize; i++)
    if (myLL->append(myLL, &testData[i]) != SUCCESS) break;

  int length = myLL->length(myLL);
  ck_assert_int_eq(length, testDataSize);

  myLL->delete(myLL);
} END_TEST

/* TEST CASE APPEND END */

/**************************************************/

/* TEST CASE PREPEND START */

START_TEST(prepend_invalid_params) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int status = 0;

  status = myLL->prepend(NULL, NULL);
  ck_assert_int_eq(status, ERROR);

  status = myLL->prepend(myLL, NULL);
  ck_assert_int_eq(status, ERROR);

  int testData = 17;
  status = myLL->prepend(NULL, &testData);
  ck_assert_int_eq(status, ERROR);

  myLL->delete(myLL);
} END_TEST

START_TEST(prepend) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  for (int i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (int i = 0; i < testDataSize; i++)
    if (myLL->prepend(myLL, &testData[i]) != SUCCESS) break;

  int length = myLL->length(myLL);
  ck_assert_int_eq(length, testDataSize);

  myLL->delete(myLL);
} END_TEST

/* TEST CASE PREPEND END */

/**************************************************/

/* TEST CASE ADD START */

START_TEST(add_invalid_params) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int status = 0;

  status = myLL->add(NULL, NULL, 0);
  ck_assert_int_eq(status, ERROR);

  status = myLL->add(myLL, NULL, 0);
  ck_assert_int_eq(status, ERROR);

  int testData = 17;
  status = myLL->add(NULL, &testData, 0);
  ck_assert_int_eq(status, ERROR);

  myLL->append(myLL, &testData);
  status = myLL->add(myLL, &testData, -1);
  ck_assert_int_eq(status, FAIL);
  
  int length = myLL->length(myLL);
  status = myLL->add(myLL, &testData, length + 1);
  ck_assert_int_eq(status, FAIL);

  myLL->delete(myLL);
} END_TEST

#include <stdio.h>
START_TEST(add) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  for (int i = 0; i < testDataSize; i++)
    testData[i] = 0;
    //testData[i] = rand() % MAX_INT_VALUE;

  int index = 0;
  int length;
  for (int i = 0; i < testDataSize; i++) {
    length = myLL->length(myLL);
    index = rand() % (length+1);
    if (myLL->add(myLL, &testData[i], index) != SUCCESS) break;
  }

  length = myLL->length(myLL);
  ck_assert_int_eq(length, testDataSize);

  myLL->delete(myLL);
} END_TEST

/* TEST CASE ADD END */

/**************************************************/

/* SUITE DEFINITION */

Suite* LDSC_linkedList_suite() {
  srand(time(NULL));

  Suite *s;
  s = suite_create("LDSC_linkedList");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(s, tc_core);

  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, length_invalid_params);
  tcase_add_test(tc_length, length);
  suite_add_tcase(s, tc_length );

  TCase* tc_empty = tcase_create("empty");
  tcase_add_test(tc_empty, empty_invalid_params);
  tcase_add_test(tc_empty, empty);
  suite_add_tcase(s, tc_empty);

  TCase* tc_append = tcase_create("append");
  tcase_add_test(tc_append, append_invalid_params);
  tcase_add_test(tc_append, append);
  suite_add_tcase(s, tc_append );

  TCase* tc_prepend= tcase_create("prepend");
  tcase_add_test(tc_prepend, prepend_invalid_params);
  tcase_add_test(tc_prepend, prepend);
  suite_add_tcase(s, tc_prepend);

  TCase* tc_add = tcase_create("add");
  tcase_add_test(tc_add, add_invalid_params);
  tcase_add_test(tc_add, add);
  suite_add_tcase(s, tc_add);

  return s;
}

