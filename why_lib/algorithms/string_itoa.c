#include "why_constants.h"
#include "why_string_functions.h"
#include "why_memory_functions.h"

int why_string_itoa_buffer(int number, int base, char *buffer)
{
    unsigned int value;
    char bytes[INT_BUFFER_SIZE];
    char *current_pointer;
    int sign;
    int length;

    if (base < 2 || base > 16)
        return 0;

    // why_memory_set(bytes, 0, INT_BUFFER_SIZE);
    current_pointer = bytes;
    sign = 1;

    value = number;

    if (number < 0 && base == 10)
    {
        sign = -1;
        value = -number;
    }

    while (value)
    {
        *current_pointer = HEX_DIGITS[value % base];
        value = value / base;
        current_pointer ++;
    }
    if (sign == -1)
    {
        *current_pointer = '-';
        current_pointer ++;
    }
    length = current_pointer - bytes;
    why_memory_copy_backwards(buffer, current_pointer - 1, length); //spooky?

    return length;
}

char *why_string_itoa(int number, int base)
{
    int length;
    char buffer[INT_BUFFER_SIZE];
    char *number_string;

    if (base < 2 || base > 16)
        return NULL;

    why_memory_set(buffer, 0, INT_BUFFER_SIZE);
    length = why_string_itoa_buffer(number, base, buffer);
    number_string = why_string_create_from_char_array(buffer, 0, length);

    return number_string;
}