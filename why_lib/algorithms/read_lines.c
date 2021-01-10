#include "why_lib.h"
#include "why_buffer.h"

#include <stdlib.h>

void *why_buffer_read_all_lines_into_structure
(struct why_buffer *buffer, char terminator, void *structure, int (*push)())
{
    int index;
    char *accumulator;
    char *string;

    accumulator = NULL;

    while (!(buffer->status & BUFFER_EOF) || !(buffer->status & BUFFER_EOR))
    {
        if ((buffer->status & BUFFER_READY) || (buffer->status & BUFFER_EOR))
            why_buffer_read_into(buffer, buffer->read_size);
        if ((buffer->status & BUFFER_FULL) && (buffer->status & BUFFER_EOR))
            why_buffer_reset(buffer);

        index = why_string_search_char_array(buffer->read_from_position,
        terminator, 0, buffer->write_into_position - buffer->read_from_position);

        if (index != -1 && !accumulator)
        {
            string = why_buffer_read_from(buffer, index);
            push(structure, string);
            why_buffer_shift_read_position(buffer, 1);
        }
        else if (index != -1 && accumulator)
        {
            string = why_buffer_read_from(buffer, index);
            accumulator = why_string_concat_and_destroy(accumulator, string);
            push(structure, accumulator);
            accumulator = NULL;
            why_buffer_shift_read_position(buffer, 1);
        }
        else
        {
            string = why_buffer_read_from(buffer, buffer->total_capacity);
            accumulator = why_string_concat_and_destroy(accumulator, string);
        }
    }
    if (accumulator)
        push(structure, accumulator);

    return structure;
}