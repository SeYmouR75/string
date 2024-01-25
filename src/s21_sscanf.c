#include "s21_string.h"

int s21_sscanf(const char* str, const char* format, ...) {
  char specs[] = "diuoxXcsnpfFeEgG%";
  va_list args;
  va_start(args, format);
  int count_succes = -1;
  const char* string = str;
  
  if (!*str) str = S21_NULL;
  while (*format && str) {
    switch (*format) {
      case '%': {
        format++;
        Flags flags = {0};
        format = set_flags(format, &flags);
        while (!s21_strchr(specs, *format)) format++;
        void* arg = S21_NULL;
        if (!flags.flag_star) arg = va_arg(args, void*);
        str = parser(str, string, format, flags, arg, &count_succes);
        break;
      }
      case ' ':
      case '\t':
      case '\n':
      case '\b':
      case '\r':
        str += skip_spaces(str, " \t\n\b\r\f\x0B");
        break;
      default:
        if (*str == *format) {
          str++;
        } else {
          va_end(args);
          return count_succes;
        }
    }
    format++;
  }
  va_end(args);
  return count_succes;
}

int skip_spaces(const char* str, const char* sym) {
  int i = 0;

  while (s21_strchr(sym, *str) && *str) {
    str++;
    i++;
  }
  return i;
}

const char* set_flags(const char* format, Flags* flags) {
  flags->flag_w = 1;
  flags->number_systems = 10;
  flags->flag_minus = 1;

  if (*format == '*') {
    flags->flag_star = 1;
    format++;
  }
  format = get_width_sf(format, flags);
  if (!flags->width) flags->width = INT_MAX;
  return format;
}

const char* get_width_sf(const char* format, Flags* flags) {
  flags->width = 0;
  while (isdigit(*format) &&
         flags->width < (INT_MAX - (*format - '0')) / 10) {
    flags->width = (flags->width) * 10 + (*format - '0');
    format++;
  }
  return format;
}

const char* parser(const char* str, const char* string, const char* format,
                    Flags flags, void* arg, int* count_success) {
  char spec = *format;
  const char* start = str + skip_spaces(str, " \t\n\r\b\f\x0B");
  if (*count_success < 0 && *start != '\0') *count_success = 0;

  switch (*format) {
    case 'd':
    case 'i':
      if (*start != '\0') {
        str = parse_integer(spec, start, arg, *(format - 1), count_success, flags);
      }
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      if (*start != '\0') {
        if (*format == 'o') {
          flags.number_systems = 8;
        } else if (*format == 'x' || *format == 'X') {
          flags.number_systems = 16;
        }
        str = specificator_u(spec, start, arg, *(format - 1), count_success, flags);
      }
      break;
    case 'c':
      if (flags.flag_star) {
        str++;
      } else {
        *(char*)arg = *str;
        *count_success += 1;
        str++;
      }
      break;
    case 's':
      if (*start != '\0') {
        str = specificator_s(start, flags, arg, count_success);
      }
      break;
    case 'n':
      if (arg) {
        int* n = (int*)arg;
        *n = str - string;
      }
      break;
    case 'p':
      if (*start != '\0') {
        str = specificator_p(start, flags, arg, *(format - 1), count_success, spec);
      }
      break;
    case 'f':
    case 'F':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      if (*start != '\0') {
        str = set_length_float(str, flags, arg, count_success, *(format - 1));
      }
      break;
    default:
      str = S21_NULL;
  }
  return str;
}

const char* parse_integer(char spec, const char* str, void* dest, char size,
                    int* count_success, Flags flags) {
  flags.length = set_length_int(size, spec);
  if (spec == 'i') str = set_scale_number_system(str, &flags);
  long long num;
  str = specificator_d_i(str, flags, &num);
  if (dest && str) {
    s21_memcpy(dest, &num, flags.length);
    *count_success += 1;
  }
  return str;
}

char set_length_int(char size, char spec) {
  char res = 0;
  if (spec == 'i' || spec == 'u' || spec == 'd') {
    if (size == 'l')
      res = sizeof(long long);
    else if (size == 'h')
      res = sizeof(short);
    else
      res = sizeof(int);
  }
  return res;
}

const char* set_scale_number_system(const char* str, Flags* flags) {
  str += skip_spaces(str, " \t\b\n\r\f\x0B");
  if (*str == '0') flags->number_systems = 8;
  if (*(str + 1) == 'x' || *(str + 1) == 'X') flags->number_systems = 16;
  return str;
}

const char* specificator_d_i(const char* str, Flags flags, long long* num) {
  int n = 0;
  const char* s = str;
  const char* res = "1";
  int continue_loop = 1;

if (!(isdigit(*str)) && (*str == '-' || *str == '+')) {
    if (*str == '-') {
        str++;
        if (convert_char_to_int(*str) != '?') {
            flags.flag_minus = -1;
        } else {
            res = S21_NULL;
        }
    } else if (*str == '+') {
        flags.flag_plus = 1;
        str++;
        if (convert_char_to_int(*str) == '?') {
            res = S21_NULL;
        }
    }
}

  if (res != S21_NULL && convert_char_to_int(*str) != '?' &&
      convert_char_to_int(*str) < flags.number_systems && str - s < flags.width) {
    *num = 0;
  } else
    res = S21_NULL;
  if ((s21_strchr(str, 'x') || s21_strchr(str, 'X')) &&
      flags.number_systems == 16 && res != S21_NULL)
    str += 2;
  while (continue_loop && *str != ' ' && *str != '\n' && *str != '\t' && str - s < flags.width && res != S21_NULL) {
    n = convert_char_to_int(*str);
    if (n < flags.number_systems && n != '?') {
      *num = *num * flags.number_systems + n * flags.flag_minus;
      str++;
    } else {
      continue_loop = 0;
    }
  }
  if (res != S21_NULL) res = str;
  return res;
}

char convert_char_to_int(char c) {
  char flag = '?';

  if (('0' <= c && c <= '9') || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F')) {
    switch (c) {
      case 'a':
      case 'A':
        flag = 10;
        break;
      case 'b':
      case 'B':
        flag = 11;
        break;
      case 'c':
      case 'C':
        flag = 12;
        break;
      case 'd':
      case 'D':
        flag = 13;
        break;
      case 'e':
      case 'E':
        flag = 14;
        break;
      case 'f':
      case 'F':
        flag = 15;
        break;
      default:
        flag = c - '0';
    }
  }
  return flag;
}

const char* specificator_u(char spec, const char* str, void* arg, char size,
                   int* count_success, Flags flags) {
  spec = 'u';
  flags.length = set_length_int(size, spec);
  unsigned long long num;
  str = specificator_d_i(str, flags, (long long*)&num);
  if (arg && str) {
    s21_memcpy(arg, &num, flags.length);
    *count_success += 1;
  }
  return str;
}

const char* specificator_s(const char* str, Flags flags, void* arg,
                       int* count_res) {
  str += skip_spaces(str, " \t\n\r\b\f\x0B");
  int i = 0;
  int skip = 0;

  while (*str && !skip && i < flags.width) {
    if (arg) {
      *((char*)arg + i) = *str;
    }
    str++;
    skip = isspace(*str);
    i++;
  }
  if (arg) {
    *((char*)arg + i) = '\0';
    *count_res += 1;
  }
  return str;
}

const char* specificator_p(const char* str, Flags flags, void* arg, char size, int* count_success, char spec) {
    if (arg) {
        char original_spec = spec;
        spec = 'u';
        flags.length = set_length_int(size, spec);
        flags.number_systems = 16;
        long long num;
        str = specificator_d_i(str, flags, &num);
        *(long long*)arg = num;
        *count_success += 1;
        spec = original_spec;
    }
    return str;
}

const char* set_length_float(const char* str, Flags flags, void* arg, int* count_res,
                       char size) {
  long double num;
  str = analyse_float_number(str, flags, &num, count_res);
  if (arg && str != S21_NULL) {
    switch (size) {
      case 'L':
        *(long double*)arg = num;
        break;
      case 'l':
        *(double*)arg = (double)num;
        break;
      default:
        *(float*)arg = (float)num;
        break;
    }
  }
  return str;
}

const char* analyse_float_number(const char* str, Flags flags, long double* num,
                                  int* count_res) {

    int check = check_nan_or_inf(str, num);
    const char* endptr;
    long double temp_num = 0;

    if (check) {
      endptr = str + check;
    } else {
      endptr = S21_NULL;
              }
    if (!check) {
        temp_num = strtold(str, (char**)&endptr);
        if (endptr == str) {
            endptr = S21_NULL;
        } else {
            temp_num *= flags.flag_minus;
            if (flags.flag_plus) {
                temp_num = fabsl(temp_num);
            }
            (*count_res)++;
            *num = temp_num;
            if (flags.flag_star) {  
                endptr += 2;
            }
        }
    }
    return endptr;
}

int s21_strncasecmp(const char *s1, const char *s2, s21_size_t n) {
    int result = 0;  

    if (n > 0) {
        while (n-- != 0 && (*s1 != '\0' || *s2 != '\0')) {
            if (tolower(*s1) != tolower(*s2)) {
                result = tolower(*s1) - tolower(*s2);
                n = 0;
            }
            s1++;
            s2++;
        }
    }
    return result;
}

int check_nan_or_inf(const char* input, long double* num) {
  int flag = 0;

  if (s21_strncasecmp(input, "nan", 3) == 0) {
    flag = 3;
    *num = NAN;
  }
  else if (s21_strncasecmp(input, "inf", 3) == 0) {
    flag = 3;
    *num = INFINITY;
  }
  else if (s21_strncasecmp(input, "-inf", 4) == 0) {
    flag = 4;
    *num = -INFINITY;
  }
  return flag;
}