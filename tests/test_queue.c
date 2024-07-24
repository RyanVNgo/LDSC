#include <stdlib.h>

#include "test_queue.h"
#include "LDSC_queue.h"
#include <LDSC.h>
#include <check.h>

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE CORE START

START_TEST(queue_init) {
  // myQueue should be nonnull
  LDSC_queue* myQueue = LDSC_queue_init();
  ck_assert_ptr_nonnull(myQueue);
} END_TEST

// TEST CASE CORE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE LENGTH START

START_TEST(queue_length_null_queue) {
  // length should equal -1
  int length = LDSC_queue_length(NULL);
  ck_assert_int_eq(length, -1);
} END_TEST

START_TEST(queue_length_empty_queue) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // length should return 0 for an empty stack
  int length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, 0);

  free(myQueue);
} END_TEST

// TEST CASE LENGTH START

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE ENQUEUE START

START_TEST(queue_enqueue_null_queue) {
  // should return with no error
  int testData = 17;
  LDSC_queue_enqueue(NULL, &testData);
} END_TEST

START_TEST(queue_enqueue_null_data) {
  LDSC_queue* myQueue = LDSC_queue_init();
  LDSC_queue_enqueue(myQueue, NULL);

  // queue should remain empty (length of 0)
  int length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, 0);

  free(myQueue);
} END_TEST

START_TEST(queue_enqueue) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // fill queue
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < testDataLength; i++)
    LDSC_queue_enqueue(myQueue, &testData[i]);

  // length of queue should equal testDataLength
  int length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, testDataLength);
  
  free(myQueue);
} END_TEST

// TEST CASE ENQUEUE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE DEQUEUE START

START_TEST(queue_dequeue_null_queue) {
  // should return NULL for NULL queue
  void* dataOutPtr = LDSC_queue_dequeue(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

START_TEST(queue_dequeue_empty_queue) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // should return NULL for empty queue
  void* dataOutPtr = LDSC_queue_dequeue(myQueue);
  ck_assert_ptr_null(dataOutPtr);

  free(myQueue);
} END_TEST

START_TEST(queue_dequeue) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // fill queue
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < testDataLength; i++)
    LDSC_queue_enqueue(myQueue, &testData[i]);

  // should return nonnull ptr and equal to first item of testData
  void* dataOutPtr = LDSC_queue_dequeue(myQueue);
  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[0]);

  // length should return 1 less than testDataLength
  int length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, testDataLength - 1);

  free(myQueue);
} END_TEST

// TEST CASE DEQUEUE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PEEK START

START_TEST(queue_peek_null_queue) {
  // shoud return NULL for NULL queue
  void* dataOutPtr = LDSC_queue_peek(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

START_TEST(queue_peek_empty_queue) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // should return NULL for empty queue
  void* dataOutPtr = LDSC_queue_peek(myQueue);
  ck_assert_ptr_null(dataOutPtr);

  free(myQueue);
} END_TEST

START_TEST(queue_peek) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // fill queue
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < testDataLength; i++)
    LDSC_queue_enqueue(myQueue, &testData[i]);

  // should return nonnull ptr and equal to first item of testData
  void* dataOutPtr = LDSC_queue_peek(myQueue);
  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[0]);

  // length should equal testDataLength
  int length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, testDataLength);

  free(myQueue);
} END_TEST

// TEST CASE PEEK END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE INTEGRATION START

START_TEST(queue_integration) {
  LDSC_queue* myQueue = LDSC_queue_init();

  // fill queue
  void* dataOutPtr;
  int trackedLength = 0;
  int trackedHeadIndex = 0;

  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  for (int i = 0; i < testDataLength; i++) {
    LDSC_queue_enqueue(myQueue, &testData[i]);
    trackedLength++;
  }

  int length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, trackedLength);

  LDSC_queue_dequeue(myQueue);
  trackedLength--; trackedHeadIndex++;
  dataOutPtr = LDSC_queue_dequeue(myQueue);
  trackedLength--; trackedHeadIndex++;

  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[trackedHeadIndex - 1]);

  int testDataExtra = 21;
  LDSC_queue_enqueue(myQueue, &testDataExtra);
  trackedLength++;

  dataOutPtr = LDSC_queue_peek(myQueue);
  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[trackedHeadIndex]);

  length = LDSC_queue_length(myQueue);
  ck_assert_int_eq(length, trackedLength);

  free(myQueue);
} END_TEST

// TEST CASE INTEGRATION END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// SUITE DEFINITION

Suite* LDSC_queue_suite() {
  Suite *s;
  s = suite_create("LDSC_queue");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, queue_init);
  suite_add_tcase(s, tc_core);

  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, queue_length_null_queue);
  tcase_add_test(tc_length, queue_length_empty_queue);
  suite_add_tcase(s, tc_length);

  TCase* tc_enqueue= tcase_create("enqueue");
  tcase_add_test(tc_enqueue, queue_enqueue_null_queue);
  tcase_add_test(tc_enqueue, queue_enqueue_null_data);
  tcase_add_test(tc_enqueue, queue_enqueue);
  suite_add_tcase(s, tc_enqueue);

  TCase* tc_dequeue = tcase_create("dequeue");
  tcase_add_test(tc_dequeue, queue_dequeue_null_queue);
  tcase_add_test(tc_dequeue, queue_dequeue_empty_queue);
  tcase_add_test(tc_dequeue, queue_dequeue);
  suite_add_tcase(s, tc_dequeue);

  TCase* tc_peek = tcase_create("peek");
  tcase_add_test(tc_peek, queue_peek_null_queue);
  tcase_add_test(tc_peek, queue_peek_empty_queue);
  tcase_add_test(tc_peek, queue_peek);
  suite_add_tcase(s, tc_peek);

  TCase* tc_integration = tcase_create("integration");
  tcase_add_test(tc_integration, queue_integration);
  suite_add_tcase(s, tc_integration);

  return s;
}
