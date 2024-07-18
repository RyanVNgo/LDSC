#include <stdlib.h>

#include "test_queue.h"
#include <LDSC.h>
#include <check.h>

// SUITE DEFINITION

Suite* LDSC_queue_suite() {
  Suite *s;
  s = suite_create("LDSC_queue");

  TCase* tc_core = tcase_create("core");
  suite_add_tcase(s, tc_core);

  return s;
}
