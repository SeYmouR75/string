#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src && trim_chars) {
    s21_size_t i = 0, size = s21_strlen(src), j = 0;

    if (size) j = size - 1;
    for (; i < size && s21_strchr(trim_chars, src[i]); i++)
      ;
    for (; j > 0 && s21_strchr(trim_chars, src[j]); j--)
      ;

    result = (char *)calloc(size + 1, sizeof(char));
    if (result && j >= i) {
      s21_strncpy(result, &src[i], j - i + 1);
    }
  }

  return (void *)result;
}
