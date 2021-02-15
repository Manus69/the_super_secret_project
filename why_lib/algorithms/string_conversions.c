#include "why_constants.h"
#include "why_string.h"

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

int why_string_itoa_buffer(int number, int base, char *buffer)
{
    unsigned int value;
    char bytes[INT_BUFFER_SIZE];
    char *current_pointer;
    int sign;
    int length;

    if (base < 2 || base > 16)
        return 0;

    why_memory_set(bytes, 0, INT_BUFFER_SIZE);
    current_pointer = bytes;
    sign = 1;
    value = base == 10 ? -number : number;

    if (number < 0)
    {
        sign = base == 10 ? -1 : 1;
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

    if (length)
        why_memory_copy_backwards(buffer, current_pointer - 1, length);

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
