#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;

  if (*needle == '\0') {
    result = (char *)haystack;
  }
  for (s21_size_t i = 0; i < s21_strlen(haystack) && !result; i++) {
    if (*(haystack + i) == *needle) {
      char *ptr = s21_strstr(haystack + i + 1, needle + 1);
      if (ptr) {
        result = ptr - 1;
      } else {
        result = S21_NULL;
      }
    }
  }
  return result;
}
