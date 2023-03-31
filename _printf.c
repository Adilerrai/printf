#include <stdio.h>
#include <stdarg.h>
#include "main.h"
int _printf(const char *format, ...)
{
    int printed_chars = 0;
    va_list arglist;
    va_start(arglist, format);

    while (*format)
    {
        if (*format == '%')
        {
            format++; // Move past the '%'

            switch (*format)
            {
                case 'c':
                {
                    char c = va_arg(arglist, int);
                    putchar(c);
                    printed_chars++;
                    break;
                }

                case 's':
                {
                    char *s = va_arg(arglist, char *);
                    fputs(s, stdout);
                    printed_chars += strlen(s);
                    break;
                }

                case '%':
                {
                    putchar('%');
                    printed_chars++;
                    break;
                }

                default:
                {
                    printf("Unknown conversion specifier: %%%c\n", *format);
                    return -1;
                }
            }
        }
        else
        {
            putchar(*format);
            printed_chars++;
        }

        format++; // Move to the next character
    }

    va_end(arglist);
    return printed_chars;
}
