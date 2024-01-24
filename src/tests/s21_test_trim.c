#include "s21_test_string.h"


#define SUITE_LABEL "suite_s21_trim"
#define SUITE_NAME *suite_s21_trim()
                   

START_TEST(test) {
  // TEST 1.
  char *str1 = "WoW, I love it!";
  char *ptr1 = "W";
  char *res1 = (char *)s21_trim(str1, ptr1);
  ck_assert_str_eq(res1, "oW, I love it!");
  free(res1);
  // TEST 2.
  char *str2 = "WoW\0, I love it!";
  char *ptr2 = "W";
  char *res2 = (char *)s21_trim(str2, ptr2);
  ck_assert_str_eq(res2, "o");
  free(res2);
  // TEST 3.
  char *str3 = "WoW, I love it!";
  char *ptr3 = "P";
  char *res3 = (char *)s21_trim(str3, ptr3);
  ck_assert_str_eq(res3, "WoW, I love it!");
  free(res3);
  // TEST 4.
  char *str4 = "abc";
  char *ptr4 = "abc";
  char *res4 = (char *)s21_trim(str4, ptr4);
  ck_assert_str_eq(res4, "");
  free(res4);
  // TEST 5.
  char *str5 = "     HELLO    ";
  char *ptr5 = " ";
  char *res5 = (char *)s21_trim(str5, ptr5);
  ck_assert_str_eq(res5, "HELLO");
  free(res5);
  // TEST 6.
  char *str6 = "     HELLO    ";
  char *ptr6 = S21_NULL;
  char *res6 = (char *)s21_trim(str6, ptr6);
  ck_assert_str_eq(res6, "HELLO");
  free(res6);
}

END_TEST

Suite SUITE_NAME {
	Suite *suite = suite_create(SUITE_LABEL);

	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test);
  	suite_add_tcase(suite, tcase);


 	return suite;
}

