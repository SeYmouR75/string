#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;

  if (str != S21_NULL) {
    result = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));

    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
      if (str[i] >= 65 && str[i] <= 91) {
        result[i] = str[i] + 32;

      } else {
        result[i] = str[i];
      }

      count++;
    }
    result[count] = '\0';
  }
  return result;
}
