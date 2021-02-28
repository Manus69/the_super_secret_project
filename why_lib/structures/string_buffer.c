#include "why_string_buffer.h"
#include "why_memory.h"
#include "why_constants.h"
#include "why_string.h"
#include "why_typedefs.h"
#include "why_lib.h"

#include <stdlib.h>

why_string_buffer *why_string_buffer_create(int size)
{
    why_string_buffer *buffer;

    if (size <= 0)
        size = DEFAULT_CAPACITY;

    buffer = malloc(sizeof(why_string_buffer));
    if (!buffer)
        return NULL;

    buffer->content = why_memory_get_zeroes(size + 1);
    if (!buffer->content)
        return NULL;
    
    buffer->current = buffer->content;
    buffer->end = buffer->content + size;

    return buffer;
}

void why_string_buffer_destory(why_string_buffer **buffer)
{
    if (!buffer || !*buffer)
        return ;
    
    why_memory_destroy((void **)&((*buffer)->content));
    why_memory_destroy((void **)buffer);
}

char *why_string_buffer_get_content(const why_string_buffer *buffer)
{
    return buffer->content;
}

int why_string_buffer_get_current_capacity(const why_string_buffer *buffer)
{
    return buffer->end - buffer->current;
}

int why_string_buffer_get_total_capacity(const why_string_buffer *buffer)
{
    return buffer->end - buffer->content;
}

int why_string_buffer_realloc(why_string_buffer *buffer, int extra_capacity)
{
    char *new_content;
    int old_capacity;
    int old_index;

    old_capacity = why_string_buffer_get_total_capacity(buffer);

    if (extra_capacity <= 0)
        extra_capacity = old_capacity;
    else if (extra_capacity < old_capacity)
        extra_capacity = old_capacity;

    old_index = buffer->current - buffer->content;

    new_content = why_memory_get_zeroes(old_capacity + extra_capacity + 1);
    if (!new_content)
        return FAILURE;

    why_memory_copy(new_content, buffer->content, old_capacity);
    why_memory_destroy((void **)&buffer->content);

    buffer->content = new_content;
    buffer->current = new_content + old_index;
    buffer->end = new_content + old_capacity + extra_capacity;

    return SUCCESS;    
}

int why_string_buffer_check_capacity(why_string_buffer *buffer, int requirement)
{
    int capacity;

    capacity = why_string_buffer_get_current_capacity(buffer);
    if (requirement > capacity)
    {
        if (why_string_buffer_realloc(buffer, requirement) == FAILURE)
            return 0;
    }

    return SUCCESS;
}

int why_string_buffer_write_string(why_string_buffer *buffer, const char *string)
{
    int length;

    length = why_string_get_length(string);

    if (why_string_buffer_check_capacity(buffer, length) == FAILURE)
        return FAILURE;

    why_memory_copy(buffer->current, string, length);
    buffer->current += length;

    return length;
}

void *why_string_buffer_write_string_rvp(why_string_buffer *buffer, const char *string)
{
    if (!buffer)
    {
        if (!(buffer = why_string_buffer_create(DEFAULT_CAPACITY)))
            return NULL;        
    }
    why_string_buffer_write_string(buffer, string);

    return buffer;
}

int why_string_buffer_write_string_backwards(why_string_buffer *buffer, const char *string)
{
    int length;

    length = why_string_get_length(string);

    if (why_string_buffer_check_capacity(buffer, length) == FAILURE)
        return FAILURE;

    why_memory_copy_backwards(buffer->current, string, length);
    buffer->current += length;

    return length;
}
