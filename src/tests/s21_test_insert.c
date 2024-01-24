#include "s21_test_string.h"


#define SUITE_LABEL "suite_s21_insert"
#define SUITE_NAME *suite_s21_insert()
                   

START_TEST(test) {
  // TEST 1.
  char *str1 = "Aboba";
  char *in1 = "kek";
  char *result1 = S21_NULL;
  result1 = s21_insert(str1, in1, 2);
  ck_assert_str_eq(result1, "Abkekoba");
  free(result1);
  // TEST 2.
  char *str2 = "Aboba";
  char *in2 = "kek";
  char *result2 = S21_NULL;
  result2 = s21_insert(str2, in2, 4);
  ck_assert_str_eq(result2, "Abobkeka");
  free(result2);
  // TEST 3.
  char *str3 = "f";
  char *in3 = "k ek";
  char *result3 = s21_insert(str3, in3, 0);
  ck_assert_str_eq(result3, "k ekf");
  free(result3);
  // TEST 4.
  char *str4 = "Aboba   ";
  char *in4 = "k ek";
  char *result4 = s21_insert(str4, in4, 0);
  ck_assert_str_eq(result4, "k ekAboba   ");
  free(result4);
  // TEST 5.
  // char *str5 = "Aboba   ";
  // char *in5 = S21_NULL;
  // char *result5 = s21_insert(str5, in5, 8);
  // ck_assert_str_eq(result5, "Aboba   ");
  // printf("%s\n", result5);
  // free(result5);
  
}

END_TEST

Suite SUITE_NAME {
	Suite *suite = suite_create(SUITE_LABEL);

	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test);
  	suite_add_tcase(suite, tcase);


 	return suite;
}