#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t length_dest = s21_strlen(dest);
  s21_size_t length_src = s21_strlen(src);
  for (s21_size_t i = 0; i < n && i < length_src; i++) {
    dest[length_dest] = src[i];
    length_dest++;
  }
  dest[length_dest] = '\0';

  return dest;
}
