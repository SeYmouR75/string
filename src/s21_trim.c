#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, int n) {
    char *str1 = (char *) dest;
    char *str2 = (char *) src;

    if (dest != S21_NULL && src != S21_NULL) {
        int i;
        if (str1 > str2) {
            i = n;
            while (i--)
                *(str1 + i) = *(str2 + i);
                 
        } else {
            i = 0;
            while (i++ < n)
                *(str1 + (i - 1)) = *(str2 + (i - 1));
        }
    }

    return str1;
}

char *s21_strcpy(char *dest, const char *src) {
    char *ptr = dest;
    if (src != S21_NULL && dest != S21_NULL) {
        while (*src != '\0') {
            *dest = *src;
            dest++;
            src++;
        }

        *dest = '\0';
    }

    return ptr;
}

void *s21_trim(const char *src, const char *trim_chars) {
    void *result = S21_NULL;
    static char *buffer = S21_NULL;
    buffer = malloc(s21_strlen(src) + 1);
   
   	       s21_strcpy(buffer, src);

    if (src) {
        if (trim_chars && *trim_chars) {
            for (int i = (int) s21_strlen(src) - 1;
                 i >= 0 && s21_strrchr(trim_chars, buffer[i]) != S21_NULL; i--)
                buffer[i] = '\0';

            while (buffer[0] != '\0' && s21_strrchr(trim_chars, buffer[0]) != S21_NULL)
                s21_memmove(&buffer[0], &buffer[1], s21_strlen(src));

            result = buffer;
        } else {
            char trim_specsymbol[] = " \n\t\r\x0B\f";
            for (int i = (int) s21_strlen(src) - 1;
                 i >= 0 && s21_strrchr(trim_specsymbol, buffer[i]) != S21_NULL; i--)
                buffer[i] = '\0';

            while (buffer[0] != '\0' && s21_strrchr(trim_specsymbol, buffer[0]) != S21_NULL)
                s21_memmove(&buffer[0], &buffer[1], s21_strlen(src));

            result = buffer;
        }
    }
    return result;
}

