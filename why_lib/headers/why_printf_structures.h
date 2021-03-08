#ifndef WHY_PRINTF_STRUCTURES_H
#define WHY_PRINTF_STRUCTURES_H

struct fpn_representation
{
    int sign;
    unsigned int integer;
    int precision;
    double decimal;
};

enum token_type
{
    D, F, S, P, X, PERCENT_SYMBOL, TEXT, BRICKED, UNKNOWN
};

enum state
{
    INSIDE = 1, OUTSIDE,
};

//this is all wrong
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

struct why_printf_token
{
    char *start;
    char *end;

    enum token_type type;

    int width;
    int precision;
    int alignment;
    char padding_char;

    char eos;
    char width_processed;
    char precision_processed;
    char alignment_processed;
    char dot_encountered;
};

#endif