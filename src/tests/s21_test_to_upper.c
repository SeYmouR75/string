#include "s21_test_string.h"


#define SUITE_LABEL "suite_s21_to_upper"
#define SUITE_NAME *suite_s21_to_upper()
                   

START_TEST(test) {
  void *test1 = s21_to_upper("Hello world\0");
  ck_assert_str_eq((const char *)test1, "HELLO WORLD\0");
  free(test1);

  void *test2 = s21_to_upper("world\0");
  ck_assert_str_eq((const char *)test2, "WORLD\0");
  free(test2);

  void *test3 = s21_to_upper("a\n\0");
  ck_assert_str_eq((const char *)test3, "A\n\0");
  free(test3);

  void *test4 = s21_to_upper(" \n\0");
  ck_assert_str_eq((const char *)test4, " \n\0");
  free(test4);

  void *test5 = s21_to_upper("HELLO WORLD\0");
  ck_assert_str_eq((const char *)test5, "HELLO WORLD\0");
  free(test5);

  void *test6 = s21_to_upper("\0");
  ck_assert_str_eq((const char *)test6, "\0");
  free(test6);
}
END_TEST

Suite SUITE_NAME {
	Suite *suite = suite_create(SUITE_LABEL);

	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test);
  	suite_add_tcase(suite, tcase);


 	return suite;
}



