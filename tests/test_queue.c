#include <stdlib.h>

#include "test_queue.h"
#include "LDSC_queue.h"
#include <LDSC.h>
#include <check.h>

/**************************************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  typedef struct privateData {
    int size;
    void* front;
    void* back;
  } privateData;

  LDSC_queue* myQueue = LDSC_queue_init();
  ck_assert_ptr_nonnull(myQueue);

  privateData* pd = (privateData*)myQueue->pd;
  ck_assert_int_eq(pd->size, 0);
  ck_assert_ptr_null(pd->front);
  ck_assert_ptr_null(pd->back);

  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE EMPTY START */

START_TEST(empty_invalid_params) {
  LDSC_queue* myQueue = LDSC_queue_init();
  int empty = myQueue->empty(NULL);
  ck_assert_int_eq(empty, -1);
  myQueue->delete(myQueue);
} END_TEST

START_TEST(empty) {
  LDSC_queue* myQueue = LDSC_queue_init();
  int empty = myQueue->empty(myQueue);
  ck_assert_int_eq(empty, 1);
  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE EMPTY END */

/**************************************************/

/* TEST CASE LENGTH START */

START_TEST(length_invalid_params) {
  LDSC_queue* myQueue = LDSC_queue_init();
  int length = myQueue->length(NULL);
  ck_assert_int_eq(length, -1);
  myQueue->delete(myQueue);
} END_TEST

START_TEST(length) {
  LDSC_queue* myQueue = LDSC_queue_init();
  int length = myQueue->length(myQueue);
  ck_assert_int_eq(length, 0);
  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE LENGTH START */

/**************************************************/

/* TEST CASE ENQUEUE START */

START_TEST(enqueue_invalid_params) {
  LDSC_queue* myQueue = LDSC_queue_init();
  int testData = 17;
  myQueue->enqueue(NULL, NULL);
  myQueue->enqueue(myQueue, NULL);
  myQueue->enqueue(NULL, &testData);
  int empty = myQueue->empty(myQueue);
  ck_assert_int_eq(empty, 1);
  myQueue->delete(myQueue);
} END_TEST

START_TEST(enqueue) {
  LDSC_queue* myQueue = LDSC_queue_init();
  int testData[] = {17, 9, 19};
  for (int i = 0; i < 3; i++)
    myQueue->enqueue(myQueue, &testData[i]);

  int empty = myQueue->empty(myQueue);
  int length = myQueue->length(myQueue);
  ck_assert_int_eq(empty, 0);
  ck_assert_int_eq(length, 3);

  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE ENQUEUE END */

/**************************************************/

/* TEST CASE DEQUEUE START */

START_TEST(dequeue_invalid_params) {
  LDSC_queue* myQueue = LDSC_queue_init();
  void* dataPtr = myQueue->dequeue(NULL);
  int length = myQueue->length(myQueue);
  ck_assert_ptr_null(dataPtr);
  ck_assert_int_eq(length, 0);
  myQueue->delete(myQueue);
} END_TEST

START_TEST(dequeue) {
  LDSC_queue* myQueue = LDSC_queue_init();

  void* dataPtr = myQueue->dequeue(myQueue);
  int length = myQueue->length(myQueue);
  ck_assert_ptr_null(dataPtr);
  ck_assert_int_eq(length, 0);

  int testData = 17;
  myQueue->enqueue(myQueue, &testData);
  dataPtr = myQueue->dequeue(myQueue);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE DEQUEUE END */

/**************************************************/

/* TEST CASE PEEK START */

START_TEST(peek_invalid_params) {
  LDSC_queue* myQueue = LDSC_queue_init();
  void* dataPtr = myQueue->peek(NULL);
  ck_assert_ptr_null(dataPtr);
  myQueue->delete(myQueue);
} END_TEST

START_TEST(peek) {
  LDSC_queue* myQueue = LDSC_queue_init();

  void* dataPtr = myQueue->peek(myQueue);
  ck_assert_ptr_null(dataPtr);

  int testData = 17;
  myQueue->enqueue(myQueue, &testData);

  dataPtr = myQueue->peek(myQueue);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE PEEK END */

/**************************************************/

/* TEST CASE INTEGRATION START */

START_TEST(integration) {
  LDSC_queue* myQueue = LDSC_queue_init();

  int empty = myQueue->empty(myQueue);
  ck_assert_int_eq(empty, 1);

  int i;
  int testData[] = {17, 9, 19};
  for (i = 0; i < 3; i++)
    myQueue->enqueue(myQueue, &testData[i]);

  void* dataPtr;

  i = 0;
  while (!myQueue->empty(myQueue)) {
    dataPtr = myQueue->dequeue(myQueue);
    ck_assert_int_eq(*(int*)dataPtr, testData[i]);
    i++;
  }

  myQueue->delete(myQueue);
} END_TEST

/* TEST CASE INTEGRATION END */

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

  TCase* tc_integration = tcase_create("integration");
  tcase_add_test(tc_integration, integration);
  suite_add_tcase(s, tc_integration);

  return s;
}
