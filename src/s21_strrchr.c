#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
	const char *last_coincidence = S21_NULL;
	if(str != S21_NULL && c){
		const char *tmp_str = str; 
		while(*tmp_str){
			if(*tmp_str == (char)c)	last_coincidence = tmp_str;
			tmp_str++;
		}
	}

	return (char *)last_coincidence;
}
