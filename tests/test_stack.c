#include <stdlib.h>

#include "test_stack.h"
#include <LDSC.h>
#include <check.h>

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE CORE START

START_TEST(stack_core) {
  LDSC_stack* myStack = LDSC_stack_init();
  ck_assert_ptr_nonnull(myStack);
} END_TEST

// TEST CASE CORE END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE LENGTH START

START_TEST(stack_length_null_stack) {
  // function should return -1 for error
  int length = LDSC_stack_length(NULL);
  ck_assert_int_eq(length, -1);
} END_TEST

START_TEST(stack_length) {
  LDSC_stack* myStack = LDSC_stack_init();

  // function should return 0 for an empty stack
  int length = LDSC_stack_length(myStack);
  ck_assert_int_eq(length, 0);

  free(myStack);
}

// TEST CASE LENGTH END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PUSH START

START_TEST(stack_push_null_stack) {
  int testData = 17;
  LDSC_stack_push(NULL, (void*)&testData);
} END_TEST

START_TEST(stack_push_null_data) {
  LDSC_stack* myStack = LDSC_stack_init();
  
  // attempt push
  LDSC_stack_push(myStack, NULL);

  // length of stack should be 0
  int length = LDSC_stack_length(myStack);
  ck_assert_int_eq(length, 0);

  free(myStack);
} END_TEST

START_TEST(stack_push) {
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  LDSC_stack* myStack = LDSC_stack_init();
  for (int i = 0; i < testDataLength; i++)
    LDSC_stack_push(myStack, &testData[i]);

  // length of the stack should be equal to the number of item in testData
  int length = LDSC_stack_length(myStack);
  ck_assert_int_eq(length, testDataLength);
}

// TEST CASE PUSH END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE ISEMPTY START

START_TEST(stack_isEmpty_null_stack) {
  // function should return -1 for error
  int isEmpty = LDSC_stack_length(NULL);
  ck_assert_int_eq(isEmpty, -1);
} END_TEST

START_TEST(stack_isEmpty_non_empty_stack) {
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  LDSC_stack* myStack = LDSC_stack_init();
  for (int i = 0; i < testDataLength; i++)
    LDSC_stack_push(myStack, &testData[i]);

  // function should return 0 for a non empty stack
  int isEmpty = LDSC_stack_isEmpty(myStack);
  ck_assert_int_eq(isEmpty, 0);

  free(myStack);
} END_TEST

START_TEST(stack_isEmpty_empty_stack) {
  LDSC_stack* myStack = LDSC_stack_init();

  // function should return 1 for an empty stack
  int isEmpty = LDSC_stack_isEmpty(myStack);
  ck_assert_int_eq(isEmpty, 1);

  free(myStack);
}

// TEST CASE ISEMPTY END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE PEEK START

START_TEST(stack_peek_null_stack) {
  // function should return null
  void* dataOutPtr = LDSC_stack_peek(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

START_TEST(stack_peek) {
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  LDSC_stack* myStack = LDSC_stack_init();
  for (int i = 0; i < testDataLength; i++)
    LDSC_stack_push(myStack, &testData[i]);

  // function should return the data ptr containing int 19
  void* dataOutPtr = LDSC_stack_peek(myStack);
  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[testDataLength-1]);

  free(myStack);
} END_TEST

// TEST CASE PEEK END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// TEST CASE POP START

START_TEST(stack_pop_null_stack) {
  // peek should return null
  void* dataOutPtr = LDSC_stack_peek(NULL);
  ck_assert_ptr_null(dataOutPtr);
} END_TEST

START_TEST(stack_pop_empty_stack) {
  LDSC_stack* myStack = LDSC_stack_init();

  // peek should return null
  void* dataOutPtr = LDSC_stack_peek(myStack);
  ck_assert_ptr_null(dataOutPtr);

  free(myStack);
} END_TEST

START_TEST(stack_pop_non_empty_stack) {
  int testDataLength = 3;
  int testData[] = {17, 9, 19};
  LDSC_stack* myStack = LDSC_stack_init();
  for (int i = 0; i < testDataLength; i++)
    LDSC_stack_push(myStack, &testData[i]);

  // peek should return data ptr containing int 19
  void* dataOutPtr = LDSC_stack_pop(myStack);
  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[testDataLength-1]);

  // peek should return data ptr containing int 9
  dataOutPtr = LDSC_stack_peek(myStack);
  ck_assert_ptr_nonnull(dataOutPtr);
  ck_assert_int_eq(*(int*)dataOutPtr, testData[testDataLength-2]);

} END_TEST

// TEST CASE POP END

// - - - - - - - - - - - - - - - - - - - - - - - - -

// SUITE DEFINITION

Suite* LDSC_stack_suite(void) {
  Suite *s;
  s = suite_create("LDSC_stack");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, stack_core);
  suite_add_tcase(s, tc_core);

  TCase* tc_length = tcase_create("length");
  tcase_add_test(tc_length, stack_length_null_stack);
  tcase_add_test(tc_length, stack_length);
  suite_add_tcase(s, tc_length);

  TCase* tc_push = tcase_create("push");
  tcase_add_test(tc_push, stack_push_null_stack);
  tcase_add_test(tc_push, stack_push_null_data);
  tcase_add_test(tc_push, stack_push);
  suite_add_tcase(s, tc_push);

  TCase* tc_isEmpty = tcase_create("isEmpty");
  tcase_add_test(tc_isEmpty, stack_isEmpty_null_stack);
  tcase_add_test(tc_isEmpty, stack_isEmpty_non_empty_stack);
  tcase_add_test(tc_isEmpty, stack_isEmpty_empty_stack);
  suite_add_tcase(s, tc_isEmpty);

  TCase* tc_peek = tcase_create("peek");
  tcase_add_test(tc_peek, stack_peek_null_stack);
  tcase_add_test(tc_peek, stack_peek);
  suite_add_tcase(s, tc_peek);

  TCase* tc_pop = tcase_create("pop");
  tcase_add_test(tc_pop, stack_pop_null_stack);
  tcase_add_test(tc_pop, stack_pop_empty_stack);
  tcase_add_test(tc_pop, stack_pop_non_empty_stack);
  suite_add_tcase(s, tc_pop);

  return s;
}
