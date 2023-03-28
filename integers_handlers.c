#include "main.h"

/**
 * print_unsigned - prints unsigned numbers
 * @types: arguments list
 * @buffer: buffer array to handle print
 * @flags: flags checker
 * @width: get width.
 * @precision: specifies precision
 * @size: size specifier
 * Return: prints characters
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[n--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[n--] = (num % 10) + '0';
		num /= 10;
	}

	n++;

	return (write_unsgnd(0, n, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: arguments list
 * @buffer: buffer array to handle print
 * @flags: flags checker
 * @width: get width.
 * @precision: specifies precision
 * @size: size specifier
 * Return: prints characters
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int n = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[n--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[n--] = (num % 8) + '0';
		num /= 8;
	}
	if (flags & F_HASH && init_num != 0)
		buffer[n--] = '0';
	n++;

	return (write_unsgnd(0, n, buffer, flags, width, precision, size));
}

/**
 * print_hexadecimal - prints an unsigned number in hexadecimal format
 * @types: arguments list
 * @buffer: buffer array to handle print
 * @flags: flags checker
 * @width: get width.
 * @precision: specifies precision
 * @size: size specifier
 * Return: prints characters
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_hexa_upper - prints an unsigned number in upper hexadecimal notation
 * @types: arguments list
 * @buffer: buffer array to handle print
 * @flags: flags checker
 * @width: get width.
 * @precision: specifies precision
 * @size: size specifier
 * Return: prints characters
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: List of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int n = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[n--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[n--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[n--] = flag_ch;
		buffer[n--] = '0';
	}
	n++;
	return (write_unsgnd(0, n, buffer, flags, width, precision, size));
}
