#include <stdlib.h>

#include "test_linkedLists.h"
#include <LDSC.h>
#include <check.h>

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

START_TEST(linkedList_insert) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();
  int data = 17;
  LDSC_linkedList_insert(myLL, (void*)&data);

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);
  int dataOutHead = *(int*)LDSC_node_dataPtr(head);
  int dataOutTail = *(int*)LDSC_node_dataPtr(tail);

  ck_assert_int_eq(length, 1);
  ck_assert_ptr_ne(head, NULL);
  ck_assert_ptr_ne(tail, NULL);
  ck_assert_ptr_eq(head, tail);

  ck_assert_int_eq(dataOutHead, data);
  ck_assert_int_eq(dataOutTail, data);
  ck_assert_int_eq(dataOutHead, dataOutTail);

} END_TEST

Suite* LDSC_linkedList_suite() {
  Suite *s;
  TCase *tc_core;

  s = suite_create("LDSC_linkedList");
  tc_core = tcase_create("Core");

  tcase_add_test(tc_core, linkedList_init);
  tcase_add_test(tc_core, linkedList_insert);
  suite_add_tcase(s, tc_core);

  return s;
}
