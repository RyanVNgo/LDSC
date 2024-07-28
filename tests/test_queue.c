#include <stdlib.h>

#include "LDSC_errors.h"
#include "LDSC_queue.h"
#include "test_queue.h"
#include <check.h>

/**
 * Test suite for LDSC_queue data structure.
 * Only the 'initialization' test will check for possible malloc errors.
 * All following tests will assume successful mallocs.
 * All tests will test for successful LDSC_queue delete.
 * All status checks will occur before value checks, if applicable.
 * Beyond that, status checks will only occur the methods that the test targets
 */

/**************************************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  LDSC_error status = OK;
  typedef struct privateData {
    int size;
    void* front;
    void* back;
  } privateData;

  LDSC_queue* myQueue = LDSC_queue_init(&status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(myQueue);
  
  privateData* pd = (privateData*)myQueue->pd;
  ck_assert_int_eq(pd->size, 0);
  ck_assert_ptr_null(pd->front);
  ck_assert_ptr_null(pd->back);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE EMPTY START */

START_TEST(empty_invalid_params) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);

  int empty = myQueue->empty(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_int_eq(empty, ERROR);

  myQueue->delete(myQueue, &status);
} END_TEST

START_TEST(empty) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);

  int empty = myQueue->empty(myQueue, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(empty, 1);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE EMPTY END */

/**************************************************/

/* TEST CASE LENGTH START */

START_TEST(length_invalid_params) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);

  int length = myQueue->length(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_int_eq(length, ERROR);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(length) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);

  int length = myQueue->length(myQueue, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(length, 0);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE LENGTH START */

/**************************************************/

/* TEST CASE ENQUEUE START */

START_TEST(enqueue_invalid_params) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);
  int testData = 17;

  myQueue->enqueue(NULL, NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
 
  myQueue->enqueue(myQueue, NULL, &status);
  ck_assert_int_eq(status, NULL_DATAPTR);
  
  myQueue->enqueue(NULL, &testData, &status);
  ck_assert_int_eq(status, NULL_SELF);

  int empty = myQueue->empty(myQueue, &status);
  ck_assert_int_eq(empty, 1);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(enqueue) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);
  int testData[] = {17, 9, 19};

  for (int i = 0; i < 3; i++) {
    myQueue->enqueue(myQueue, &testData[i], &status);
    ck_assert_int_eq(status, OK);
  }

  int empty = myQueue->empty(myQueue, &status);
  int length = myQueue->length(myQueue, &status);
  ck_assert_int_eq(empty, 0);
  ck_assert_int_eq(length, 3);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE ENQUEUE END */

/**************************************************/

/* TEST CASE DEQUEUE START */

START_TEST(dequeue_invalid_params) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);
  
  void* dataPtr = myQueue->dequeue(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);
  
  int length = myQueue->length(myQueue, &status);
  ck_assert_int_eq(length, 0);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(dequeue) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);
 
  void* dataPtr = myQueue->dequeue(myQueue, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_null(dataPtr);

  int length = myQueue->length(myQueue, &status);
  ck_assert_int_eq(length, 0);

  int testData = 17;
  myQueue->enqueue(myQueue, &testData, &status);

  dataPtr = myQueue->dequeue(myQueue, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE DEQUEUE END */

/**************************************************/

/* TEST CASE PEEK START */

START_TEST(peek_invalid_params) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);

  void* dataPtr = myQueue->peek(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(peek) {
  LDSC_error status = OK;
  LDSC_queue* myQueue = LDSC_queue_init(&status);

  void* dataPtr = myQueue->peek(myQueue, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_null(dataPtr);

  int testData = 17;
  myQueue->enqueue(myQueue, &testData, &status);

  dataPtr = myQueue->peek(myQueue, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  myQueue->delete(myQueue, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE PEEK END */

/**************************************************/

/* SUITE DEFINITION */

Suite* LDSC_queue_suite() {
  Suite *s;
  s = suite_create("LDSC_queue");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(s, tc_core);

  TCase* tc_empty = tcase_create("empty");
  tcase_add_test(tc_empty, empty_invalid_params);
  tcase_add_test(tc_empty, empty);
  suite_add_tcase(s, tc_empty);

  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, length_invalid_params);
  tcase_add_test(tc_length, length);
  suite_add_tcase(s, tc_length);

  TCase* tc_enqueue= tcase_create("enqueue");
  tcase_add_test(tc_enqueue, enqueue_invalid_params);
  tcase_add_test(tc_enqueue, enqueue);
  suite_add_tcase(s, tc_enqueue);

  TCase* tc_dequeue = tcase_create("dequeue");
  tcase_add_test(tc_dequeue, dequeue_invalid_params);
  tcase_add_test(tc_dequeue, dequeue);
  suite_add_tcase(s, tc_dequeue);

  TCase* tc_peek = tcase_create("peek");
  tcase_add_test(tc_peek, peek_invalid_params);
  tcase_add_test(tc_peek, peek);
  suite_add_tcase(s, tc_peek);

  return s;
}
