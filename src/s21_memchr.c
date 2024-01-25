#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
    unsigned char *bait = (unsigned char *)str;
    void *result = S21_NULL;
    int found = 0;

    while (n > 0 && !found) {
        if (*bait == c) {
            result = (void *)bait;
            found = 1;
        }
        bait++;
        n--;
    }
    return result;
}

