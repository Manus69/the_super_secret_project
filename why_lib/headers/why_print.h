#ifndef WHY_PRINT_H
#define WHY_PRINT_H

#define SPECIAL_CHAR '%'
#define SPECIFIERS "dfsp"

typedef struct why_string_token why_string_token;

enum token_type
{
    D, F, S, P, PERCENT_SYMBOL, TEXT, BROKEN,
};

struct why_string_token
{
    char *string;

    enum token_type type;

    int length;
    int width;
    int precision;
    int alignment;
};


#endif