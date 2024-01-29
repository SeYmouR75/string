#include "s21_test_string.h"

#define ACTUAL(x, y, z) s21_memset(x, y, z)
#define EXPECTED(x, y, z) memset(x, y, z)

#define SUITE_LABEL "suite_s21_memset"
#define SUITE_NAME suite_s21_memset

START_TEST(s21_memset_01) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = '*';
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_02) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = 42;
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_03) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = '*';
  s21_size_t n = 1;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_04) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = 42;
  s21_size_t n = 1;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_05) {
  char str[] = "";
  char str2[] = "";
  char c = '*';
  s21_size_t n = 0;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_06) {
  char str[] = "";
  char str2[] = "";
  char c = 42;
  s21_size_t n = 0;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_07) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = '\0';
  s21_size_t n = 1;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_08) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = '\0';
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_09) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = '\0';
  s21_size_t n = s21_strlen(str) + 1;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memset_10) {
  char str[] = "s21_Hello, world!";
  char str2[] = "s21_Hello, world!";
  char c = '\0';
  s21_size_t n = 10;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str2, c, n);
  ck_assert_str_eq(actual_result, expected_result);
}
END_TEST

Suite* SUITE_NAME(void) {
  Suite* suite = suite_create(SUITE_LABEL);
  TCase* tcase = tcase_create("case");
  tcase_add_test(tcase, s21_memset_01);
  tcase_add_test(tcase, s21_memset_02);
  tcase_add_test(tcase, s21_memset_03);
  tcase_add_test(tcase, s21_memset_04);
  tcase_add_test(tcase, s21_memset_05);
  tcase_add_test(tcase, s21_memset_06);
  tcase_add_test(tcase, s21_memset_07);
  tcase_add_test(tcase, s21_memset_08);
  tcase_add_test(tcase, s21_memset_09);
  tcase_add_test(tcase, s21_memset_10);
  suite_add_tcase(suite, tcase);
  return suite;
}
