#include <stdarg.h> // for va_list, va_start, va_arg, va_end
#include <unistd.h> // for write

#define BUFF_SIZE 1024 // size of the output buffer

/**
 * _printf - prints a formatted string to stdout
 * @format: a string containing zero or more directives
 * Return: the number of characters printed (excluding the null byte used to end output to strings)
 */
int _printf(const char *format, ...)
{
    int i, printed = 0, printed_chars = 0;
    int flags, width, precision, size, buff_ind = 0;
    va_list list;
    char buffer[BUFF_SIZE];

    if (format == NULL)
        return (-1);

    va_start(list, format);

    for (i = 0; format && format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
            {
                write(1, buffer, buff_ind);
                buff_ind = 0;
            }
            printed_chars++;
        }
        else
        {
            if (format[i + 1] == '%')
            {
                buffer[buff_ind++] = '%';
                i++;
                printed_chars++;
            }
            else if (format[i + 1] == 'c')
            {
                char c = (char) va_arg(list, int);
                buffer[buff_ind++] = c;
                i++;
                printed_chars++;
            }
            else if (format[i + 1] == 's')
            {
                char *s = va_arg(list, char *);
                int j;

                if (s == NULL)
                    s = "(null)";

                for (j = 0; s[j] != '\0'; j++)
                {
                    buffer[buff_ind++] = s[j];
                    if (buff_ind == BUFF_SIZE)
                    {
                        write(1, buffer, buff_ind);
                        buff_ind = 0;
                    }
                }

                i++;
                printed_chars += j;
            }
        }
    }

    if (buff_ind > 0)
        write(1, buffer, buff_ind);

    va_end(list);

    return (printed_chars);
}
/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
