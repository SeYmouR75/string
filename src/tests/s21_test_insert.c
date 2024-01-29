#include "s21_test_string.h"

#define SUITE_LABEL "suite_s21_insert"
#define SUITE_NAME *suite_s21_insert()

char VALUES[][4][64] = {{"Aboba", "kek", "2", "Abkekoba"},
                        {"Aboba", "kek", "4", "Abobkeka"},
                        {"f", "k ek", "0", "k ekf"},
                        {"Aboba   ", "k ek", "0", "k ekAboba   "}};

START_TEST(test) {
  s21_size_t start_index;
  sscanf(VALUES[_i][2], "%lu", &start_index);
  char *result = s21_insert(VALUES[_i][0], VALUES[_i][1], start_index);
  ck_assert_pstr_eq(result, VALUES[_i][3]);
  if (result) free(result);
}
END_TEST

START_TEST(test1) {
  char *result = s21_insert("", "k ek", 0);
  ck_assert_pstr_eq(result, S21_NULL);
  if (result) free(result);
}
END_TEST

START_TEST(test2) {
  char *result = s21_insert(S21_NULL, "k ek", 0);
  ck_assert_pstr_eq(result, S21_NULL);
  if (result) free(result);
}
END_TEST

START_TEST(test3) {
  char *result = s21_insert("f", S21_NULL, 0);
  ck_assert_pstr_eq(result, S21_NULL);
  if (result) free(result);
}
END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_loop_test(tcase, test, 0, sizeof(VALUES) / sizeof(VALUES[0]));
  suite_add_tcase(suite, tcase);

  TCase *tcase1 = tcase_create("case1");
  tcase_add_test(tcase1, test1);
  suite_add_tcase(suite, tcase1);

  TCase *tcase2 = tcase_create("case2");
  tcase_add_test(tcase2, test2);
  suite_add_tcase(suite, tcase2);

  TCase *tcase3 = tcase_create("case3");
  tcase_add_test(tcase3, test3);
  suite_add_tcase(suite, tcase3);

  return suite;
}
