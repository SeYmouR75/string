#include "s21_test_string.h"

#define ACTUAL s21_sscanf
#define EXPECTED sscanf
#define SUITE_LABEL "suite_s21_sscanf"
#define SUITE_NAME *suite_s21_sscanf()

START_TEST(test_d) {
  int x1, x2, y1, y2;
  ck_assert_int_eq(sscanf("298 7 3", "%d%*d%d", &x1, &x2),
                   s21_sscanf("298 7 3", "%d%*d%d", &y1, &y2));

  ck_assert_int_eq(sscanf("298/02", "%d%*c%d", &x1, &x2),
                   s21_sscanf("298/02", "%d%*c%d", &y1, &y2));

  ck_assert_int_eq(sscanf("298\n\t 3.1", "%d%d", &x1, &x2),
                   s21_sscanf("298\n\t 3.1", "%d%d", &y1, &y2));

  int x5, y5;
  ck_assert_int_eq(sscanf("298\n\t 3.1", "%d%d%n", &x1, &x2, &x5),
                   s21_sscanf("298\n\t 3.1", "%d%d%n", &y1, &y2, &y5));

  short int x4, y4;
  ck_assert_int_eq(sscanf("298 3", "%d%hd", &x1, &x4),
                   s21_sscanf("298 3", "%d%hd", &y1, &y4));

  long int x3, y3;
  ck_assert_int_eq(sscanf("298 3", "%ld%hd", &x3, &x4),
                   s21_sscanf("298 3", "%ld%hd", &y3, &y4));

  ck_assert_int_eq(sscanf("298 3", "%ld%n%hd", &x3, &x1, &x4),
                   s21_sscanf("298 3", "%ld%n%hd", &y3, &y1, &y4));
}

END_TEST

START_TEST(test_x) {
  unsigned int x1, x2, y1, y2;
  ck_assert_int_eq(sscanf("298 7 ab", "%x%*x%x", &x1, &x2),
                   s21_sscanf("298 7 ab", "%x%*x%x", &y1, &y2));

  unsigned short x3, y3;
  unsigned long x4, y4;
  ck_assert_int_eq(sscanf("298 7 ab", "%hX%*i%lx", &x3, &x4),
                   s21_sscanf("298 7 ab", "%hX%*i%lx", &y3, &y4));
}

END_TEST

START_TEST(test_o) {
  unsigned int x1, x2 = 0, y1, y2 = 0;
  ck_assert_int_eq(sscanf("298 7 ab", "%o%*o%o", &x1, &x2),
                   s21_sscanf("298 7 ab", "%o%*o%o", &y1, &y2));

  short unsigned x3, y3;
  long unsigned x4, y4;
  ck_assert_int_eq(sscanf("298 7 ab", "%ho%*i%lo", &x3, &x4),
                   s21_sscanf("298 7 ab", "%ho%*i%lo", &y3, &y4));
}

END_TEST

START_TEST(test_u) {
  unsigned int x1, x2 = 0, y1, y2 = 0;
  ck_assert_int_eq(sscanf("298 -7 ab", "%u%*u%u", &x1, &x2),
                   s21_sscanf("298 -7 ab", "%u%*u%u", &y1, &y2));

  ck_assert_int_eq(sscanf("298 7 -3", "%u%*u%u", &x1, &x2),
                   s21_sscanf("298 7 -3", "%u%*u%u", &y1, &y2));

  short unsigned x3, y3;
  long unsigned x4, y4;
  ck_assert_int_eq(sscanf("298 -7 0003", "%hu%*i%lu", &x3, &x4),
                   s21_sscanf("298 -7 0003", "%hu%*i%lu", &y3, &y4));
}

END_TEST

START_TEST(test_i) {
  int x1, x2 = 0, y1, y2 = 0;
  ck_assert_int_eq(sscanf("0x298 -7 ab", "%i%*i%i", &x1, &x2),
                   s21_sscanf("0x298 -7 ab", "%i%*i%i", &y1, &y2));

  short x3, y3;
  long x4, y4;
  ck_assert_int_eq(sscanf("298 -7 0xab", "%hi%*i%li", &x3, &x4),
                   s21_sscanf("298 -7 0xab", "%hi%*i%li", &y3, &y4));

  ck_assert_int_eq(sscanf("298 -7 0xab", "%hn%i%ln", &x3, &x1, &x4),
                   s21_sscanf("298 -7 0xab", "%hn%i%ln", &y3, &y1, &y4));
}

END_TEST

START_TEST(test_p) {
  void *x1, *x2, *y1, *y2;
  ck_assert_int_eq(sscanf("298 7 0xab", "%p%*p%p", &x1, &x2),
                   s21_sscanf("298 7 0xab", "%p%*p%p", &y1, &y2));
}

END_TEST

START_TEST(test_f) {
  float x1, x2 = 0, y1, y2 = 0;
  ck_assert_int_eq(sscanf("298.3 4", "%f%f", &x1, &x2),
                   s21_sscanf("298.3 4", "%f%f", &y1, &y2));

  ck_assert_int_eq(sscanf("298.3 0 nAN 4", "%f%*f%*f%f", &x1, &x2),
                   s21_sscanf("298.3 0 Nan 4", "%f%*f%*f%f", &y1, &y2));

  long double x3, y3;
  ck_assert_int_eq(sscanf("298e-2 iNf 3E3", "%Lf%*f%f", &x3, &x2),
                   s21_sscanf("298e-2 InF 3E3", "%Lf%*f%f", &y3, &y2));
}

END_TEST

START_TEST(test_c) {
  char x1, x2, y1, y2;
  ck_assert_int_eq(sscanf("0 a", "%c %c", &x1, &x2),
                   s21_sscanf("0 a", "%c %c", &y1, &y2));

  ck_assert_int_eq(sscanf("0.a", "%c.%c", &x1, &x2),
                   s21_sscanf("0.a", "%c.%c", &y1, &y2));
}

END_TEST

START_TEST(test_s) {
  char x1[10] = "\0", x2[10] = "\0", y1[10] = "\0", y2[10] = "\0";
  ck_assert_int_eq(sscanf("This good work", "%9sabc%9s", x1, x2),
                   s21_sscanf("This good work", "%9sabc%9s", y1, y2));

  ck_assert_int_eq(sscanf("This good work", "%9s%*2s%9s", x1, x2),
                   s21_sscanf("This good work", "%9s%*2s%9s", y1, y2));

  ck_assert_int_eq(sscanf("This good work", "%9sf%9s", x1, x2),
                   s21_sscanf("This good work", "%9sf%9s", y1, y2));

  ck_assert_int_eq(sscanf("  so", "%9s%9s", x1, x2),
                   s21_sscanf("  so", "%9s%9s", y1, y2));
}

END_TEST

START_TEST(test_eg) {
  float fx, fx1;
  double lfx, lfx1;
  long double llfx, llfx1;
  s21_sscanf("1 2 -123232.001 .995123 999.99.1", "%*E %*G %g %le %Lf", &fx,
             &lfx, &llfx);
  sscanf("1 2 -123232.001 .995123 999.99.1", "%*E %*G %g %le %Lf", &fx1, &lfx1,
         &llfx1);
}

END_TEST

START_TEST(test_inf) {
  float a1, a2, b1, b2, c1, c2, d1, d2;

  s21_sscanf("inF InF inF INF", "%G %G %G %G", &a1, &b1, &c1, &d1);
  sscanf("inF InF inF INF", "%G %G %G %G", &a2, &b2, &c2, &d2);
}

END_TEST

START_TEST(test_nan) {
  float a1, a2, b1, b2, c1, c2, d1, d2;

  s21_sscanf("Nan NAN 0.0000 0", "%G %G %G %G", &a1, &b1, &c1, &d1);
  sscanf("Nan NAN 0.0000 0", "%G %G %G %G", &a2, &b2, &c2, &d2);
}
END_TEST

Suite SUITE_NAME {
  Suite *suite = suite_create(SUITE_LABEL);

  TCase *tcase = tcase_create("case");
  tcase_add_test(tcase, test_d);
  suite_add_tcase(suite, tcase);

  TCase *tcase2 = tcase_create("case2");
  tcase_add_test(tcase2, test_x);
  suite_add_tcase(suite, tcase2);

  TCase *tcase3 = tcase_create("case3");
  tcase_add_test(tcase3, test_o);
  suite_add_tcase(suite, tcase3);

  TCase *tcase4 = tcase_create("case4");
  tcase_add_test(tcase4, test_u);
  suite_add_tcase(suite, tcase4);

  TCase *tcase5 = tcase_create("case5");
  tcase_add_test(tcase5, test_i);
  suite_add_tcase(suite, tcase5);

  TCase *tcase6 = tcase_create("case6");
  tcase_add_test(tcase6, test_p);
  suite_add_tcase(suite, tcase6);

  TCase *tcase7 = tcase_create("case7");
  tcase_add_test(tcase7, test_f);
  suite_add_tcase(suite, tcase7);

  TCase *tcase8 = tcase_create("case8");
  tcase_add_test(tcase8, test_c);
  suite_add_tcase(suite, tcase8);

  TCase *tcase9 = tcase_create("case9");
  tcase_add_test(tcase9, test_s);
  suite_add_tcase(suite, tcase9);

  TCase *tcase10 = tcase_create("case10");
  tcase_add_test(tcase10, test_eg);
  suite_add_tcase(suite, tcase10);

  TCase *tcase11 = tcase_create("case11");
  tcase_add_test(tcase11, test_inf);
  suite_add_tcase(suite, tcase11);

  TCase *tcase12 = tcase_create("case12");
  tcase_add_test(tcase12, test_nan);
  suite_add_tcase(suite, tcase12);

  return suite;
}
