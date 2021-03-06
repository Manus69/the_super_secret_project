#include "why_buffer_structure.h"
#include "why_buffer_functions.h"
#include "why_string_functions.h"
#include "why_constants.h"

#include <stdlib.h>
#include <fcntl.h> //unix only
#include <sys/stat.h>
#include <unistd.h>

static int get_file_descriptor(const char *file_name)
{
    int file;

    if (file_name == NULL || file_name == STDIN_FILENO)
        return STDIN_FILENO;
    
    file = open(file_name, O_RDONLY);
    
    return file;
}

void why_buffer_reset(struct why_buffer *buffer)
{
    buffer->write_into_position = buffer->content;
    buffer->read_from_position = buffer->content;
    buffer->status = BUFFER_READY;

    // why_memory_set(buffer->content, 0, buffer->total_capacity); //
}

struct why_buffer *why_buffer_create(const char *file_name, int capacity, int read_size)
{
    struct why_buffer *buffer;
    int file;
    
    if ((file = get_file_descriptor(file_name)) < 0)
        return NULL;

    capacity = capacity < 1 ? BUFFER_DBC : capacity;
    read_size = read_size < 1 ? BUFFER_DRS : read_size;
    read_size = read_size > capacity ? capacity : read_size;

    if ((buffer = malloc(sizeof(struct why_buffer))))
    {
        if ((buffer->content = malloc(capacity + 1)))
        {
            buffer->file = file;
            buffer->read_size = read_size;
            buffer->total_capacity = capacity;

            buffer->content[capacity] = '\0';
            // why_memory_set(buffer->content, 0, capacity + 1); //

            buffer->terminal_position = &buffer->content[capacity];
            why_buffer_reset(buffer);

            return buffer;
        }
        free(buffer);
    }

    return NULL;
}

void why_buffer_destroy(struct why_buffer **buffer)
{
    if (!buffer || !*buffer)
        return ;

    if ((*buffer)->file != STDIN_FILENO)
        close((*buffer)->file);

    free((*buffer)->content);
    free(*buffer);
    *buffer = NULL;
}

static enum why_buffer_status evaluate_buffer_after_input(why_buffer *buffer, int bytes_written)
{
    int bytes_availible;

    bytes_availible = buffer->terminal_position - buffer->write_into_position;

    if (bytes_availible == 0)
        buffer->status |= BUFFER_FULL;

    if (bytes_written == 0)
        buffer->status |= BUFFER_EOF;

    if (bytes_written && (buffer->status & BUFFER_EOR))
        buffer->status = (buffer->status & ~BUFFER_EOR);

    if ((buffer->status & BUFFER_READY) && (buffer->status != BUFFER_READY))
        buffer->status &= ~BUFFER_READY;

    return buffer->status;
}

static enum why_buffer_status evaluate_buffer_after_output(why_buffer *buffer, int bytes_read)
{
    if (buffer->write_into_position - buffer->read_from_position == 0)
        buffer->status |= BUFFER_EOR;
    
    bytes_read = bytes_read; //remove later

    return buffer->status;
}

enum why_buffer_status why_buffer_read_into(struct why_buffer *buffer, int number_of_bytes)
{
    int remaining_capacity;

    remaining_capacity = buffer->terminal_position - buffer->write_into_position;

    if (buffer->status & BUFFER_FULL)
        return BUFFER_FULL;
    
    if (remaining_capacity < number_of_bytes)
        number_of_bytes = remaining_capacity;
    
    number_of_bytes = read(buffer->file, buffer->write_into_position, number_of_bytes);

    buffer->write_into_position += number_of_bytes;

    evaluate_buffer_after_input(buffer, number_of_bytes);

    return buffer->status;
}

char *why_buffer_read_from(struct why_buffer *buffer, int number_of_bytes)
{
    char *string;
    int unread_bytes;

    unread_bytes = buffer->write_into_position - buffer->read_from_position;

    if (unread_bytes < number_of_bytes)
        number_of_bytes = unread_bytes;

    string = why_string_create_from_char_array(buffer->read_from_position, 0, number_of_bytes);

    buffer->read_from_position += number_of_bytes;
    
    evaluate_buffer_after_output(buffer, number_of_bytes);

    return string;
}

char *why_buffer_flush(struct why_buffer *buffer)
{
    char *string;
    int length;

    length = buffer->write_into_position - buffer->read_from_position;
    string = why_string_create_from_char_array(buffer->content, 0, length);
    why_buffer_reset(buffer);

    return string;
}

enum why_buffer_status why_buffer_shift_read_position(why_buffer *buffer, int shift)
{
    int unread_bytes;

    unread_bytes = buffer->write_into_position - buffer->read_from_position;

    if (unread_bytes > shift)
    {
        buffer->read_from_position += shift;
    }
    else
    {
        buffer->read_from_position += unread_bytes;
        buffer->status |= BUFFER_EOR;
    }

    return buffer->status;
}

enum why_buffer_status why_buffer_get_status(const struct why_buffer *buffer)
{
    return buffer->status;
}