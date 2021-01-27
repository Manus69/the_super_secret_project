#include "why_lib.h"
#include "why_string.h"

#define DEFAULT_VECTOR_SIZE 16

struct why_vector *why_string_split(const char *literal, char separator)
{
    struct why_vector *vector;
    char *string;
    char *current_position;
    char *separator_position;
    int distance_to_separator;


    vector = why_vector_create(DEFAULT_VECTOR_SIZE, why_memory_shallow_copy, why_string_destroy);

    current_position = (char *)literal;
    separator_position = (char *)literal;
    distance_to_separator = 0;
    
    while (*separator_position == separator)
    {
        current_position ++;
        separator_position ++;
    }

    while (*separator_position != '\0')
    {
        if (*separator_position == separator)
        {
            distance_to_separator = separator_position - current_position;
            string = why_string_create_from_char_array(current_position, 0, distance_to_separator);
            why_vector_push(vector, string);
            current_position = separator_position + 1;
        }
        separator_position ++;
    }
    distance_to_separator = separator_position - current_position;
    string = why_string_create_from_char_array(current_position, 0, distance_to_separator);
    why_vector_push(vector, string);

    return vector;
}

static int get_index_of_digit(const char *string, int starting_index)
{
    while (string[starting_index] != '\0')
    {
        if (why_string_is_digit(string[starting_index]))
            return starting_index;
        starting_index ++;
    }

    return -1;
}

int why_string_get_index_of_any(const char *string, const char *char_set, int starting_index)
{
    if (!string || !char_set)
        return -1;
    if (starting_index < 0)
        return -1;
    if (char_set == (char *)DIGITS) //is this bad?
        return get_index_of_digit(string, starting_index);

    while (string[starting_index] != '\0')
    {
        if (why_string_get_index_of(char_set, string[starting_index]) != -1)
            return starting_index;
        starting_index ++;
    }

    return -1;
}

char *why_string_find_char(const char *string, const char *set)
{
    while (*string != '\0')
    {
        if (why_string_get_index_of(set, *string) != -1)
            return (char *)string;
        string ++;
    }

    return (char *)string; //this is not right
}

int why_string_atoi(const char *string)
{
    long result;
    int sign;
    int left_digit_index; 

    if (!string)
        return 0;

    sign = 1;
    result = 0;
    left_digit_index = why_string_get_index_of_any(string, DIGITS, 0);

    if (left_digit_index == -1)
        return result;
    if (left_digit_index && (string[left_digit_index - 1] == '-'))
        sign = -1;

    string += left_digit_index;
    while (*string != '\0')
    {
        if (!why_string_is_digit(*string))
            break ;

        result = 10 * result + *string - '0';
        string ++;
    }

    return (int)(result * sign);
}