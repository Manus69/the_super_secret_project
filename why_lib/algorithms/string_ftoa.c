#include "why_constants.h"
#include "why_string.h"

struct fpn_representation
{
    int sign;
    int integer;
    int precision;
    double decimal;
};

struct fpn_representation *fpn_representation_create(double x, int precision)
{
    struct fpn_representation *representation;

    representation = malloc(sizeof(struct fpn_representation));
    if (!representation)
        return NULL;

    representation->sign = x < 0 ? -1 : 1;
    representation->integer = representation->sign == 1 ? (int)x : (int) -x;
    representation->precision = precision;
    representation->decimal = x - representation->integer;

    return representation;
}

static int process_decimal_fraction(struct fpn_representation *representation)
{
    int carry_digit;
    int count;
    double decimal;
    double adjustment;

    adjustment = 10;
    count = 0;
    carry_digit = 0;
    decimal = representation->decimal;
    while (count < representation->precision + 1)
    {
        decimal = decimal * 10;
        carry_digit = (int)decimal;
        decimal = decimal - carry_digit;

        adjustment = adjustment / 10;
        count ++;
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
    
    representation = fpn_representation_create(x, precision);
    process_decimal_fraction(representation);
    
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
        *buffer = digit + '0';
        decimal = decimal - digit;
        precision --;
        buffer ++;
    }

    precision = representation->precision;
    free(representation);

    return length + precision + 1;
}

//limit precision?
char *why_string_ftoa(double x, int precision)
{
    char buffer[DOUBLE_BUFFER_SIZE];
    char *current;
    char *string;
    int length;

    why_memory_set(buffer, 0, DOUBLE_BUFFER_SIZE);
    current = buffer;
    length = why_string_ftoa_buffer(x, precision, buffer);
    string = why_string_create_from_char_array(current, 0, length);

    return string;
}