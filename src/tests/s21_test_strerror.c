#include <string.h>

#include "s21_test_string.h"

#define ACTUAL(x) s21_strerror(x)
#define EXPECTED(x) strerror(x)
#define SUITE_LABEL "suite_s21_strerror"
#define SUITE_NAME *suite_s21_strerror()

START_TEST(test) {
  for (int i = -1; i < 134; i++) {
    ck_assert_str_eq(ACTUAL(i), EXPECTED(i));
  }
}
END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_test(tcase, test);
  suite_add_tcase(suite, tcase);

  return suite;
}
