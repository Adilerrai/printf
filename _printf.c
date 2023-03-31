#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include "main.h"
int _putchar(char c)
{
    return write(1, &c, 1);
}

int _printf(const char *format, ...)
{
    va_list args;
    int printed_chars = 0;
    va_start(args, format);

    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c': {
                    char c = (char) va_arg(args, int);
                    _putchar(c);
                    printed_chars++;
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
                    while (*s != '\0') {
                        _putchar(*s);
                        s++;
                        printed_chars++;
                    }
                    break;
                }
                case '%': {
                    _putchar('%');
                    printed_chars++;
                    break;
                }
                default:
                    // unsupported conversion specifier
                    break;
            }
        } else {
            _putchar(*format);
            printed_chars++;
        }
        format++;
    }

    va_end(args);
    return printed_chars;
}

