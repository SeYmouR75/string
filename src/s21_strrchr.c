#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
	char *result = S21_NULL;

	s21_size_t lenght = s21_strlen(str);
	for(s21_size_t i = 0; i <= lenght; i++){
		if(str[i] == c){
			result = ((char *)str) + i;
		}
	}


	return result;
}
