#include <stdlib.h>

#include "LDSC_stack.h"
#include "test_stack.h"
#include <check.h>

/**
 * Test suite for LDSC_stack data structure.
 * Only the 'initialization' test will check for possible malloc errors.
 * All following tests will assume successful mallocs.
 * All tests will test for successful LDSC_stack delete.
 * All status checks will occur before value checks, if applicable.
 * Beyond that, status checks will only occur the methods that the test targets
 */

/**************************************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  typedef struct privateData {
    int size;
    void* top;
  } privateData;

  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(myStack);

  privateData* pd = (privateData*)myStack->pd;
  ck_assert_ptr_nonnull(pd);
  ck_assert_int_eq(pd->size, 0);
  ck_assert_ptr_null(pd->top);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE SIZE START */

START_TEST(size_invalid_params) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);

  int size = myStack->size(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_int_eq(size, ERROR);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
}

START_TEST(size_empty_stack) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);

  int size = myStack->size(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(size, 0);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE SIZE END */

/**************************************************/

/* TEST CASE PUSH START */

START_TEST(push_invalid_params) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);
  int testData = 17;

  myStack->push(NULL, NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);

  myStack->push(myStack, NULL, &status);
  ck_assert_int_eq(status, NULL_DATAPTR);

  myStack->push(NULL, &testData, &status);
  ck_assert_int_eq(status, NULL_SELF);
  
  int size = myStack->size(myStack, &status);
  ck_assert_int_eq(size, 0);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
}

START_TEST(push) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);
  int testData[] = {17, 9, 19};

  for (int i = 0; i < 3 ; i++) {
    myStack->push(myStack, &testData[i], &status);
    ck_assert_int_eq(status, OK);
  }

  int size = myStack->size(myStack, &status);
  ck_assert_int_eq(size, 3);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE PUSH END */

/**************************************************/

/* TEST CASE EMPTY START */

START_TEST(empty_invalid_params) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);

  int isEmpty = myStack->empty(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_int_eq(isEmpty, ERROR);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(empty) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);
  int isEmpty;

  isEmpty = myStack->empty(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(isEmpty, 1);

  int testData = 17;
  myStack->push(myStack, &testData, &status);

  isEmpty = myStack->empty(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(isEmpty, 0);
 
  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
}

/* TEST CASE ISEMPTY END */

/**************************************************/

/* TEST CASE PEEK START */

START_TEST(peek_invalid_params) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);

  void* dataPtr = myStack->peek(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(peek) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);
  int testData = 17;
  void* dataPtr;

  dataPtr = myStack->peek(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_null(dataPtr);

  myStack->push(myStack, &testData, &status);
  
  dataPtr = myStack->peek(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE PEEK END */

/**************************************************/

/* TEST CASE POP START */

START_TEST(pop_invalid_params) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);

  void* dataPtr = myStack->pop(NULL, &status);
  ck_assert_int_eq(status, NULL_SELF);
  ck_assert_ptr_null(dataPtr);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

START_TEST(pop) {
  LDSC_error status = OK;
  LDSC_stack* myStack = LDSC_stack_init(&status);
  int testData = 17;
  void* dataPtr;

  dataPtr = myStack->pop(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_null(dataPtr);

  myStack->push(myStack, &testData, &status);
  
  dataPtr = myStack->pop(myStack, &status);
  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  int size = myStack->size(myStack, &status);
  ck_assert_int_eq(size, 0);

  myStack->delete(myStack, &status);
  ck_assert_int_eq(status, OK);
} END_TEST

/* TEST CASE POP END */

/**************************************************/

/* SUITE DEFINITION */

Suite* LDSC_stack_suite(void) {
  Suite *s;
  s = suite_create("LDSC_stack");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(s, tc_core);

  TCase* tc_size = tcase_create("sizej");
  tcase_add_test(tc_size, size_invalid_params);
  tcase_add_test(tc_size, size_empty_stack);
  suite_add_tcase(s, tc_size);

  TCase* tc_push = tcase_create("push");
  tcase_add_test(tc_push, push_invalid_params);
  tcase_add_test(tc_push, push);
  suite_add_tcase(s, tc_push);

  TCase* tc_empty = tcase_create("empty");
  tcase_add_test(tc_empty, empty_invalid_params);
  tcase_add_test(tc_empty, empty);
  suite_add_tcase(s, tc_empty);

  TCase* tc_peek = tcase_create("peek");
  tcase_add_test(tc_peek, peek_invalid_params);
  tcase_add_test(tc_peek, peek);
  suite_add_tcase(s, tc_peek);

  TCase* tc_pop = tcase_create("pop");
  tcase_add_test(tc_pop, pop_invalid_params);
  tcase_add_test(tc_pop, pop);
  suite_add_tcase(s, tc_pop);

  return s;
}
