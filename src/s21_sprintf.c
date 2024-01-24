#include "s21_string.h"

int print_symbol(const char *str, int symbol);
int print_text(const char *str, const char *format, s21_size_t *index);

void parcer(const char *str, const char *format, s21_size_t *index, va_list list);
void get_length(const char *format, s21_size_t *index, STRSPEC *spec);
int get_precision(const char *format, s21_size_t *index, STRSPEC *spec, va_list list);
void get_width(const char *format, s21_size_t *index, STRSPEC *spec, va_list list);
unsigned int value_width_precision(const char *format, s21_size_t *index);
void get_flags(const char *format, s21_size_t *index, STRSPEC *spec);

void output(const char *str, va_list list, STRSPEC *spec);
void print_value(const char *str, STRSPEC *spec, char *value_buffer);
void output_str(const char *str, va_list list, STRSPEC *spec);
void output_symbols_count(va_list list);

void output_whole(const char *str, va_list list, STRSPEC *spec);
s21_size_t  binary_to_decimal_value(const char *binary_buffer, STRSPEC *spec);
void  decimal_to_decimal_buffer(s21_size_t value, char *decimal_buffer);
void binary_to_octal_hex(const char *binary_buffer, char octal_hex_type, char *octal_hex_buffer);
void variable_to_binary(const void *value, int val_size, char *binary_buffer);
int whole_var_size(STRSPEC *spec);

void output_real(const char *str, va_list list, STRSPEC *spec);
void fill_corr_buffer(char *corr_buffer, long precision);
void fill_with_zeros(char *value_buffer, s21_size_t next_index);
void round_real(char *value_buffer, long precision);
void exp_real(char *decimal_real, STRSPEC *spec);
s21_size_t dot_place(const char *value_buffer);
void trim_real(char *value_buffer, STRSPEC *spec);
void fill_real_e(char *value_buffer, STRSPEC *spec);

void swap(char *x, char *y);
void turn_over(char *array);
void trim_last_zero(char *array);
double s21_int_pow(int number, int degree);
void addition(const char *buffer1, const char *buffer2, char *result_buffer);
void multiply_by_number(const char *buffer, int number, int place, char *result_buffer);
void multiplication_exp(const char *buffer, int number, int exp, char *result_buffer);
void multiplication(const char *buffer1, const char *buffer2, char *result_buffer);
void real_mantissa(const char *binary_buffer, char *result_buffer);
void dot_move(char *value_buffer, int step);
void multiplication_exp_negative(const char *buffer, int exp, char *result_buffer);
void copy_buffer(const char *buffer, char *result_buffer);
s21_size_t long_exponentiation(int number, int degree);
void bin_exp_array(char *temp_result_arr, double temp_result);

// --------------------------------------------------------------------

int s21_sprintf(char *str, const char *format, ...) {
    va_list list;
    va_start(list, format);

	int call_parcer = 1;
	s21_size_t index = 0;
	
	*str = 0;

	while(call_parcer) {
			parcer(str, format, &index, list);
			call_parcer = print_text(str, format, &index);
	}
    
    va_end(list);

	return print_symbol(str, '\0');
}

int print_symbol(const char *str, int symbol) {
	static int symbols_count = 0;
	char *result_str = (char *)str;

	if(result_str) {
		if(!*result_str) symbols_count = 0;
		result_str[symbols_count] = symbol;
		if(symbol != 0) symbols_count++;
	}

	return symbols_count;
}

int print_text(const char *str, const char *format, s21_size_t *index) {
	int call_parcer = 0;

	while (*index < s21_strlen(format) && !call_parcer) {
		if(format[*index] == '%') {
			call_parcer = 1;
		} else {
			print_symbol(str, format[*index]);
			*index += 1;
		}
	}

	return call_parcer;
}

void get_flags(const char *format, s21_size_t *index, STRSPEC *spec) {
	int no_flags = 0;

	while (*index < s21_strlen(format) && !no_flags) {
		if(format[*index] == '-') {
			spec->minus = 1;
			*index += 1;
		} else if(format[*index] == '+') {
			spec->plus = 1;
			*index += 1;
		} else if(format[*index] == ' ') {
			spec->space = 1;
			*index += 1;
		} else if(format[*index] == '#') {
			spec->hash = 1;
			*index += 1;
		} else if(format[*index] == '0') {
			spec->zero = 1;
			*index += 1;
		} else {
			no_flags = 1;
		}
	}

	if(spec->minus == 1) spec->zero = 0;
	if(spec->space) spec->sign = ' ';
	if(spec->plus) spec->sign = '+';
}

unsigned int value_width_precision(const char *format, s21_size_t *index) {
	unsigned int result = 0;
	int numbers = 1;

		while (*index < s21_strlen(format) && numbers) {
			if(format[*index] >= '0' && format[*index] <= '9') {
				result *= 10;
				result += format[*index] - '0';
				*index += 1;
			} else {
				numbers = 0;
			}
		}
	
	return result;
}

void get_width(const char *format, s21_size_t *index, STRSPEC *spec, va_list list) {
	long result = 0;

	if(format[*index] == '*') {
		result = va_arg(list, long);
		if(result < 0) {
			result *= -1;
			spec->minus = 1;
		}
		spec->width = result;
		*index += 1;
	} else if(format[*index] >= '0' && format[*index] <= '9') {
		spec->width = value_width_precision(format, index);
	}
}

int get_precision(const char *format, s21_size_t *index, STRSPEC *spec, va_list list) {
	spec->precision = 6;
	int result = 1;

	if(format[*index] == '.') {
		spec->dot = 1;
		*index += 1;
		spec->precision = 0;
		if(format[*index] == '*') {
			result = va_arg(list, long);
			if(result > 0) {
				spec->precision = result;
			}

			*index += 1;
		} else if(format[*index] >= '0' && format[*index] <= '9') {
			spec->precision = value_width_precision(format, index);
		}

	}

	return result;
}

void get_length(const char *format, s21_size_t *index, STRSPEC *spec) {
	if(format[*index] == 'h') {
		*index += 1;
		spec->length_h = 1;
		if(format[*index] == 'h') {
			*index += 1;
			spec->length_h = 2;
		}
	} else if(format[*index] == 'l') {
		*index += 1;
		spec->length_l = 1;
		if(format[*index] == 'l') {
			*index += 1;
			spec->length_l = 2;
		}
	} else if(format[*index] == 'L') {
		*index += 1;
		spec->length_L = 1;
	}
}

void parcer(const char *str, const char *format, s21_size_t *index, va_list list) {
	STRSPEC spec = {0};
	char *types = "seEfgGcdiuoxXpn";
	char *type_ptr = NULL;

	int no_prec_error = 1;
	s21_size_t start_index = *index, start_length;

	if(format[*index] == '%') {	
		*index += 1;
		if(format[*index] == '%') {
			print_symbol(str, format[*index]);
			*index += 1;
		} else {
			get_flags(format, index, &spec);
			get_width(format, index, &spec, list);
			no_prec_error = get_precision(format, index, &spec, list);
			start_length = *index;
			get_length(format, index, &spec);

			type_ptr = s21_strchr(types, format[*index]);
			if(type_ptr && no_prec_error) {
				spec.type = type_ptr[0];
				*index += 1;
				output(str, list, &spec);
			} else {
				s21_size_t finish_index;
				if(!no_prec_error)
					finish_index = *index;
				else
					finish_index = start_length;
				
				for(s21_size_t i = start_index; i < finish_index; i++)
					print_symbol(str, format[i]);
			}
		}
	}
}

void output(const char *str, va_list list, STRSPEC *spec) {
	if(spec->type == 'c' || spec->type == 'd' || spec->type == 'i' || spec->type == 'u' || spec->type == 'o' || spec->type == 'x' || spec->type == 'X' || spec->type == 'p') {
		output_whole(str, list, spec);
	} else if(spec->type == 'e' || spec->type == 'E' || spec->type == 'f' || spec->type == 'g' || spec->type == 'G') {
		output_real(str, list, spec);
	} else if(spec->type == 's') {
		output_str(str, list, spec);
	} else if(spec->type == 'n') {
		output_symbols_count(list);
	}
}

void print_value(const char *str, STRSPEC *spec, char *value_buffer) {
	s21_size_t len_total = s21_strlen(value_buffer);

	if((spec->type == 'o' || spec->type == 'x' || spec->type == 'X') && spec->hash) {
		len_total++;
		if(spec->type == 'x' || spec->type == 'X') len_total++;		
	}
	
	if(spec->sign) {
		len_total++;
	}

	int spaces = 0;
	if(spec->type == 's' && spec->dot == 1) {
		if(spec->width > spec->precision) spaces = spec->width - spec->precision;
	} else {
		if(spec->width > len_total) spaces = spec->width - len_total;
	}

	if(spaces && !spec->minus) {
		if(spec->space_symbol == '0') {
			if(spec->sign) {
				print_symbol(str, spec->sign);
				spec->sign = 0;
			}

			if((spec->type == 'o' || spec->type == 'x' || spec->type == 'X') && spec->hash) {
				print_symbol(str, '0');
				if(spec->type == 'x' || spec->type == 'X') print_symbol(str, spec->type);		
			}
		}
		while(spaces--) 
			print_symbol(str, spec->space_symbol);
	}

	if(spec->sign) {
		print_symbol(str, spec->sign);
	}

	if((spec->type == 'o' || spec->type == 'x' || spec->type == 'X') && spec->hash && spec->space_symbol != '0') {
		print_symbol(str, '0');
		if(spec->type == 'x' || spec->type == 'X') print_symbol(str, spec->type);		
	}

	if(spec->type == 's' && spec->dot == 1) {
		for(s21_size_t i = 0; i < spec->precision && value_buffer[i]; i++) print_symbol(str, value_buffer[i]);
	} else {
		while(*value_buffer) print_symbol(str, *value_buffer++);
	}

	if(spaces && spec->minus) {
		while(spaces--) 
			print_symbol(str, spec->space_symbol);
	}
}

void output_str(const char *str, va_list list, STRSPEC *spec) {
	char *str_var = va_arg(list, char *);
	spec->space_symbol = ' ';
	spec->sign = 0;
	print_value(str, spec, str_var);
}

void output_symbols_count(va_list list) {
	int *count_var = va_arg(list, int *);
	*count_var = print_symbol(NULL, 0);
}

void fill_corr_buffer(char *corr_buffer, long precision) {
	*corr_buffer++ = '1';

	if(precision) {
		precision--;
		while(precision--) {
			*corr_buffer++ = '0';
		}
		*corr_buffer++ = '.';
		*corr_buffer = '0';
	}
}

void fill_with_zeros(char *value_buffer, s21_size_t next_index) {
	s21_size_t length = s21_strlen(value_buffer);
	for(s21_size_t i = length; i < next_index; i++) value_buffer[i] = '0';
	value_buffer[next_index] = '\0';
}

void round_real(char *value_buffer, long precision) {
	char corr_buffer[max_buf_size] = {0};
	fill_corr_buffer(corr_buffer, precision);
	char temp_buffer[max_buf_size] = {0};
	turn_over(value_buffer);
	addition(value_buffer, corr_buffer, temp_buffer);
	copy_buffer(temp_buffer, value_buffer);
	turn_over(value_buffer);
}

void exp_real(char *decimal_real, STRSPEC *spec) {
	s21_size_t length = s21_strlen(decimal_real);
	int exp = spec->exp;

	if(decimal_real[0] == '0' && decimal_real[1] == '.') {
		for(s21_size_t i = 2; i < length; i++) {
			swap(&decimal_real[i - 1], &decimal_real[i]);
			exp--;
			if(decimal_real[i - 1] != '0') i = length;
		}

		spec->exp = exp;
		turn_over(decimal_real);
		trim_last_zero(decimal_real);
		turn_over(decimal_real);
	} else {
		for(int i = length - 1; i > 1; i--) {
			if(decimal_real[i] == '.') {
				swap(&decimal_real[i - 1], &decimal_real[i]);
				exp++;
			}
		}

		spec->exp = exp;
	}
}

s21_size_t dot_place(const char *value_buffer) {
	s21_size_t result = 0, flag = 1;
	
	while(*value_buffer && flag) {
		result++;
		if(*value_buffer++ == '.') {
			flag = 0;
		}
	}

	return result;
}

void trim_real(char *value_buffer, STRSPEC *spec) {
	s21_size_t length = s21_strlen(value_buffer), dot_index = dot_place(value_buffer);
	
	if(dot_index) {
		s21_size_t next_index = dot_index + spec->precision, increment = 0;
		if(next_index < length) {
			if(value_buffer[next_index] > '4') increment = 1;
		}

		if(!spec->precision) next_index--;

		fill_with_zeros(value_buffer, next_index);
		if(increment) round_real(value_buffer, spec->precision);
	}
}

void fill_real_e(char *value_buffer, STRSPEC *spec) {
	s21_size_t length = s21_strlen(value_buffer);
	char exp_buffer[min_buf_size] = {0};
	char *ptr_exp_buf = exp_buffer;
	short exp = spec->exp;
	int exp_sign = '+', zero1 = 0, zero2 = 0;

	value_buffer[length++] = spec->type;

	if(exp < 0) {
		exp_sign = '-';
		exp *= -1;
	}

	if(exp < 10) zero1 = '0';
	if(exp == 0) zero2 = '0';

	int i = 0;
	while(exp) {
		exp_buffer[i++] = exp % 10 + '0';
		exp /= 10;
	}

	if(zero2) exp_buffer[i++] = zero2;
	if(zero1) exp_buffer[i++] = zero1;
	exp_buffer[i++] = exp_sign;
	exp_buffer[i] = '\0';
	turn_over(exp_buffer);

	while(*ptr_exp_buf) value_buffer[length++] = *ptr_exp_buf++;

	value_buffer[length] = '\0';
}

void output_real(const char *str, va_list list, STRSPEC *spec) {
	char binary_buffer[min_buf_size] = {0};
	char binary_mantissa[min_buf_size] = {0};
	char decimal_mantissa[max_buf_size] = {0};
	char decimal_real[max_buf_size] = {0};
	char value_buffer_f[max_buf_size] = {0};
	char value_buffer_e[max_buf_size] = {0};
	int exp, mant_size;

	if(spec->length_L == 1) {
		long double ldbl_var = va_arg(list, long double);
		variable_to_binary(&ldbl_var, sizeof(long double), binary_buffer);
		union un_ldouble var = {0};
		var.real = ldbl_var;
		exp = var.fld.exp - 16383;
		mant_size = 63;
		spec->negative = var.fld.sign;
		if(spec->negative) spec->sign = '-';
	} else {
		double dbl_var = va_arg(list, double);
		variable_to_binary(&dbl_var, sizeof(double), binary_buffer);
		union un_double var = {0};
		var.real = dbl_var;
		exp = var.fld.exp - 1023;
		mant_size = 52;
		spec->negative = var.fld.sign;
		if(spec->negative) spec->sign = '-';
	}

	for(int i = 0; i < mant_size; i++)	{
		binary_mantissa[i] = binary_buffer[i];
	}

	turn_over(binary_mantissa);
	real_mantissa(binary_mantissa, decimal_mantissa);
	if(exp >= 0) {
		multiplication_exp(decimal_mantissa, 2, exp, decimal_real);
	} else {
		multiplication_exp_negative(decimal_mantissa, exp, decimal_real);
	}

	turn_over(decimal_real);
	trim_last_zero(decimal_real);

	if(spec->zero)
		spec->space_symbol = '0';
	else
		spec->space_symbol = ' ';

	if(spec->type == 'f') {
		copy_buffer(decimal_real, value_buffer_f);
		trim_real(value_buffer_f, spec);
		print_value(str, spec, value_buffer_f);
	} else if(spec->type == 'e' || spec->type == 'E') {
		copy_buffer(decimal_real, value_buffer_e);
		exp_real(value_buffer_e, spec);
		trim_real(value_buffer_e, spec);
		exp_real(value_buffer_e, spec);
		trim_real(value_buffer_e, spec);
		fill_real_e(value_buffer_e, spec);
		print_value(str, spec, value_buffer_e);
	}
}

s21_size_t  binary_to_decimal_value(const char *binary_buffer, STRSPEC *spec) {	
	int last_bit = s21_strlen(binary_buffer) - 1;
	s21_size_t value = 0;

    for(int i = 0; i <= last_bit; i++) {
		value += (binary_buffer[i] - '0') * (s21_size_t)s21_int_pow(binary_radix, i);
	}

	if(spec->type != 'u' && spec->type != 'o' && spec->type != 'x' && spec->type != 'X') {
		s21_size_t first_negative = (s21_size_t)s21_int_pow(binary_radix, last_bit);
		if(value >= first_negative) {
			value = first_negative * 2 - value;
			spec->sign = '-';
			spec->negative = 1;
		} 
	}

	return value;
}

void  decimal_to_decimal_buffer(s21_size_t value, char *decimal_buffer) {
	int i = 0;

	do {
		decimal_buffer[i] = value % decimal_radix + '0';
		value /= decimal_radix;
		i++;
	} while(value);

	decimal_buffer[i] = '\0';
	turn_over(decimal_buffer);
}

void binary_to_octal_hex(const char *binary_buffer, char octal_hex_type, char *octal_hex_buffer) {	
	int step_length = 4, last_bit = s21_strlen(binary_buffer) - 1;
	int step_sum = 0, place = 0, step_count = 0, hex_symbol = 'a';

	if(octal_hex_type == 'X') {
		hex_symbol = 'A';
	} else if(octal_hex_type == 'o') {
		hex_symbol = '\0';
		step_length = 3;
	}
	
    for (int i = 0; i <= last_bit; i++) {
		step_sum += (binary_buffer[i] - '0') * (int)s21_int_pow(binary_radix, place);
		place++;
		if(place == step_length || i == last_bit) {
			if(step_sum < 10) 
				step_sum += '0';
			else
				step_sum = hex_symbol + step_sum - 10;
			octal_hex_buffer[step_count++] = step_sum;
			step_sum = 0;
			place = 0;
		}
	}

	step_count--;
	while(step_count && octal_hex_buffer[step_count] == '0') octal_hex_buffer[step_count--] = '\0';

	turn_over(octal_hex_buffer);
}

void variable_to_binary(const void *value, int val_size, char *binary_buffer) {
    unsigned char *ptr = (unsigned char *)value;
	if(val_size > 10) val_size = 10;
	int length = val_size * byte_size;
	binary_buffer[length--] = '\0';

    for (int i = val_size - 1; i >= 0; i--) {
        for (int j = byte_size - 1; j >= 0; j--) {
	        unsigned char bit = (ptr[i] >> j) & 1;
			if(length >= 0) binary_buffer[length--] = bit + '0';
        }
    }
}

int whole_var_size(STRSPEC *spec) {
	int var_size = sizeof(int);

	if(spec->length_h == 2 || spec->type == 'c') {
		var_size = sizeof(char);
	} else if(spec->length_h == 1) {
		var_size = sizeof(short);
	} else if(spec->length_l || spec->length_L) {
		var_size = sizeof(long);
	}

	return var_size;
}

void output_whole(const char *str, va_list list, STRSPEC *spec) {
	char binary_buffer[min_buf_size] = {0};
	char value_buffer[min_buf_size] = {0};
	char *ptr_val = value_buffer;

	if (spec->type == 'p') {
		spec->type = 'x';
		spec->length_l = 1;
		spec->hash = 1;
	}

	int var_size = whole_var_size(spec);
	void *ptr_var = va_arg(list, void *);
	variable_to_binary(&ptr_var, var_size, binary_buffer);

//	int sign = 0;
	if(spec->type == 'o' || spec->type == 'x' || spec->type == 'X') {
		binary_to_octal_hex(binary_buffer, spec->type, ptr_val);
		if(s21_strlen(ptr_val) == 1 && *ptr_val == '0') spec->hash = 0;
	} else {
		s21_size_t value =  binary_to_decimal_value(binary_buffer, spec);
		if(spec->type == 'd' || spec->type == 'i' || spec->type == 'u') {
			decimal_to_decimal_buffer(value, ptr_val);
		} else if(spec->type == 'c') {
			spec->sign = 0;
			*ptr_val = (char)value;
		} 
	}

	if(!spec->dot && spec->zero && spec->type != 'c')
		spec->space_symbol = '0';
	else
		spec->space_symbol = ' ';

	print_value(str, spec, value_buffer);
}






void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void turn_over(char *array) {
    s21_size_t i = 0, j = s21_strlen(array) - 1;

    while (i < j) {
        swap(array + i, array + j);
        i++;
        j--;
    }
}

void trim_last_zero(char *array) {
    s21_size_t max_len = s21_strlen(array) - 1;

	while (array[max_len] == '0' && max_len) {
		array[max_len] = '\0';
	    max_len--;
	}
}

double s21_int_pow(int number, int degree) {
	double exp_result = 1.0;
	int sign = 0;

	if(degree < 0) {
		sign = 1;
		degree *= -1;
	}

	while(degree--) {
		exp_result *= number;
	}

	if(sign) exp_result = 1.0 / exp_result;

	return exp_result;
}

void addition(const char *buffer1, const char *buffer2, char *result_buffer) {
	int len1 = s21_strlen(buffer1), len2 = s21_strlen(buffer2);
	int max_len = len1 > len2 ? len1 : len2;

	int temp2 = 0;
	for (int i = 0; i < max_len; i++) {
		if(buffer1[i] == '.') {
			result_buffer[i] = '.';
			continue;
		}
	    int temp1 = temp2;
		if(i < len1) temp1 += buffer1[i] - '0';
		if(i < len2) temp1 += buffer2[i] - '0';
	    temp2 = temp1 / 10;
	    result_buffer[i] = temp1 % 10 + '0';
	}

	if (temp2 > 0) {
	    result_buffer[max_len] = temp2 + '0';
	}

	while (result_buffer[max_len] == '0' && max_len) {
		result_buffer[max_len] = '\0';
	    max_len--;
	}
}

void multiply_by_number(const char *buffer, int number, int place, char *result_buffer) {
	int length = s21_strlen(buffer), dot_pos = 0;

    int temp2 = 0;
    for (int i = 0; i < length; i++) {
		if(buffer[i] == '.') {
			result_buffer[i + place] = '.';
			dot_pos = i;
			continue;
		}
		int temp1 = temp2 + (buffer[i] - '0') * number;
	    temp2 = temp1 / 10;
	    result_buffer[i + place] = temp1 % 10 + '0';
	}

    if (temp2 > 0) {
        result_buffer[length + place] = temp2 + '0';
    }

	for(int i = 0; i < place; i++) {
		result_buffer[i] += '0';
	};

	if(dot_pos) {
		for(int j = dot_pos + place; j > dot_pos; j--) {
			result_buffer[j] = result_buffer[j - 1];
		};

		result_buffer[dot_pos] = '.';
	}

	trim_last_zero(result_buffer);
}

void copy_buffer(const char *buffer, char *result_buffer) {
	int length = s21_strlen(buffer);

	for(int i = 0; i < length; i++)
		result_buffer[i] = buffer[i];

	result_buffer[length] = '\0';
}

void multiplication_exp(const char *buffer, int number, int exp, char *result_buffer) {
	char temp_buffer[max_buf_size] = {0};
	
	copy_buffer(buffer, temp_buffer);
	
	while(exp--) {
		multiply_by_number(temp_buffer, number, 0, result_buffer);
		copy_buffer(result_buffer, temp_buffer);
	}
}

void multiplication(const char *buffer1, const char *buffer2, char *result_buffer) {
    int length2 = s21_strlen(buffer2);

	for(int i = 0; i < length2; i++) {
		char temp_buffer[max_buf_size] = {0}, temp_buffer_result[max_buf_size] = {0};
		copy_buffer(result_buffer, temp_buffer_result);
		multiply_by_number(buffer1, buffer2[i] - '0', i, temp_buffer); 
		addition(temp_buffer, temp_buffer_result, result_buffer);
	}
}

void multiplication_exp_negative(const char *buffer, int exp, char *result_buffer) {
	char temp_buffer[max_buf_size] = {0};
	
	copy_buffer(buffer, temp_buffer);
	
	while(exp++) {
		char temp_buffer2[max_buf_size] = {0};		
		multiply_by_number(temp_buffer, 5, 0, temp_buffer2);
		dot_move(temp_buffer2, 1);
		copy_buffer(temp_buffer2, temp_buffer);
	}

	copy_buffer(temp_buffer, result_buffer);
}

s21_size_t long_exponentiation(int number, int degree) {
	s21_size_t exp_result = 1;
	
	while(degree--) {
		exp_result *= number;
	}

	return exp_result;
}

void dot_move(char *value_buffer, int step) {
	int length = s21_strlen(value_buffer), dot_place = 0;
	
//	char *temp = strchr(value_buffer, '.');	

	for(int i = 0; i < length; i++) {
		if(value_buffer[i] == '.') dot_place = i;
	}

	for(int j = dot_place; j < dot_place + step; j++) {
		if(!value_buffer[j + 1]) value_buffer[j + 1] = '0';
		swap(&value_buffer[j], &value_buffer[j + 1]);
	}

	length = s21_strlen(value_buffer);

	if(value_buffer[length - 1] == '.') value_buffer[length] = '0';
}

void bin_exp_array(char *temp_result_arr, double temp_result) {
	int whole;
	double temp_whole, temp_fraction;

	for(int i = 0; i < 60; i++) {
		temp_result *= 10;
		temp_fraction = modf (temp_result, &temp_whole);
		whole = (int)temp_whole;
		temp_result_arr[i] = whole + '0';
		temp_result = temp_fraction;
	}

	turn_over(temp_result_arr);
	s21_size_t length = s21_strlen(temp_result_arr);
	temp_result_arr[length++] = '.';
	temp_result_arr[length] = '0';
}

void real_mantissa(const char *binary_buffer, char *result_buffer) {
	double temp_result;
    int length = s21_strlen(binary_buffer);  // 40, 310, 4940
	char result_buff2[100] = {0}, result_buff3[100] = {0};

	for (int i = 0; i < length; i++) {
		if(binary_buffer[i] - '0') {
			char temp_result_arr[100] = {0};
			s21_size_t bin_exp = long_exponentiation(2, i + 1);
			temp_result = 1.0 / (double)bin_exp;
			bin_exp_array(temp_result_arr, temp_result);
			addition(temp_result_arr, result_buff2, result_buff3);
			copy_buffer(result_buff3, result_buff2);
		}
	}

	copy_buffer(result_buff3, result_buffer);
	length = s21_strlen(result_buffer);
	result_buffer[length - 1] = '1';
}