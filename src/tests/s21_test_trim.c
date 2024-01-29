#include "s21_test_string.h"

#define SUITE_LABEL "suite_s21_trim"
#define SUITE_NAME *suite_s21_trim()

START_TEST(test) {
  // TEST 1.
  char *str1 = "WoW, I love it!";
  char *ptr1 = "W";
  char *res1 = (char *)s21_trim(str1, ptr1);
  //	printf("%s\n", res1);
  ck_assert_pstr_eq(res1, "oW, I love it!");
  if (res1) free(res1);
  // TEST 2.
  char *str2 = "WoW\0, I love it!";
  char *ptr2 = "W";
  char *res2 = (char *)s21_trim(str2, ptr2);
  //	printf("%s\n", res2);
  ck_assert_pstr_eq(res2, "o");
  if (res2) free(res2);
  // TEST 3.
  char *str3 = "WoW, I love it!";
  char *ptr3 = "P";
  char *res3 = (char *)s21_trim(str3, ptr3);
  //	printf("%s\n", res3);
  ck_assert_pstr_eq(res3, "WoW, I love it!");
  if (res3) free(res3);
  // TEST 4.
  char *str4 = "abc";
  char *ptr4 = "abc";
  char *res4 = (char *)s21_trim(str4, ptr4);
  //	printf("%s\n", res4);
  ck_assert_pstr_eq(res4, "");
  if (res4) free(res4);
  // TEST 5.
  char *str5 = "     HELLO    ";
  char *ptr5 = " ";
  char *res5 = (char *)s21_trim(str5, ptr5);
  //	printf("%s\n", res5);
  ck_assert_pstr_eq(res5, "HELLO");
  if (res5) free(res5);
  // TEST 6.

  char *str6 = "abc";
  char *ptr6 = "";
  char *res6 = (char *)s21_trim(str6, ptr6);
  //	printf("%s\n", res6);
  ck_assert_pstr_eq(res6, "abc");
  if (res6) free(res6);
  // TEST 7.

  char *str7 = "";
  char *ptr7 = "abc";
  char *res7 = (char *)s21_trim(str7, ptr7);
  //	printf("%s\n", res7);
  ck_assert_pstr_eq(res7, "");
  if (res7) free(res7);
  // TEST 8.

  char *str8 = S21_NULL;
  char *ptr8 = "abc";
  char *res8 = (char *)s21_trim(str8, ptr8);
  ck_assert_pstr_eq(res8, S21_NULL);
  if (res8) free(res8);
  // TEST 9.
  char *str9 = "abc";
  char *ptr9 = S21_NULL;
  char *res9 = (char *)s21_trim(str9, ptr9);
  ck_assert_pstr_eq(res9, S21_NULL);
  if (res9) free(res9);
}

END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_test(tcase, test);
  suite_add_tcase(suite, tcase);

  return suite;
}
