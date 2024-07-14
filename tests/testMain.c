#include <check.h>
#include <LDSC.h>
#include <stdlib.h>
#include <stdio.h>

/* Example of setting up a set for a method called LDSC_add(int, int)
START_TEST(test_add) {
  int testCount = 3;
  struct {
    int x;
    int y;
    int result;
  } tests[] = {
    {4, 5, 9},
    {-1, 5, 4},
    {-19, -8, -27}
  };
  int result;
  for (int i = 0; i < testCount; i++) {
    result = LDSC_add(tests[i].x, tests[i].y); // method
    ck_assert_int_eq(tests[i].result, result);
  }
} END_TEST
*/

START_TEST(linkedList_init) {
  LDSC_linkedList* myLL = LDSC_linkedList_init();

  int length = LDSC_linkedList_length(myLL);
  LDSC_node* head = LDSC_linkedList_head(myLL);
  LDSC_node* tail = LDSC_linkedList_tail(myLL);

  ck_assert_int_eq(length, 0);
  ck_assert_ptr_eq(head, NULL);
  ck_assert_ptr_eq(tail, NULL);

} END_TEST

Suite *LDS_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("LDSC");
  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);
  //tcase_add_test(tc_core, test_add); // example of adding a test
  tcase_add_test(tc_core, linkedList_init); 
  
  return s;
}

int main() {
  int numberFailed;
  Suite *s;
  SRunner *sr;
  
  s = LDS_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  numberFailed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (numberFailed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

