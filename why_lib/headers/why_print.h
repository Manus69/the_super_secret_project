#ifndef WHY_PRINT_H
#define WHY_PRINT_H

#define SPECIAL_CHAR '%'
#define SPECIFIERS "dfsp"

typedef struct why_string_token why_string_token;

struct why_string_token
{
    char *string;

    int width;
    int precision;
    int alignment;
};


#endif