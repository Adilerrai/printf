#include <stdarg.h>
#include <stdio.h>
#include "main.h"
/**
 * _printf - Custom printf function that supports some conversion specifiers
 *
 * @format: A string that contains text and conversion specifiers
 * @...: Zero or more arguments that correspond to the conversion specifiers
 *
 * Return: The number of characters printed (excluding the null byte used to end
 * the output to strings) or a negative value if an error occurs.
 */
int _printf(const char *format, ...)
{
    int chars_printed = 0;  // The number of characters printed so far
    va_list args;           // A variable-length argument list

    // Initialize the argument list to point to the first optional argument
    va_start(args, format);

    // Loop over the characters in the format string
    while (*format != '\0')
    {
        // If the current character is not a percent sign, print it as is
        if (*format != '%')
        {
            putchar(*format);
            chars_printed++;
        }
        // Otherwise, process the next character as a conversion specifier
        else
        {
            // Advance the format string pointer to the next character
            format++;

            // Check if the next character is a valid conversion specifier
            if (*format == 'c')
            {
                // Print the next character argument as a character
                char c = (char) va_arg(args, int);
                putchar(c);
                chars_printed++;
            }
            else if (*format == 's')
            {
                // Print the next string argument
                const char *s = va_arg(args, const char *);
                while (*s != '\0')
                {
                    putchar(*s);
                    s++;
                    chars_printed++;
                }
            }
            else if (*format == 'd' || *format == 'i')
            {
                // Print the next integer argument
                int n = va_arg(args, int);
                int sign = (n < 0) ? -1 : 1;
                n *= sign;
                int digit_count = 0;
                int temp = n;
                do {
                    temp /= 10;
                    digit_count++;
                } while (temp > 0);
                if (sign < 0)
                {
                    putchar('-');
                    chars_printed++;
                }
                while (digit_count > 0)
                {
                    int divisor = 1;
                    for (int i = 1; i < digit_count; i++)
                        divisor *= 10;
                    int digit = n / divisor;
                    n %= divisor;
                    putchar('0' + digit);
                    chars_printed++;
                    digit_count--;
                }
            }
            else if (*format == 'u')
            {
                // Print the next unsigned integer argument
                unsigned int n = va_arg(args, unsigned int);
                unsigned int digit_count = 0;
                unsigned int temp = n;
                do {
                    temp /= 10;
                    digit_count++;
                } while (temp > 0);
                while (digit_count > 0)
                {
                    unsigned int divisor = 1;
                    for (unsigned int i = 1; i < digit_count; i++)
                        divisor *= 10;
                    unsigned int digit = n / divisor;
                    n %= divisor;
                    putchar('0' + digit);
                    chars_printed++;
                    digit_count--;
                }
            }
            else if (*format == 'o')
            {
                // Print the next unsigned integer argument as an octal number
                unsigned int n = va_arg(args, unsigned int);
                unsigned int digit_count = 
