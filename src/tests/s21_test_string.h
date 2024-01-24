#ifndef S21_TEST_STRING_H
#define S21_TEST_STRING_H

#include <check.h>
#include <string.h>
#include <stdlib.h>

#include "../s21_string.h"

Suite *suite_s21_memchr();
Suite *suite_s21_memcmp();
Suite *suite_s21_memcpy();
Suite *suite_s21_memset();
Suite *suite_s21_strncat();
Suite *suite_s21_strchr();
Suite *suite_s21_strncmp();
Suite *suite_s21_strncpy();
Suite *suite_s21_strcspn();
Suite *suite_s21_strerror();
Suite *suite_s21_strlen();
Suite *suite_s21_strpbrk();
Suite *suite_s21_strrchr();
Suite *suite_s21_strstr();
Suite *suite_s21_strtok();
Suite *suite_s21_sprintf();
Suite *suite_s21_sscanf();
Suite *suite_s21_to_lower();
Suite *suite_s21_to_upper();
Suite *suite_s21_trim();
Suite *suite_s21_insert();
#endif  // S21_TEST_STRING_H
