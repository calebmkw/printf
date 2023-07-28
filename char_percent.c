#include "main.h"

/**
 * ConvertChar - Converts an argument to an unsigned char and
 *             stores it to a buffer contained in a struct.
 * @arguments: A va_list pointing to the argument to be converted.
 * @buffer: A buffer_t struct containing a character array.
 * @format_flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int ConvertChar(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length)
{
	char character;
	unsigned int bytes = 0;

	(void)precision;
	(void)length;

	character = va_arg(arguments, int);

	bytes += print_width(buffer, bytes, format_flags, width);
	bytes += _memcpy(buffer, &character, 1);
	bytes += print_neg_width(buffer, bytes, format_flags, width);

	return (bytes);
}

/**
 * ConvertPercent - Stores a percent sign to a
 *                   buffer contained in a struct.
 * @arguments: A va_list pointing to the argument to be converted.
 * @buffer: A buffer_t struct containing a character array.
 * @format_flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 *
 * Return: The number of bytes stored to the buffer (always 1).
 */
unsigned int ConvertPercent(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length)
{
	char percent_sign = '%';
	unsigned int bytes = 0;

	(void)arguments;
	(void)precision;
	(void)length;

	bytes += print_width(buffer, bytes, format_flags, width);
	bytes += _memcpy(buffer, &percent_sign, 1);
	bytes += print_neg_width(buffer, bytes, format_flags, width);

	return (bytes);
}

/**
 * ConvertPointer - Converts the address of an argument to hex and
 *             stores it to a buffer contained in a struct.
 * @arguments: A va_list pointing to the argument to be converted.
 * @buffer: A buffer_t struct containing a character array.
 * @format_flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int ConvertPointer(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length)
{
	char *null_string = "(nil)";
	unsigned long int address;
	unsigned int bytes = 0;

	(void)length;

	address = va_arg(arguments, unsigned long int);
	if (address == '\0')
		return (_memcpy(buffer, null_string, 5));

	format_flags |= 32;
	bytes += convert_ubase(buffer, address, "0123456789abcdef",
			format_flags, width, precision);
	bytes += print_neg_width(buffer, bytes, format_flags, width);

	return (bytes);
}
