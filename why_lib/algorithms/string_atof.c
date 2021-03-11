#include "why_constants.h"
#include "why_string_functions.h"

struct number
{
    unsigned int integer;
    double decimal;
    int sign;
    char dot_encountered;
};

struct number number_reset(struct number *number)
{
    number->integer = 0;
    number->decimal = 0;
    number->sign = 1;
    number->dot_encountered = false;
}

double why_string_atof(const char *number_string)
{
    struct number number;
    double base;

    if (!number_string)
        return 0;

    number_reset(&number);
    base = 1.0;
    while (*number_string != '\0')
    {
        if (why_string_is_digit(*number_string))
        {
            if (number.dot_encountered == false)
                number.integer = number.integer * 10 + *number_string - '0';
            else
            {
                base = base * 10;
                number.decimal = number.decimal + ((*number_string - '0') / base);
            }
        }
        else if (*number_string == '-')
            number.sign = -1;
        else if (*number_string == '.')
        {
            number.dot_encountered = true;
        }
        number_string ++;
    }

    return (number.integer + number.decimal) * number.sign;
}