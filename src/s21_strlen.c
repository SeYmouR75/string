#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  const char *buffer = str;
  s21_size_t length = 0;
  while (*buffer++) length++;

  return length;
}
