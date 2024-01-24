#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {  if (src == S21_NULL || str == S21_NULL || start_index > s21_strlen(src)) {
    return S21_NULL;
  }
  char *ptr = S21_NULL;
  if (src != S21_NULL && str != S21_NULL) {
    ptr =
        (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    if (ptr != S21_NULL && start_index <= s21_strlen(src)) {
      s21_memcpy(ptr, src, start_index);  
                                          
      s21_memcpy(ptr + start_index, str,
                 s21_strlen(str));  /
      s21_memcpy(ptr + start_index + s21_strlen(str),
                 src + start_index,  
                                     
                 s21_strlen(src) - start_index);
      ptr[s21_strlen(src) + s21_strlen(str)] = '\0';
    }
  }
  return ptr;
}
