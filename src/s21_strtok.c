#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
	static char *ptr_str;
	static s21_size_t i, length;
    char *token = S21_NULL;
	int zero = 0;

    if(str) {
        ptr_str = str;
		i = 0;
		length = s21_strlen(ptr_str);
		for(s21_size_t j = 0; j < length; j++) {
			if(s21_strchr(delim, ptr_str[j])) ptr_str[j] = '\0';
		}
		zero = 1;
    }

	while(i < length && !token) {
		if(zero && ptr_str[i]) token = &ptr_str[i];
		if(!ptr_str[i]) zero = 1;
		i++;
	}

    return token;
}
