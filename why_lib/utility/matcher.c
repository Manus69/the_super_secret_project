#include "why_matcher_structure.h"
#include "why_matcher_constants.h"
#include "why_math_functions.h"
#include "why_typedefs.h"
#include "why_memory_functions.h"
#include "why_constants.h"
#include "why_string_functions.h"

static inline int max(int a, int b)
{
    return a > b ? a : b;
}

static inline int min(int a, int b)
{
    return a > b ? b : a;
}

static inline int min_but_nonzero(int a, int b)
{
    if (!a)
        return b;
    if (!b)
        return a;
    return a > b ? b : a;
}

why_matcher *why_matcher_create(const char *string)
{
    why_matcher *matcher;

    matcher = malloc(sizeof(why_matcher));
    if (!matcher)
        return NULL;
    
    matcher->string = (char *)string;
    matcher->current_position = matcher->string;
    matcher->match_length = 0;

    return matcher;
}

void why_matcher_reset(why_matcher *matcher, const char *string)
{
    matcher->string = (char *)string;
    matcher->current_position = (char *)string;
    matcher->match_length = 0;
}

int why_matcher_shift_position(why_matcher *matcher, int shift)
{
    char *initial_position;

    initial_position = matcher->current_position;
    if (shift < 0)
    {
        while (shift < 0 && (matcher->current_position - matcher->string))
        {
            matcher->current_position --;
            shift ++;
        }

        return initial_position - matcher->current_position;
    }
    while (shift && (*matcher->current_position != '\0'))
    {
        matcher->current_position ++;
        shift --;
    }

    return matcher->current_position - initial_position;
}

static int match_character(char string_char, char pattern_char)
{
    if (pattern_char == WILDCARD)
        return true;
    else if ((pattern_char == ANY_DIGIT) && why_string_is_digit(string_char))
        return true;
    else if ((pattern_char == ANY_LETTER) && why_string_is_letter(string_char))
        return true;
    else if (string_char == pattern_char)
        return true;

    return false;
}

//the return value is fictitious
int match_and_count(char *string, char *pattern, int (*minmax)(), why_matcher *matcher)
{
    char next_pattern_char;

    if ((*string == '\0' && *pattern == '\0') || *pattern == '\0')
        return (matcher->match_length = minmax(matcher->match_length, string - matcher->current_position));

    next_pattern_char = *(pattern + 1);

    if (*string == '\0' && (next_pattern_char == ZERO_OR_ONE || next_pattern_char == ZERO_OR_MANY))
    {
        if (*(pattern + 2) == '\0')
            return (matcher->match_length = minmax(matcher->match_length, string - matcher->current_position));
        return 0;
    }

    if (*string == '\0')
        return 0;

    if (*pattern == OR || *pattern == '\\')
        pattern ++;

    if (match_character(*string, *pattern))
    {
        if (next_pattern_char == ZERO_OR_MANY)
        {
            match_and_count(string + 1, pattern, minmax, matcher);
            match_and_count(string, pattern + 2, minmax, matcher);
        }
        else if (next_pattern_char == ONE_OR_MANY)
        {
            match_and_count(string + 1, pattern, minmax, matcher);
            match_and_count(string + 1, pattern + 2, minmax, matcher);
        }
        else if (next_pattern_char == ZERO_OR_ONE)
        {
            match_and_count(string + 1, pattern + 2, minmax, matcher);
            match_and_count(string, pattern + 2, minmax, matcher);
        }
        else if (next_pattern_char == END)
        {
            if (*(string + 1) == '\0')
                match_and_count(string + 1, pattern + 2, minmax, matcher);
            else
                return 0;
        }

        while (next_pattern_char == OR)
        {
            pattern = pattern + 2;
            next_pattern_char = *(pattern + 1);
        }

        match_and_count(string + 1, pattern + 1, minmax, matcher);
    }

    if (next_pattern_char == ZERO_OR_MANY || next_pattern_char == ZERO_OR_ONE || next_pattern_char == OR)
        match_and_count(string, pattern + 2, minmax, matcher);

    return 0;
}

int why_matcher_next(why_matcher *matcher, char *pattern, int greedy, int inclusive)
{
    int (*minmax)();

    minmax = greedy ? max : min_but_nonzero;

    while (*(matcher->current_position) != '\0')
    {
        match_and_count(matcher->current_position, pattern, minmax, matcher);

        if (matcher->match_length && inclusive)
            return matcher->match_length;
        if ((matcher->match_length > 1) && !inclusive)
            return matcher->match_length - 1;

        matcher->current_position ++;
    }

    return 0;
}

char *why_matcher_get_next_match(why_matcher *matcher, char *pattern, int greedy, int inclusive)
{
    char *string;
    char *substring;
    int match_length;

    if (*pattern == START)
    {
        if (*(pattern + 1) == *matcher->string)
            pattern ++;
        else
            return NULL;
    }

    match_length = why_matcher_next(matcher, pattern, greedy, inclusive);
    string = matcher->current_position;

    if (match_length)
    {
        substring = why_string_substring(string, 0, match_length);
        matcher->current_position += match_length;
        matcher->match_length = 0;

        return substring;
    }

    return NULL;
}

void why_matcher_destroy(why_matcher **matcher)
{
    // free((*matcher)->string);
    why_memory_destroy((void **)matcher);
}