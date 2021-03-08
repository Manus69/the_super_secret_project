#include "why_constants.h"
#include "why_string_functions.h"
#include "why_macros.h"
#include "why_printf_constants.h"
#include "why_print_structures.h"
#include "why_memory_functions.h"

void reset_fpn_representation(struct fpn_representation *representation, double x, int precision)
{
    representation->sign = x < 0 ? -1 : 1;
    representation->integer = representation->sign == 1 ? (unsigned int)x : (unsigned int) -x;
    representation->precision = precision;
    representation->decimal = ABS(x) - representation->integer;
}

struct fpn_representation *fpn_representation_create(double x, int precision)
{
    struct fpn_representation *representation;

    representation = malloc(sizeof(struct fpn_representation));
    if (!representation)
        return NULL;

    reset_fpn_representation(representation, x, precision);

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
    
    if (1 - decimal < PRINTF_EPSILON)
        carry_digit ++;
    
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
    // struct fpn_representation *representation;
    struct fpn_representation representation;
    int length;
    int digit;
    double decimal;

    if (x > INT_MAX || x < INT_MIN)
        x = 0;
    
    // representation = fpn_representation_create(x, precision);
    reset_fpn_representation(&representation, x, precision);
    // process_decimal_fraction(representation);
    process_decimal_fraction(&representation);

    
    // length = why_string_itoa_buffer(representation->integer * representation->sign, 10, buffer);
    length = why_string_itoa_buffer(representation.integer * representation.sign, 10, buffer);

    buffer += length;

    if (length + precision >= PRINTF_DOUBLE_DBC)
        precision = PRINTF_DOUBLE_DBC - length;

    if (precision)
    {
        *buffer = '.';
        buffer ++;
    }

    // decimal = representation->decimal;
    decimal = representation.decimal;
    while (precision)
    {
        decimal = decimal * 10;
        digit = (int)decimal;
        *buffer = digit + '0';
        decimal = decimal - digit;
        precision --;
        buffer ++;
    }

    // precision = representation->precision;
    precision = representation.precision;
    length = precision ? length + precision + 1 : length;
    // free(representation);

    return length;
}

//limit precision?
char *why_string_ftoa(double x, int precision)
{
    char buffer[PRINTF_DOUBLE_DBC];
    char *current;
    char *string;
    int length;

    why_memory_set(buffer, 0, PRINTF_DOUBLE_DBC);
    current = buffer;
    length = why_string_ftoa_buffer(x, precision, buffer);
    string = why_string_create_from_char_array(current, 0, length);

    return string;
}