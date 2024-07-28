#include <stdlib.h>
#include <time.h>

#include "LDSC_linkedList.h"
#include "test_linkedLists.h"
#include <LDSC_errors.h>
#include <check.h>

/**
 * Test suite for LDSC_linkedList data structure.
 * Only the 'initialization' test will check for possible malloc errors.
 * All following tests will assume successful mallocs.
 * All tests will test for successful LDSC_linkedList delete.
 * All status checks will occur before value checks, if applicable.
 * Beyond that, status checks will only occur the methods that the test targets
 */

/**************************************************/

enum Test_constants {
  MAX_DATA_SET_SIZE = 100,
  MAX_INT_VALUE = 100
};

/**************************************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  LDSC_error status = OK;
  typedef struct privateData {
    int length;
    void* head;
    void* tail;
  } privateData;

  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(myLL);

  privateData* pd = (privateData*)myLL->pd;
  int length = pd->length;
  void* head = pd->head;
  void* tail = pd->tail;

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_null(head);
  ck_assert_ptr_null(tail);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE LENGTH START */

START_TEST(length_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  int length = myLL->length(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_int_eq(length, ERROR);
  
  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(length) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  int length = myLL->length(myLL, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(length, 0);
  
  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE LENGTH END */

/**************************************************/

/* TEST CASE EMPTY END */

START_TEST(empty_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  int empty = myLL->empty(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_int_eq(empty, ERROR);
  
  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(empty) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  int empty = myLL->empty(myLL, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(empty, 1);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE EMPTY END */

/**************************************************/

/* TEST CASE APPEND START */

START_TEST(append_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  int testData = 17;

  myLL->append(NULL, NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->append(myLL, NULL, &status);
  ck_assert_int_eq(status, NULL_DATAPTR);

  myLL->append(NULL, &testData, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(append) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++) {
    myLL->append(myLL, &testData[i], &status);
    ck_assert_int_eq(status, OK);
  }

  int length = myLL->length(myLL, &status);
  ck_assert_int_eq(length, testDataSize);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE APPEND END */

/**************************************************/

/* TEST CASE PREPEND START */

START_TEST(prepend_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  int testData = 17;

  myLL->prepend(NULL, NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->prepend(myLL, NULL, &status);
  ck_assert_int_eq(status, NULL_DATAPTR);

  myLL->prepend(NULL, &testData, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(prepend) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++) {
    myLL->prepend(myLL, &testData[i], &status);
    ck_assert_int_eq(status, OK);
  }

  int length = myLL->length(myLL, &status);
  ck_assert_int_eq(length, testDataSize);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE PREPEND END */

/**************************************************/

/* TEST CASE ADD START */

START_TEST(add_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  int testData = 17;

  myLL->add(NULL, NULL, 0, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->add(myLL, NULL, 0, &status);
  ck_assert_int_eq(status, NULL_DATAPTR);

  myLL->add(NULL, &testData, 0, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->append(myLL, &testData, &status);
  
  myLL->add(myLL, &testData, -1, &status);
  ck_assert_int_eq(status, LESS_THAN_INDEX);
  
  int length = myLL->length(myLL, &status);
  myLL->add(myLL, &testData, length + 1, &status);
  ck_assert_int_eq(status, GREATER_THAN_INDEX);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(add) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  for (int i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  int index = 0;
  int length;
  for (int i = 0; i < testDataSize; i++) {
    length = myLL->length(myLL, &status);
    index = rand() % (length+1);
    myLL->add(myLL, &testData[i], index, &status);
    ck_assert_int_eq(status, OK);
  }

  length = myLL->length(myLL, &status);
  ck_assert_int_eq(length, testDataSize);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE ADD END */

/**************************************************/

/* TEST CASE AT START */

START_TEST(at_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  void* dataPtr = NULL;

  dataPtr = myLL->at(NULL, 0, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->at(myLL, -1, &status);
  ck_assert_int_eq(status, LESS_THAN_INDEX);
  ck_assert_ptr_null(dataPtr);
  
  dataPtr = myLL->at(myLL, 0, &status);
  ck_assert_int_eq(status, GREATER_THAN_INDEX);
  ck_assert_ptr_null(dataPtr);
  
  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(at) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++)
    myLL->append(myLL, &testData[i], &status);

  void* dataPtr = NULL;
  int index = 0;
  int dataOut = 0;
  for (i = 0; i < testDataSize; i++) {
    dataPtr = myLL->at(myLL, index, &status);
    ck_assert_int_eq(status, OK);
    ck_assert_ptr_nonnull(dataPtr);
    
    dataOut = *(int*)dataPtr;
    ck_assert_int_eq(dataOut, testData[index]);
  }

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE AT END */

/**************************************************/

/* TEST CASE REPLACE START */

START_TEST(replace_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  void* dataPtr = NULL;
  int testData = 17;

  dataPtr = myLL->replace(NULL, NULL, 0, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->replace(myLL, NULL, 0, &status);
  ck_assert_int_eq(status, NULL_DATAPTR);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->replace(NULL, &testData, 0, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->replace(myLL, &testData, -1, &status);
  ck_assert_int_eq(status, LESS_THAN_INDEX);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->replace(myLL, &testData, 0, &status);
  ck_assert_int_eq(status, GREATER_THAN_INDEX);
  ck_assert_ptr_null(dataPtr);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(replace) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++)
    myLL->append(myLL, &testData[i], &status);

  void* dataPtr = NULL;
  int dataOut = 0;
  for (i = 0; i < testDataSize; i++) {
    int newData = rand() % MAX_INT_VALUE;

    dataPtr = myLL->replace(myLL, &newData, i, &status);
    ck_assert_int_eq(status, OK);
    ck_assert_ptr_nonnull(dataPtr);

    dataOut = *(int*)dataPtr;
    ck_assert_int_eq(dataOut, testData[i]);

    dataPtr = myLL->at(myLL, i, &status);
    ck_assert_ptr_nonnull(dataPtr);
    
    dataOut = *(int*)dataPtr;
    ck_assert_int_eq(dataOut, newData);
  }

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE REPLACE END */

/**************************************************/

/* TEST CASE POP START */

START_TEST(pop_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  void* dataPtr = myLL->pop(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(pop) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++)
    myLL->append(myLL, &testData[i], &status);

  void* dataPtr = NULL;
  int dataOut = 0;
  for (i = 0; i < testDataSize; i++) {
    dataPtr = myLL->pop(myLL, &status);
    ck_assert_int_eq(status, OK);
    ck_assert_ptr_nonnull(dataPtr);

    dataOut = *(int*)dataPtr;
    ck_assert_int_eq(dataOut, testData[i]);
  }

  int empty = myLL->empty(myLL, &status);
  ck_assert_int_eq(empty, 1);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE POP END */

/**************************************************/

/* TEST CASE PULL START */

START_TEST(pull_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  void* dataPtr = myLL->pull(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(pull) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++)
    myLL->prepend(myLL, &testData[i], &status);

  void* dataPtr = NULL;
  int dataOut = 0;
  for (i = 0; i < testDataSize; i++) {
    dataPtr = myLL->pull(myLL, &status);
    ck_assert_int_eq(status, OK);
    ck_assert_ptr_nonnull(dataPtr);

    dataOut = *(int*)dataPtr;
    ck_assert_int_eq(dataOut, testData[i]);
  }

  int empty = myLL->empty(myLL, &status);
  ck_assert_int_eq(empty, 1);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE PULL END */

/**************************************************/

/* TEST CASE REMOVE START */

START_TEST(remove_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  void* dataPtr = NULL;

  dataPtr = myLL->remove(NULL, 0, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->remove(myLL, -1, &status);
  ck_assert_int_eq(status, LESS_THAN_INDEX);
  ck_assert_ptr_null(dataPtr);

  dataPtr = myLL->remove(myLL, 0, &status);
  ck_assert_int_eq(status, GREATER_THAN_INDEX);
  ck_assert_ptr_null(dataPtr);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(remove) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++)
    myLL->append(myLL, &testData[i], &status);

  int index = 0;
  void* dataPtr = NULL;
  int initData = 0;
  int dataOut = 0;;
  for (i = 0; i < testDataSize; i++) {
    index = rand() % myLL->length(myLL, &status);
    initData = *(int*)myLL->at(myLL, index, &status);

    dataPtr = myLL->remove(myLL, index, &status);
    ck_assert_int_eq(status, OK);
    ck_assert_ptr_nonnull(dataPtr);

    dataOut = *(int*)dataPtr;
    ck_assert_int_eq(dataOut, initData);
  }

  int empty = myLL->empty(myLL, &status);
  ck_assert_int_eq(empty, 1);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE REMOVE END */

/**************************************************/

/* TEST CASE CLEAR START */

START_TEST(clear_invalid_params) {
  LDSC_error status = OK;
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);

  myLL->clear(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST


START_TEST(clear) {
  LDSC_error status = OK;
  typedef struct privateData {
    int length;
    void* head;
    void* tail;
  } privateData;
  
  LDSC_linkedList* myLL = LDSC_linkedList_init(&status);
  const int testDataSize = rand() % MAX_DATA_SET_SIZE;
  int testData[testDataSize];

  int i = 0;
  for (i = 0; i < testDataSize; i++)
    testData[i] = rand() % MAX_INT_VALUE;

  for (i = 0; i < testDataSize; i++)
    myLL->append(myLL, &testData[i], &status);

  myLL->clear(myLL, &status);
  ck_assert_int_eq(status, OK);
  
  int empty = myLL->empty(myLL, &status);
  ck_assert_int_eq(empty, 1);

  privateData* pd = (privateData*)myLL->pd;
  ck_assert_ptr_null(pd->head);
  ck_assert_ptr_null(pd->tail);

  myLL->delete(myLL, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE CLEAR END */

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

  TCase* tc_at = tcase_create("at");
  tcase_add_test(tc_at, at_invalid_params);
  tcase_add_test(tc_at, at);
  suite_add_tcase(s, tc_at);

  TCase* tc_replace = tcase_create("replace");
  tcase_add_test(tc_replace, replace_invalid_params);
  tcase_add_test(tc_replace, replace);
  suite_add_tcase(s, tc_replace);

  TCase* tc_pop = tcase_create("pop");
  tcase_add_test(tc_pop, pop_invalid_params);
  tcase_add_test(tc_pop, pop);
  suite_add_tcase(s, tc_pop);

  TCase* tc_pull = tcase_create("pull");
  tcase_add_test(tc_pull, pull_invalid_params);
  tcase_add_test(tc_pull, pull);
  suite_add_tcase(s, tc_pull);

  TCase* tc_remove = tcase_create("remove");
  tcase_add_test(tc_remove, remove_invalid_params);
  tcase_add_test(tc_remove, remove);
  suite_add_tcase(s, tc_remove);

  TCase* tc_clear = tcase_create("clear");
  tcase_add_test(tc_clear, clear_invalid_params);
  tcase_add_test(tc_clear, clear);
  suite_add_tcase(s, tc_clear );

  return s;
}

