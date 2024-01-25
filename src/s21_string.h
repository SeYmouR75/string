#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>

typedef unsigned long s21_size_t;
#define S21_NULL (void*)0
typedef struct {
	s21_size_t minus: 1;  
	s21_size_t plus: 1;
	s21_size_t space: 1;
	s21_size_t hash: 1;
	s21_size_t zero: 1;
	s21_size_t width: 32;
	s21_size_t dot: 1;
	s21_size_t precision: 32;
	s21_size_t length_h: 2;
	s21_size_t length_l: 2;
	s21_size_t length_L: 1;
	s21_size_t type: 7;
	s21_size_t exp: 16;
	s21_size_t negative: 1;
	s21_size_t sign: 6;
	s21_size_t space_symbol: 6;
} STRSPEC;

union un_double {
  struct {
    unsigned long mant : 52;
    unsigned long exp : 11;
    unsigned long sign : 1;
  } fld;
  double real;
};

union un_ldouble {
  struct {
    unsigned long mant : 63;
    unsigned long exp : 15;
    unsigned long sign : 1;
    unsigned long empty : 48;
  } fld;
  long double real;
};

#define INT_MAX 2147483647

typedef struct {
  int width;
  int flag_w;
  int flag_minus;
  int flag_star;
  int flag_plus;
  int number_systems;
  char length;
} Flags;

enum  {byte_size = 8, min_buf_size = 129, mid_buf_size = 1000, max_buf_size = 20000, binary_radix = 2, octal_radix = 8, decimal_radix = 10, hex_radix = 16};

void *s21_memchr(const void *str, int c, s21_size_t n);

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);

void *s21_memcpy(void *dest, const void *src, s21_size_t n);

void *s21_memset(void *str, int c, s21_size_t n);

char *s21_strncat(char *dest, const char *src, s21_size_t n);

char *s21_strchr(const char *str, int c);

int s21_strncmp(const char *str1, const char *str2, s21_size_t n);

char *s21_strncpy(char *dest, const char *src, s21_size_t n);

s21_size_t s21_strcspn(const char *str1, const char *str2);

char *s21_strerror(int errnum);

s21_size_t s21_strlen(const char *str);

char *s21_strpbrk(const char *str1, const char *str2);

char *s21_strrchr(const char *str, int c);

char *s21_strstr(const char *haystack, const char *needle);

char *s21_strtok(char *str, const char *delim);

void *s21_insert(const char *src, const char *str, s21_size_t start_index);

void *s21_trim(const char *src, const char *trim_chars);

void *s21_to_lower(const char *str);

void *s21_to_upper(const char *str);

int s21_sprintf(char *str, const char *format, ...);

int s21_sscanf(const char* str, const char* format, ...);

// declarates functions for s21_sscanf

int skip_spaces(const char* str, const char* sym);

const char* get_width_sf(const char* format, Flags* flags);

const char* set_flags(const char* format, Flags* flags);

char set_length_int(char size, char spec);

const char* set_scale_number_system(const char* str, Flags* flags);

const char* parse_integer(char spec, const char* str, void* dest, char size,
                    int* count_success, Flags flags);

const char* specificator_u(char spec, const char* str, void* arg, char size,
                   int* count_success, Flags flags);

const char* parser(const char* str, const char* string, const char* format,
                    Flags flags, void* arg, int* count_success);

const char* specificator_p(const char* str, Flags flags, void* arg, char size,
                       int* count_success, char spec);

char convert_char_to_int(char c);

const char* specificator_d_i(const char* str, Flags flags, long long* num);

const char* specificator_s(const char* str, Flags flags, void* arg, int* count_res);

const char* set_length_float(const char* str, Flags flags, void* arg, int* count_res,
                       char size);

const char* analyse_float_number(const char* str, Flags flags, long double* num,
                   int* count_res);

int s21_strncasecmp(const char *s1, const char *s2, s21_size_t n);

int check_nan_or_inf(const char* str, long double* num);
