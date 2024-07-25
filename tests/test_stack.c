#include <stdlib.h>

#include "test_stack.h"
#include <LDSC.h>
#include <check.h>

/**************************************************/

/* TEST CASE CORE START */

START_TEST(initialization) {
  typedef struct stackPrivate {
    int size;
    void* top;
  } stackPrivate;

  LDSC_stack* myStack = LDSC_stack_init();  
  ck_assert_ptr_nonnull(myStack);

  stackPrivate* pd = (stackPrivate*)myStack->pd;
  ck_assert_ptr_nonnull(pd);
  ck_assert_int_eq(pd->size, 0);
  ck_assert_ptr_null(pd->top);

  myStack->delete(myStack);
} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* TEST CASE SIZE START */

START_TEST(size_invalid_params) {
  LDSC_stack* myStack = LDSC_stack_init();
  int size = myStack->size(NULL);
  ck_assert_int_eq(size, -1);
  myStack->delete(myStack);
}

START_TEST(size_empty_stack) {
  LDSC_stack* myStack = LDSC_stack_init();
  int size = myStack->size(myStack);
  ck_assert_int_eq(size, 0);
  myStack->delete(myStack);
} END_TEST

/* TEST CASE SIZE END */

/**************************************************/

/* TEST CASE PUSH START */

START_TEST(push_invalid_params) {
  LDSC_stack* myStack = LDSC_stack_init();
  int testData = 17;
  myStack->push(NULL, NULL);
  myStack->push(myStack, NULL);
  myStack->push(NULL, &testData);
  int size = myStack->size(myStack);
  ck_assert_int_eq(size, 0);
  myStack->delete(myStack);
}

START_TEST(push) {
  LDSC_stack* myStack = LDSC_stack_init();
  int testData[] = {17, 9, 19};
  for (int i = 0; i < 3 ; i++)
    myStack->push(myStack, &testData[i]);
  int size = myStack->size(myStack);
  ck_assert_int_eq(size, 3);
  myStack->delete(myStack);
} END_TEST

/* TEST CASE PUSH END */

/**************************************************/

/* TEST CASE ISEMPTY START */

START_TEST(isEmpty_invalid_params) {
  LDSC_stack* myStack = LDSC_stack_init();
  int isEmpty = myStack->isEmpty(NULL);
  ck_assert_int_eq(isEmpty, -1);
  myStack->delete(myStack);
} END_TEST

START_TEST(isEmpty) {
  LDSC_stack* myStack = LDSC_stack_init();
  int isEmpty;

  isEmpty = myStack->isEmpty(myStack);
  ck_assert_int_eq(isEmpty, 1);

  int testData = 17;
  myStack->push(myStack, &testData);
  isEmpty = myStack->isEmpty(myStack);
  ck_assert_int_eq(isEmpty, 0);
  myStack->delete(myStack);
}

/* TEST CASE ISEMPTY END */

/**************************************************/

/* TEST CASE PEEK START */

START_TEST(peek_invalid_params) {
  LDSC_stack* myStack = LDSC_stack_init();
  void* dataPtr = myStack->peek(NULL);
  ck_assert_ptr_null(dataPtr);
  myStack->delete(myStack);
} END_TEST;

START_TEST(peek) {
  LDSC_stack* myStack = LDSC_stack_init();
  void* dataPtr;

  dataPtr = myStack->peek(myStack);
  ck_assert_ptr_null(dataPtr);

  int testData = 17;
  myStack->push(myStack, &testData);
  dataPtr = myStack->peek(myStack);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  myStack->delete(myStack);
} END_TEST;

/* TEST CASE PEEK END */

/**************************************************/

/* TEST CASE POP START */

START_TEST(pop_invalid_params) {
  LDSC_stack* myStack = LDSC_stack_init();
  void* dataPtr = myStack->pop(NULL);
  ck_assert_ptr_null(dataPtr);
  myStack->delete(myStack);
} END_TEST

START_TEST(pop) {
  LDSC_stack* myStack = LDSC_stack_init();
  void* dataPtr;

  dataPtr = myStack->pop(myStack);
  ck_assert_ptr_null(dataPtr);

  int testData = 17;
  myStack->push(myStack, &testData);
  dataPtr = myStack->pop(myStack);
  ck_assert_ptr_nonnull(dataPtr);
  ck_assert_int_eq(*(int*)dataPtr, testData);

  int size = myStack->size(myStack);
  ck_assert_int_eq(size, 0);

  myStack->delete(myStack);
} END_TEST

/* TEST CASE POP END */

/**************************************************/

/* TEST CASE INTEGRATION START */

#include <stdio.h>
START_TEST(integration) {
  LDSC_stack* myStack = LDSC_stack_init();

  int testData[] = {17, 9, 19}; 
  int i;
  for (i = 0; i < 3; i++)
    myStack->push(myStack, &testData[i]);

  int size = myStack->size(myStack);
  ck_assert_int_eq(size, 3);

  void* dataPtr;
  i = 2;
  while (!myStack->isEmpty(myStack)) {
    dataPtr = myStack->pop(myStack);
    ck_assert_int_eq(*(int*)dataPtr, testData[i]);
    i--;
  }

  size = myStack->size(myStack);
  ck_assert_int_eq(size, 0);

  int testDataMore[] = {23, 11};
  myStack->push(myStack, &testDataMore[0]);

  if (!myStack->isEmpty(myStack)) 
    myStack->push(myStack, &testDataMore[1]);

  size = myStack->size(myStack);
  ck_assert_int_eq(size, 2);
  
  myStack->delete(myStack);
} END_TEST 

/* TEST CASE INTEGRATION END */

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

  TCase* tc_isEmpty = tcase_create("isEmpty");
  tcase_add_test(tc_isEmpty, isEmpty_invalid_params);
  tcase_add_test(tc_isEmpty, isEmpty);
  suite_add_tcase(s, tc_isEmpty);

  TCase* tc_peek = tcase_create("peek");
  tcase_add_test(tc_peek, peek_invalid_params);
  tcase_add_test(tc_peek, peek);
  suite_add_tcase(s, tc_peek);

  TCase* tc_pop = tcase_create("pop");
  tcase_add_test(tc_pop, pop_invalid_params);
  tcase_add_test(tc_pop, pop);
  suite_add_tcase(s, tc_pop);

  TCase* tc_integration = tcase_create("integration");
  tcase_add_test(tc_integration , integration);
  suite_add_tcase(s, tc_integration);

  return s;
}
