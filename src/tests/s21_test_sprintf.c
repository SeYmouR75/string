#include "s21_test_string.h"

#define ACTUAL s21_sprintf
#define EXPECTED sprintf
#define SUITE_LABEL "suite_s21_sprintf"
#define SUITE_NAME *suite_s21_sprintf()
#define STRINGS strings_sprintf
#define VARIABLES variables_sprintf
#define TEST_SIZE 8  // 1-8

#define M_PI 3.14159265358979323846                   /* pi */
#define M_PIf 3.14159265358979323846f                 /* pi */
#define M_PIl 3.141592653589793238462643383279502884L /* pi */

typedef struct {
  char *vstr;
  long vlong1;
  long vlong2;
  double vdbl;
  float vflt;
  long double vldbl;
} SPFDATA;

SPFDATA VARIABLES[] = {{"Good job!", 'U', 'U', M_PI, M_PIf, 1.189e+132L},
                       {"Good job!", 'U', 'U', M_PI, M_PIf, M_PIl},
                       {"Good job!", 952, -952, 9.9999992546, M_PIf, M_PIl},
                       {"Good job!", -75352, -1, M_PI, 0.00000999215, M_PIl},
                       {"Good job!", 5212777897, -5212777897, 2.22507e-308,
                        1.175494e-38, 3.36210314e-4932L},
                       {"Good job!", 5212777897, -5212777897, 1.79769e+308,
                        3.402823e+38, 1.18973149e+4932L},
                       {"Good job!", 75352, -1, M_PI, M_PIf, 2147483647.0},
                       {"Good job!", 75352, -1, M_PI, M_PIf, 2147483647.0}};

char STRINGS[][256] = {
    "ptr: %p, char: %-24c, char: %+012.4c, double: %f, float: %+27.5f, long "
    "double: %Lf, count: %n fi",
    "ptr: %+030.2p, char num: %hhd, uchar: %hhu, double: %e, float: %e, long "
    "double: %+034.17Lf, count: %n fi",
    "ptr: % -25.3p, short: %hd, ushort: %hu, double: %E, float: %E, long "
    "double: %- 22Lf, count: %n fi",
    "str: %s, int: %d, uint: %u, double: %e, float: %e, long double: %Le, "
    "count: %n fi",
    "str: %+022s, long: %ld, ulong: %lu, double: %.5E, float: %E, long double: "
    "%.8LE, count: %n fi",
    "str: % 24s, long long: %lld, ulong long: %llu, double: %f, float: %f, "
    "long double: %.25Le, count: %n fi",
    "str: %-9.3s, int: % d, uint: %#x, double: %f, float: %.2e, long double: "
    "%Le, count: %n fi",
    "str: %.7s, int: %+d, uint: %015u, double: %-17.9f, float: %.9f, long "
    "double: %#Lf, count: %n fi %%",
};

START_TEST(test) {
  int actual_result;
  int expected_result;
  char actual_dest[20000] = {0};
  char expected_dest[20000] = {0};
  int actual_count = 0, expected_count = 0;

  actual_result =
      ACTUAL(actual_dest, STRINGS[_i], VARIABLES[_i].vstr, VARIABLES[_i].vlong1,
             VARIABLES[_i].vlong2, VARIABLES[_i].vdbl, VARIABLES[_i].vflt,
             VARIABLES[_i].vldbl, &actual_count);
  expected_result =
      EXPECTED(expected_dest, STRINGS[_i], VARIABLES[_i].vstr,
               VARIABLES[_i].vlong1, VARIABLES[_i].vlong2, VARIABLES[_i].vdbl,
               VARIABLES[_i].vflt, VARIABLES[_i].vldbl, &expected_count);

  //	printf("act: %s, res: %d, count: %d\n", actual_dest, actual_result,
  // actual_count); 	printf("exp: %s, res: %d, count: %d\n\n", expected_dest,
  // expected_result, expected_count);

  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_str_eq(actual_dest, expected_dest);
  ck_assert_int_eq(actual_count, expected_count);
}
END_TEST

START_TEST(test2) {
  int actual_result;
  int expected_result;
  char actual_dest[20000] = {0};
  char expected_dest[20000] = {0};
  int actual_count = 0, expected_count = 0;
  char *format =
      "str: %p, char: %c, double: %*f, float: %.*f, long double: %*.*Lf, "
      "count: %n fi";

  actual_result =
      ACTUAL(actual_dest, format, "string", 'F', 12, 3.14159, 3, 15.42578, 64,
             22, 54556456513513524541303.6511651L, &actual_count);
  expected_result =
      EXPECTED(expected_dest, format, "string", 'F', 12, 3.14159, 3, 15.42578,
               64, 22, 54556456513513524541303.6511651L, &expected_count);

  //	printf("act: %s, res: %d, count: %d\n", actual_dest, actual_result,
  // actual_count); 	printf("exp: %s, res: %d, count: %d\n\n", expected_dest,
  // expected_result, expected_count);

  ck_assert_int_eq(actual_result, expected_result);
  ck_assert_str_eq(actual_dest, expected_dest);
  ck_assert_int_eq(actual_count, expected_count);
}
END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_loop_test(tcase, test, 0, TEST_SIZE);
  suite_add_tcase(suite, tcase);

  TCase *tcase2 = tcase_create("case2");
  tcase_add_test(tcase2, test2);
  suite_add_tcase(suite, tcase2);

  return suite;
}
