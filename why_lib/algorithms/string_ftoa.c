#include "why_constants.h"
#include "why_string.h"

struct fpn_representation
{
    int sign;
    int integer;
    double decimal;
};

struct fpn_representation *fpn_representation_create(double x)
{
    struct fpn_representation *representation;

    representation = malloc(sizeof(struct fpn_representation));
    if (!representation)
        return NULL;

    representation->sign = x < 0 ? -1 : 1;
    representation->integer = representation->sign == 1 ? (int)x : (int) -x;
    representation->decimal = x - representation->integer;

    return representation;
}

static int process_decimal_fraction(struct fpn_representation *representation, int precision)
{
    int carry_digit;
    double decimal;
    double adjustment;

    adjustment = 1;
    decimal = representation->decimal;
    while (precision + 1)
    {
        decimal = decimal * 10;
        carry_digit = (int)decimal;
        decimal = decimal - carry_digit;

        adjustment = adjustment / 10;
        precision --;
    }
    
    if (carry_digit >= 5)
    {
        representation->decimal += adjustment;
        if (representation->decimal >= 1)
        {
            representation->integer ++;
            representation->decimal += -1;
        }
    }

    return SUCCESS;
}

//there is some bullshit with . and .0
int why_string_ftoa_buffer(double x, int precision, char *buffer)
{
    struct fpn_representation *representation;
    int length;
    int digit;
    double decimal;

    if (x > INT_MAX || x < INT_MIN)
        x = 0;
    
    representation = fpn_representation_create(x);
    process_decimal_fraction(representation, precision);
    
    length = why_string_itoa_buffer(representation->integer * representation->sign, 10, buffer);
    buffer += length;

    if (precision)
    {
        *buffer = '.';
        buffer ++;
    }

    decimal = representation->decimal;
    while (precision)
    {
        decimal = decimal * 10;
        digit = (int)decimal;
        *buffer = decimal + '0';
        decimal = decimal - digit;
        precision --;
        buffer ++;
    }

    return length + precision + 1;
}