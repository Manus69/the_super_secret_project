#include "why_lib.h"
#include "why_display.h"

#include <stdio.h>

static const char *item_separator = ";\n";
static const char *string_separator = "\n-------------\n";

void why_display_string(const char *literal)
{
    printf("%s", literal);
}

void why_display_int(int *n)
{
    printf("%d ", *n);
}

void why_display_double(double *x)
{
    printf("%f", *x);
}

void why_display_list(const why_list *list, void (*display_function)())
{
    struct why_list_item *iterator;
    void *content;

    iterator = why_list_get_head_iterator(list);
    if (!iterator)
        return ;
    
    while (iterator != NULL)
    {
        content = why_list_get_content(iterator);
        display_function(content);
        printf("%s", item_separator);
        iterator = why_list_next(iterator);
    }
    printf("LENGTH: %d\n\n", why_list_get_length(list));
}

void why_display_hash_table(const why_hash_table *table, void (*display)())
{
    void **array;
    unsigned int n;
    unsigned int size;

    array = why_hash_table_get_table(table);
    size = why_hash_table_get_size(table);
    n = 0;
    while (n < size)
    {
        printf("index = %u: ", n);
        why_display_list(array[n], why_display_string);
        printf("\n");
        n ++;
    }
}

void why_display_vector(const why_vector *vector, void (*display_function)())
{
    int n;
    int size;
    void *current_item;

    n = 0;
    size = why_vector_get_length(vector);
    while (n < size)
    {
        current_item = why_vector_at(vector, n); //replace with an iterator?
        display_function(current_item);
        printf("%s", item_separator);
        n ++;
    }
    printf("%s", string_separator);
}

void why_display_array(void **array, int number_of_elements, void (*display_functon)())
{
    int n;
    void *current_element;

    n = 0;
    while (n < number_of_elements)
    {
        current_element = array[n];
        display_functon(current_element);
        printf("%s", item_separator);
        n ++;
    }
    printf("\n");
}