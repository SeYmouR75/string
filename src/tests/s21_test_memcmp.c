#include "s21_test_string.h"

#define ACTUAL(x, y, z) s21_memcmp(x, y, z)
#define EXPECTED(x, y, z) memcmp(x, y, z)

#define SUITE_LABEL "suite_s21_memcmp"
#define SUITE_NAME *suite_s21_memcmp()

START_TEST(test) {
  int actualres;
  int expectedres;
  // TEST 1
  char *f1 = "Hello world\0";
  char *s1 = "Hello world\0";
  actualres = ACTUAL(f1, s1, 5);
  expectedres = EXPECTED(f1, s1, 5);

  ck_assert_int_eq(actualres, expectedres);

  // TEST 2
  char *f2 = "Hello world\n\0";
  char *s2 = "Hello world\n\0";
  actualres = ACTUAL(f2, s2, 13);
  expectedres = EXPECTED(f2, s2, 13);

  ck_assert_int_eq(actualres, expectedres);

  // TEST 3
  char *f3 = "a\n\0";
  char *s3 = "Hello world\n\0";
  actualres = ACTUAL(f3, s3, 3);
  expectedres = EXPECTED(f3, s3, 3);

  ck_assert_int_gt(actualres, 0);
  ck_assert_int_gt(expectedres, 0);

  // TEST 4
  char *f4 = "H\n\0";
  char *s4 = "a\n\0";
  actualres = ACTUAL(f4, s4, 1);
  expectedres = EXPECTED(f4, s4, 1);

  ck_assert_int_lt(actualres, 0);
  ck_assert_int_lt(expectedres, 0);


  // TEST 5
  char *f5 = " \n\0";
  char *s5 = " \0";
  actualres = ACTUAL(f5, s5, 1);
  expectedres = EXPECTED(f5, s5, 1);

  ck_assert_int_eq(actualres, expectedres);

  // TEST 6
  char *f6 = " \0";
  char *s6 = "\n\0";
  actualres = ACTUAL(f6, s6, 2);
  expectedres = EXPECTED(f6, s6, 2);

  ck_assert_int_gt(actualres, 0);
  ck_assert_int_gt(expectedres, 0);
}

END_TEST

Suite SUITE_NAME {
	Suite *suite = suite_create(SUITE_LABEL);

	TCase *tcase = tcase_create("case");
	tcase_add_test(tcase, test);
  	suite_add_tcase(suite, tcase);


 	return suite;
}



