#ifndef WHY_PRINT_H
#define WHY_PRINT_H

#define SPECIAL_CHAR '%'
#define SPECIFIERS "dfsp"

typedef struct why_string_token why_string_token;

enum token_type
{
    D, F, S, P, PERCENT_SYMBOL, TEXT, BRICKED,
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