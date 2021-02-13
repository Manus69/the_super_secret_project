#include "why_constants.h"
#include "why_string.h"

#define SIZE 16

int why_string_atoi(const char *string)
{
    long result;
    int sign;
    int left_digit_index; 

    if (!string)
        return 0;

    sign = 1;
    result = 0;
    left_digit_index = why_string_get_index_of_any(string, DIGITS, 0);

    if (left_digit_index == -1)
        return result;
    if (left_digit_index && (string[left_digit_index - 1] == '-'))
        sign = -1;

    string += left_digit_index;
    while (*string != '\0')
    {
        if (!why_string_is_digit(*string))
            break ;

        result = 10 * result + *string - '0';
        string ++;
    }

    return (int)(result * sign);
}

int why_string_itoa_buffer(int number, int base, char *buffer, int buffer_size)
{
    long value;
    char bytes[SIZE];
    char *current_pointer;
    int sign;
    int length;

    if (base < 2 || base > 16 || buffer_size == 0)
        return 0;

    why_memory_set(bytes, 0, SIZE);
    current_pointer = bytes;
    sign = 1;
    value = number;

    if (number < 0)
    {
        sign = -1;
        value = -number;
    }

    while (value)
    {
        *current_pointer = (value % base) + '0';
        value = value / base;
        current_pointer ++;
    }
    if (sign == -1)
    {
        *current_pointer = '-';
        current_pointer ++;
    }
    length = current_pointer - bytes;
    length = (buffer_size <= length) ? length : buffer_size;
    why_memory_copy_backwards(buffer, current_pointer, length);

    return length;
}

char *why_string_itoa(int number, int base)
{
    int length;
    char buffer[SIZE];
    char *number_string;

    if (base < 2 || base > 16)
        return NULL;

    why_memory_set(buffer, 0, SIZE);
    length = why_string_itoa_buffer(number, base, buffer, SIZE);
    number_string = why_string_create_from_char_array(buffer, 0, length);

    return number_string;
}

int why_string_ftoa_buffer(double x, int precision, int buffer_size)
{
    ;
}

char *why_sting_ftoa(double x, int precision)
{
    ;
}