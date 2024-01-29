#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;

  do {
    if (*str == c) result = (char *)str;
  } while (*str++ && !result);

  return result;
}
