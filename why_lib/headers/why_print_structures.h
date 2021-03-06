#ifndef WHY_PRINT_STRUCTURES_H
#define WHY_PRINT_STRUCTURES_H

struct fpn_representation
{
    int sign;
    int integer;
    int precision;
    double decimal;
};

enum token_type
{
    D, F, S, P, PERCENT_SYMBOL, TEXT, BRICKED,
};

enum state
{
    INSIDE = 1, OUTSIDE,
};

struct why_string_token
{
    char *string;

    enum token_type type;

    int string_length;
    int actual_length;
    
    int width;
    int precision;
    int alignment;
};

#endif