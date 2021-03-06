#include "why_constants.h"
#include "why_string_functions.h"

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
