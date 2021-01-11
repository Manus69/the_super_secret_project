#include "why_string.h"

int why_string_get_length(const char *literal)
{
    int n;

    if (!literal)
        return 0;

    n = 0;
    while (literal[n] != '\0')
        n ++;
    
    return n;
}

char *why_string_create(const char *literal) //literal is assumed to be nul terminated
{
    char *string;
    int length;

    if (!literal)
        return NULL;

    length = why_string_get_length(literal);

    if ((string = malloc(length + 1)))
    {
        string = why_memory_copy(string, literal, length);
        string[length] = '\0';

        return string;
    }
    
    return NULL;        
}

char *why_string_create_shallow(const char *char_string)
{
    return (char *)char_string;
}

char *why_string_create_from_char_array(const char *char_array, int left_index, int length)
{
    char *string;

    if (!char_array)
        return NULL;

    if ((string = malloc(length + 1)))
    {
        string = why_memory_copy(string, &char_array[left_index], length);
        string[length] = '\0';

        return string;
    }

    return NULL;
}

void why_string_destroy(char **string)
{
    if (!string || !*string)
        return ;
        
    free(*string);
    *string = NULL;
}

char *why_string_copy(const char *old_string)
{
    char *copy;
    int length;

    if (!old_string)
        return NULL;

    length = why_string_get_length(old_string);

    if ((copy = malloc(length + 1)))
    {
        copy = why_memory_copy(copy, old_string, length);
        copy[length] = '\0';

        return copy;
    }
    
    return NULL;
}


char *why_string_substring(const char *string, int left_index, int length)
{
    char *substring;
    int n;

    if (!string)
        return NULL;

    substring = malloc(length + 1);
    if (!substring)
        return NULL;
    
    n = 0;
    while (length)
    {
        substring[n] = string[left_index];
        n ++;
        left_index ++;
        length --;
    }
    substring[n] = '\0';

    return substring;
}

char *why_string_concat(const char *left, const char *right)
{
    int left_length;
    int right_length;
    int total_length;
    char *string;

    if (!left && !right)
        return NULL;

    left_length = why_string_get_length(left);
    right_length = why_string_get_length(right);
    total_length = left_length + right_length;

    if ((string = malloc(total_length + 1)))
    {
        string = why_memory_copy(string, left, left_length);
        why_memory_copy(&string[left_length], right, right_length);
        string[total_length] = '\0';

        return string;
    }

    return NULL;
}

char *why_string_concat_and_destroy(char *lhs, char *rhs)
{
    char *result;

    result = why_string_concat(lhs, rhs);
    why_string_destroy(&lhs);
    why_string_destroy(&rhs);

    return result;
}

int why_string_get_index_of(const char *literal, char c)
{
    int n;

    if (!literal)
        return -1;

    n = 0;
    while (literal[n] != '\0')
    {
        if (c == literal[n])
            return n;
        n ++;
    }

    return -1;
}

int why_string_search_char_array(const char *array, char c, int left_index, int number_of_bytes)
{
    if (!array)
        return -1;

    while (number_of_bytes)
    {
        if (array[left_index] == c)
            return left_index;

        left_index ++;
        number_of_bytes --;
    }

    return -1;
}

char *why_string_join(const char *lhs, const char *joint, const char *rhs)
{
    int lhs_length;
    int rhs_length;
    int joint_length;
    int total_length;
    char *result;

    if (!joint)
        return why_string_concat(lhs, rhs);

    lhs_length = why_string_get_length(lhs);
    rhs_length = why_string_get_length(rhs);
    joint_length = why_string_get_length(joint);
    total_length = lhs_length + joint_length + rhs_length;

    if ((result = malloc(total_length + 1)))
    {
        why_memory_copy(result, lhs, lhs_length);
        why_memory_copy(result + lhs_length, joint, joint_length);
        why_memory_copy(result + lhs_length + joint_length, rhs, rhs_length);
        result[total_length] = '\0';

        return result;
    }

    return NULL;
}

int why_string_compare(const char *lhs, const char *rhs)
{
    if (!lhs && !rhs)
        return 0;
    
    if (!lhs)
        return 1;
    
    if (!rhs)
        return -1;

    while (*lhs && *rhs)
    {
        if (*lhs != *rhs)
            break ;

        lhs ++;
        rhs ++;
    }

    return *lhs < *rhs ? -1 : *lhs > *rhs;
}

int why_string_compare_mk2(const char *lhs, const char *rhs)
{
    int n;

    if (!lhs && !rhs)
        return 0;
    
    if (!lhs)
        return 1;
    
    if (!rhs)
        return -1;

    n = 0;
    while (lhs[n] == rhs[n])
    {
        if (lhs[n] == '\0')
            break ;
        n ++;
    }

    return lhs[n] - rhs[n];
}

int why_string_compare_test(const void *lhs, const void *rhs)
{
    const char *left;
    const char *right;

    left = lhs;
    right = rhs;

    while (*left && *right)
    {
        if (*left != *right)
            break ;

        left ++;
        right ++;
    }

    return *left < *right ? -1 : *left > *right;
}

int why_string_is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int why_string_is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}