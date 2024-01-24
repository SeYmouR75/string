#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n){
    unsigned char *bait = (unsigned char *)str;
    void *result = S21_NULL;

    while (n > 0){
        if (*bait == c){
            result = (void *)bait;
            break;  // Прерываем цикл, так как мы уже нашли символ
        }
        bait++;
        n--;
    }

    return result;
}

