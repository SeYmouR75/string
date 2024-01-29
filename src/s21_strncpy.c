#include "s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *orig_dest = {0};
  if (src != S21_NULL && dest != S21_NULL) {
    orig_dest = dest;
    s21_size_t i = 0;
    while (i < n && src[i]) {
      orig_dest[i] = src[i];
      i++;
    }
    while (i < n) {
      orig_dest[i] = '\0';
      i++;
    }
  }
  return orig_dest;
}
