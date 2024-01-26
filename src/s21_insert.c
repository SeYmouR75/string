#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (str != S21_NULL && src != S21_NULL) {
    s21_size_t size = s21_strlen(src) + s21_strlen(str);
    s21_size_t end_index = start_index + s21_strlen(str);
    result = (char *)calloc(size + 1, sizeof(char));
    if (result != S21_NULL && start_index < s21_strlen(src)) {
      for (s21_size_t i = 0; i < start_index; i++) result[i] = src[i];
      for (s21_size_t i = start_index, j = 0; i < end_index; i++, j++)
        result[i] = str[j];
      for (s21_size_t i = end_index, j = start_index; i < size; i++, j++)
        result[i] = src[j];
    } else
      result = S21_NULL;
  }
  return result;
}



