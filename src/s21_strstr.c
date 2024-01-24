#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {                  // optimization raises questions
	char *result = S21_NULL;
	if(haystack != S21_NULL || needle != S21_NULL){
		char *tmp_ptr = (char *)haystack;
		while (*tmp_ptr && result == S21_NULL){
			const char *temp_haystack = tmp_ptr;
			const char *temp_needle = needle;

			while(temp_haystack && temp_needle && (*temp_haystack == *temp_needle)){
				temp_haystack++;
				temp_needle++;	
				if(!*temp_needle) result = tmp_ptr;
			}
			

			tmp_ptr++;
		}
	}
	
	return result;
}

