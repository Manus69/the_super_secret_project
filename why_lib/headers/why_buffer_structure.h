#ifndef WHY_BUFFER_STRUCTURE_H
#define WHY_BUFFER_STRUCTURE_H

enum why_buffer_status
{
    BUFFER_DEFAULT = 1,
    BUFFER_READY = BUFFER_DEFAULT << 1,
    BUFFER_FULL = BUFFER_DEFAULT << 2,
    BUFFER_EOF = BUFFER_DEFAULT << 3,
    BUFFER_EOR = BUFFER_DEFAULT << 4,
};

struct why_buffer
{
    char *content;
    char *write_into_position;
    char *read_from_position;
    char *terminal_position;

    int file;
    int read_size;
    int total_capacity;  
    
    enum why_buffer_status status;
};

#endif