#include <check.h>
#include <LDSC.h>
#include <stdlib.h>

/* Example of setting up a set for a method called LDSC_add(int, int)
START_TEST(test_add) {
  int testCount = 1;
  struct {
    int x;
    int y;
    int result;
  } tests[] = {
    {4, 5, 9}
  };
  int result;
  for (int i = 0; i < testCount; i++) {
    result = LDSC_add(tests[i].x, tests[i].y);
    ck_assert_int_eq(tests[i].result, result);
  }
} END_TEST
*/

Suite *LDS_suite() {
  Suite *s;
  TCase *tc_core;
  s = suite_create("LDSC");
  tc_core = tcase_create("Core");

  suite_add_tcase(s, tc_core);
  //tcase_add_test(tc_core, test_add); // example of adding a test
  
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

