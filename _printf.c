#include <stdio.h>
#include <stdarg.h>
#include "main.h"

#define MAX_BUFFER_SIZE 1024

void print_buffer(char buffer[], int *buff_ind) 
	{
	fwrite(buffer, sizeof(char), *buff_ind, stdout);
			*buff_ind = 0;
	}

void print_integer(int value, char buffer[], int *buff_ind)
	{
		int i = 0;
		char digits[20];
		 if (value < 0) 
	{
		buffer[(*buff_ind)++] = '-';
		value = -value;
    }

    do
	{
		digits[i++] = value % 10 + '0';
		value /= 10;
    } 
	while (value > 0);

    while (i > 0) 
	
	 buffer[(*buff_ind)++] = digits[--i];
	}

void print_string(const char *str, char buffer[], int *buff_ind) 
{
    while (*str != '\0')
		buffer[(*buff_ind)++] = *str++;
}

int custom_printf(const char *format, ...) 
{
	va_list args;
	va_start(args, format);

char buffer[MAX_BUFFER_SIZE];
int buff_ind = 0;

while (*format != '\0') 
{
if (*format != '%') 
{
buffer[buff_ind++] = *format++;
if (buff_ind == MAX_BUFFER_SIZE) 
print_buffer(buffer, &buff_ind); 
} 
else
{
format++;
switch (*format) 
{
case 'd': 
{
int value = va_arg(args, int);
print_integer(value, buffer, &buff_ind);
break;
}
case 's':
{
const char *str = va_arg(args, const *char);
print_string(str, buffer, &buff_ind);
break;
}
default:
buffer[buff_ind++] = *format;
break;
}
format++;
}
}

va_end(args);

print_buffer(buffer, &buff_ind);

return buff_ind;
}

int main() {
custom_printf("Hello, %s! The answer is %d.\n", "world", 42);
return 0;
}
