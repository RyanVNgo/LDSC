#include <stdlib.h>

#include "LDSC_linkedList.h"
#include "test_linkedLists.h"
#include <check.h>

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

} END_TEST

/* TEST CASE CORE END */

/**************************************************/

/* SUITE DEFINITION */

Suite* LDSC_linkedList_suite() {
  Suite *s;
  s = suite_create("LDSC_linkedList");

  TCase* tc_core = tcase_create("core");
  tcase_add_test(tc_core, initialization);
  suite_add_tcase(s, tc_core);

  TCase* tc_append= tcase_create("append");
  suite_add_tcase(s, tc_append);

  TCase* tc_prepend = tcase_create("prepend");
  suite_add_tcase(s, tc_prepend);

  TCase* tc_get = tcase_create("get");
  suite_add_tcase(s, tc_get);

  TCase* tc_insert = tcase_create("insert");
  suite_add_tcase(s, tc_insert);

  TCase* tc_removeFirst = tcase_create("removeFirst");
  suite_add_tcase(s, tc_removeFirst);

  TCase* tc_removeLast = tcase_create("removeLast");
  suite_add_tcase(s, tc_removeLast);

  TCase* tc_remove = tcase_create("remove");
  suite_add_tcase(s, tc_remove);

  TCase* tc_integration = tcase_create("integration");
  suite_add_tcase(s, tc_integration);

  return s;
}

