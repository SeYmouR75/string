#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {

	static char *next_token = S21_NULL;
    char *token = S21_NULL;

    if (str) {
        next_token = str;
    } 
    
    token = next_token;
    
    if (!*token) {
        token = S21_NULL;
    }
    
    char *delim_pos = next_token;
    
    if (s21_strchr(delim, *delim_pos)){
        token = S21_NULL;
    }

    while (*delim_pos && !s21_strchr(delim, *delim_pos)) {
        delim_pos++;
    }
    
    if (*delim_pos) {
        next_token = delim_pos + 1;
        *delim_pos = '\0';
    } else {
        next_token = S21_NULL;
    }

    return token;
}
