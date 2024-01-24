#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {  char *ptr = S21_NULL;
  if (src && trim_chars) {
    char *start = (char *)src;  // указатель на начало исходной строки
    char *end =
        (char *)src + s21_strlen(src);  // указатель на конец исходной строки
    for (; *start &&
           s21_strchr(trim_chars,
                      *start);  // проверяем что указатель на текущий символ
                                // не нулевой и находится в trim_chars
         start++)  // двигаем указатель start вперед пока не встретим trim_chars
      ;
    for (; end != start && s21_strchr(trim_chars, *(end - 1));
         end--)  // проверяем тоже самое для end
      ;  // двигаем указатель end c конца строки пока не встретим trim_chars
    ptr = (char *)malloc((end - start + 1) * sizeof(char));
    if (ptr) {
      s21_strncpy(ptr, start,
                  end - start);  // копируем в новую строку start до end
      *(ptr + (end - start)) = '\0';
    }
  }
  return ptr;
}
