#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
	char *result = S21_NULL;
	while(*str1 && !result) {
		result = s21_strchr(str2, *str1);
		if (result) result = (char *)str1;
		str1++;
	}
	
	return result;
}

