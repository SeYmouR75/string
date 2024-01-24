#include "s21_test_string.h"

#define ACTUAL(x, y, z) s21_memchr(x, y, z)
#define EXPECTED(x, y, z) memchr(x, y, z)

#define SUITE_LABEL "suite_s21_memchr"
#define SUITE_NAME suite_s21_memchr



START_TEST(s21_memchr_01) {
  char str[] = "s21_Hello, world!";
  int c = ',';
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memchr_02) {
  char str[] = "s21_Hello, world!";
  int c = '?';
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);

}
END_TEST

START_TEST(s21_memchr_03) {
  char str[] = "s21_Hello, world!";
  int c = 1;
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memchr_04) {
  char str[] = "s21_Hello, world!";
  int c = 72;
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memchr_05) {
  char str[] = "s21_Hello, world!";
  int c = 'd';
  s21_size_t n = 10;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memchr_06) {
  char str[] = "s21_Hello, world!";
  int c = 'o';
  s21_size_t n = 10;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memchr_07) {
  char str[] = "s21_Hello, world!";
  int c = '2';
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);
}
END_TEST

START_TEST(s21_memchr_08) {
  char str[] = "s21_Hello, world!";
  int c = '1';
  s21_size_t n = 0;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);

}
END_TEST

START_TEST(s21_memchr_09) {
  char str[] = "s21_Hello, world!";
  int c = '\0';
  s21_size_t n = s21_strlen(str);
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);

}
END_TEST

START_TEST(s21_memchr_10) {
  char str[] = "s21_Hello, world!";
  int c = 0;
  s21_size_t n = 0;
  void* actual_result = ACTUAL(str, c, n);
  void* expected_result = EXPECTED(str, c, n);
  ck_assert_ptr_eq(actual_result, expected_result);

}
END_TEST

Suite *SUITE_NAME(void) {
    Suite *suite = suite_create(SUITE_LABEL);
    TCase *tcase = tcase_create("case");


  //suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, s21_memchr_01);
  tcase_add_test(tcase, s21_memchr_02);
  tcase_add_test(tcase, s21_memchr_03);
  tcase_add_test(tcase, s21_memchr_04);
  tcase_add_test(tcase, s21_memchr_05);
  tcase_add_test(tcase, s21_memchr_06);
  tcase_add_test(tcase, s21_memchr_07);
  tcase_add_test(tcase, s21_memchr_08);
  tcase_add_test(tcase, s21_memchr_09);
  tcase_add_test(tcase, s21_memchr_10);

  suite_add_tcase(suite, tcase);
  return suite;
}
