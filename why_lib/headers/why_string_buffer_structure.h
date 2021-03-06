#ifndef WHY_STRING_BUFFER_STRUCTURE_H
#define WHY_STRING_BUFFER_STRUCTURE_H

struct why_string_buffer
{
    char *content;
    char *current;
    char *end;
};

#endif