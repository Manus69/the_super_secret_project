#ifndef WHY_LIB_H
#define WHY_LIB_H


typedef struct why_buffer why_buffer;

why_buffer *why_buffer_create(const char *file_name, int capacity, int read_size);

void why_buffer_destroy(why_buffer **buffer);
void why_buffer_reset(why_buffer *buffer);

char *why_buffer_flush(why_buffer *buffer);
char *why_buffer_read_from(why_buffer *buffer, int number_of_bytes);

enum why_buffer_status why_buffer_read_into(why_buffer *buffer, int number_of_bytes);
enum why_buffer_status why_buffer_read_into_default(why_buffer *buffer);
enum why_buffer_status why_buffer_shift_read_position(why_buffer *buffer, int shift);
enum why_buffer_status why_buffer_get_status(const why_buffer *buffer);

void *why_buffer_read_all_lines_into_structure
(why_buffer *buffer, char terminator, void *structure, int (*push)());


#endif