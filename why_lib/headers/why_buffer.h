#ifndef WHY_BUFFER_H
#define WHY_BUFFER_H

#define DEFAULT_BUFFER_CAPACITY (1 << 13)
#define DEFAULT_READ_SIZE (1 << 13)

void why_buffer_reset(why_buffer *buffer);

char *why_buffer_flush(why_buffer *buffer);

enum why_buffer_status why_buffer_read_into(why_buffer *buffer, int number_of_bytes);
enum why_buffer_status why_buffer_read_into_default(why_buffer *buffer);
enum why_buffer_status why_buffer_shift_read_position(why_buffer *buffer, int shift);
enum why_buffer_status why_buffer_get_status(const why_buffer *buffer);

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