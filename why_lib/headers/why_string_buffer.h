#ifndef WHY_STRING_BUFFER_H
#define WHY_STRING_BUFFER_H

#define DEFAULT_CAPACITY 1 << 10

struct why_string_buffer
{
    char *content;
    char *current;
    char *end;
};

#endif