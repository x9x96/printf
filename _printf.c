#include "main.h"

void buffer_output(char buffer[], int *index);

/**
 * _printf - prints contents in the buffer to the stdout
 * @format: input format specifier
 * Return: chars to be printed to the stdout
 */
int _printf(const char *format, ...)
{
	int flags, width, precision, size, index = 0;
	int i, printed = 0, printed_chars = 0;
	char buffer[BUFF_SIZE];
	va_list list;

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
		    /*A character from the "format" string is being added*/
		    /*to the "buffer" array at the current "index" position*/
			buffer[index++] = format[i];
			/*"&index" is a pointer to the "index" variable, which allows the*/
			/*"buffer_output" function to modify the value of "index"*/
			if (index == BUFF_SIZE)
				buffer_output(buffer, &index);
			printed_chars++;
		}
		else
		{
			buffer_output(buffer, &index);
			flags = flag_checker(format, &i);
			width = width_checker(format, &i, list);
			precision = precision_checker(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}
	buffer_output(buffer, &index);

	va_end(list);

	return (printed_chars);
}

/**
 * buffer_output - Prints the contents of the buffer if exist
 * @buffer: Array of chars
 * @index: Index at which to add next char, represents the length.
 */
void buffer_output(char buffer[], int *index)
{
	if (*index > 0)
		write(1, &buffer[0], *index);
	*index = 0;
}
