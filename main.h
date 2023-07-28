#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Modifier Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (format_flags & 1)
#define SPACE_FLAG ((format_flags >> 1) & 1)
#define HASH_FLAG ((format_flags >> 2) & 1)
#define ZERO_FLAG ((format_flags >> 3) & 1)
#define NEG_FLAG ((format_flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */

typedef struct buffer_s
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct converter_s - A new type defining a converter struct.
 * @specifier: A character representing a conversion specifier.
 * @func: A pointer to a conversion function corresponding to specifier.
 */

typedef struct converter_s
{
	unsigned char specifier;
	unsigned int (*func)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */

typedef struct flag_s
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);
void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);

/* Conversion Specifier Functions */
unsigned int ConvertChar(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length);
unsigned int store_string(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len);
unsigned int ConvertPercent(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length);
unsigned int ConvertPointer(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length);
unsigned int ConvertHexLower(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length);
unsigned int ConvertHexUpper(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length);
unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char format_flags, int wid, int prec, unsigned char len);
unsigned int convert_binary(va_list params, buffer_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char length);
unsigned int convert_octal(va_list params, buffer_t *buffer,
		 unsigned char modifiers, int width, int precision, unsigned char length);
unsigned int convert_decimal(va_list params, buffer_t *buffer,
		unsigned char modifiers, int width, int precision, unsigned char length);

/* Handlers */
/**
 * handle_specifiers - handle.
 * @flag_ptr: A pointer to a potential string of flags.
 * @fmt_ptr: A pointer to the current index of the format string.
 * Return: If flag characters are found - a bitwise value of the flags.
 */
unsigned char get_flag_value(const char *flag_ptr, char *fmt_ptr);
unsigned char get_length_value(const char *mod_ptr, char *fmt_ptr);
int get_width_value(va_list args, const char *mod_ptr, char *fmt_ptr);
int get_precision_value(va_list args, const char *mod_ptr, char *fmt_ptr);
unsigned int(*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Modifiers */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char format_flags, int wid);
unsigned int print_string_width(buffer_t *output,
		unsigned char format_flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char format_flags, int wid);

/* Helper Functions */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int convert_sbase(buffer_t *output_buffer, long int number,
		char *base_string, unsigned char format_flags, int min_width, int precision);
unsigned int convert_ubase(buffer_t *output_buffer, unsigned long int number,
		char *base_string, unsigned char format_flags, int min_width, int precision);
#endif
