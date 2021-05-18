#include "why_display_functions.h"
#include "why_printf_structures.h"
#include "why_list_functions.h"
#include "why_hash_table_functions.h"
#include "why_vector_functions.h"
#include "why_string_functions.h"
#include "why_memory_functions.h"
#include "why_printf_functions.h"
#include "why_typedefs.h"
#include "why_polynomial_functions.h"

// #include <stdio.h> //

static const char *item_separator = " ";
static const char *string_separator = "\n-------------\n";

void why_display_string(const char *literal)
{
    why_printf("%s", literal);
}

void why_display_int(int *n)
{
    why_printf("%d", *n);
}

void why_display_double(double *x)
{
    why_printf("%f", *x);
}

void why_display_string_token(const void *token)
{
    why_printf("%s", ((why_string_token *)token)->string);
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
        why_printf("%s", item_separator);
        iterator = why_list_next(iterator);
    }
    why_printf("LENGTH: %d\n\n", why_list_get_length(list));
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
        why_printf("index = %u: ", n);
        why_display_list(array[n], display); //?
        why_printf("\n");
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
        why_printf("%s", item_separator);
        n ++;
    }
    why_printf("%s", string_separator);
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
        why_printf("%s", item_separator);
        n ++;
    }
    why_printf("\n");
}

void why_display_polynomial(why_real_polynomial *polynomial)
{
    int n;
    int degree;
    double coefficient;

    if (!polynomial)
        return ;
        
    n = 0;
    degree = why_polynomial_get_degree(polynomial);
    while (n <= degree)
    {
        coefficient = why_polynomial_get_coefficient(polynomial, n);
        if (coefficient)
            why_printf("%.3f", coefficient);
        else
        {
            n ++;
            continue ;
        }
        if (n > 1)
        {
            why_printf("x^%d ", n);
        }
        else if (n == 1)
            why_printf("x");
        if (n < degree)
            why_printf(" + ");
        n ++;
    }
    why_printf("\n");
}