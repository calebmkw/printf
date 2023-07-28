#include "main.h"

/**
 * ConvertHexLower - Converts an unsigned int argument to hex using abcdef
 *             and stores it to a buffer contained in a struct.
 * @arguments: A va_list pointing to the argument to be converted.
 * @buffer: A buffer_t struct containing a character array.
 * @format_flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int ConvertHexLower(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length)
{
	unsigned long int number;
	unsigned int bytes = 0;
	char *prefix = "0x";

	if (length == LONG)
		number = va_arg(arguments, unsigned long int);
	else
		number = va_arg(arguments, unsigned int);
	if (length == SHORT)
		number = (unsigned short)number;

	if (HASH_FLAG == 1 && number != 0)
		bytes += _memcpy(buffer, prefix, 2);

	if (!(number == 0 && precision == 0))
		bytes += convert_ubase(buffer, number, "0123456789abcdef",
				format_flags, width, precision);

	bytes += print_neg_width(buffer, bytes, format_flags, width);

	return (bytes);
}

/**
 * ConvertHexUpper - Converts an unsigned int argument to hex using ABCDEF
 *             and stores it to a buffer contained in a struct.
 * @arguments: A va_list pointing to the argument to be converted.
 * @buffer: A buffer_t struct containing a character array.
 * @format_flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int ConvertHexUpper(va_list arguments, buffer_t *buffer,
		unsigned char format_flags, int width, int precision, unsigned char length)
{
	unsigned long int number;
	unsigned int bytes = 0;
	char *prefix = "0X";

	if (length == LONG)
		number = va_arg(arguments, unsigned long);
	else
		number = va_arg(arguments, unsigned int);
	if (length == SHORT)
		number = (unsigned short)number;

	if (HASH_FLAG == 1 && number != 0)
		bytes += _memcpy(buffer, prefix, 2);

	if (!(number == 0 && precision == 0))
		bytes += convert_ubase(buffer, number, "0123456789ABCDEF",
				format_flags, width, precision);

	bytes += print_neg_width(buffer, bytes, format_flags, width);

	return (bytes);
}
