#include "why_constants.h"
#include "why_printf_constants.h"
#include "why_string_functions.h"
#include "why_memory_functions.h"

int why_string_ultoa_buffer(unsigned long number, int base, char *buffer)
{
    char bytes[PRINTF_INT_DBC];
    char *current_pointer;
    int length;

    if (base < 2 || base > 16)
        return 0;
    
    current_pointer = bytes;
    if (!number)
    {
        *current_pointer = '0';
        current_pointer ++;
    }

    while (number)
    {
        *current_pointer = HEX_DIGITS[number % base];
        number = number / base;
        current_pointer ++;
    }
    length = current_pointer - bytes;
    why_memory_copy_backwards(buffer, current_pointer - 1, length);

    return length;
}

int why_string_uitoa_buffer(unsigned int number, int base, char *buffer)
{
    char bytes[PRINTF_INT_DBC];
    char *current_pointer;
    int length;

    if (base < 2 || base > 16)
        return 0;
    
    current_pointer = bytes;
    if (!number)
    {
        *current_pointer = '0';
        current_pointer ++;
    }

    while (number)
    {
        *current_pointer = HEX_DIGITS[number % base];
        number = number / base;
        current_pointer ++;
    }
    length = current_pointer - bytes;
    why_memory_copy_backwards(buffer, current_pointer - 1, length);

    return length;
}

int why_string_itoa_buffer(int number, int base, char *buffer)
{
    unsigned int value;
    char bytes[PRINTF_INT_DBC];
    char *current_pointer;
    int sign;
    int length;

    if (base < 2 || base > 16)
        return 0;

    // why_memory_set(bytes, 0, INT_BUFFER_SIZE);
    current_pointer = bytes;
    sign = 1;
    value = number;
    length = 0;

    if (number < 0 && base == 10)
    {
        sign = -1;
        value = -number;
        *buffer = '-';
        buffer ++;
        length ++;
    }
    current_pointer += why_string_uitoa_buffer(value, base, bytes);
    length += current_pointer - bytes;
    why_memory_copy(buffer, bytes, length);

    return length;
}

char *why_string_itoa(int number, int base)
{
    int length;
    char buffer[PRINTF_INT_DBC];
    char *number_string;

    if (base < 2 || base > 16)
        return NULL;

    why_memory_set(buffer, 0, PRINTF_INT_DBC);
    length = why_string_itoa_buffer(number, base, buffer);
    number_string = why_string_create_from_char_array(buffer, 0, length);

    return number_string;
}