#include "why_lib.h"
#include "why_matcher.h"

#include "why_math.h"

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
    
    // matcher->string = why_string_create(string); //check return?
    matcher->string = (char *)string;
    matcher->pattern = NULL;
    matcher->current_position = matcher->string;
    matcher->match_length = 0;
    matcher->quantifier = 0;

    return matcher;
}

void why_matcher_reset(why_matcher *matcher, const char *string)
{
    matcher->string = (char *)string;
    matcher->current_position = (char *)string;
    matcher->match_length = 0;
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
    char next_char;

    if ((*string == '\0' && *pattern == '\0') || *pattern == '\0')
        return (matcher->match_length = minmax(matcher->match_length, string - matcher->current_position));

    next_char = *(pattern + 1);

    if (*string == '\0' && (next_char == ZERO_OR_ONE || next_char == ZERO_OR_MANY))
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
        if (next_char == ZERO_OR_MANY)
        {
            match_and_count(string + 1, pattern, minmax, matcher);
            match_and_count(string, pattern + 2, minmax, matcher);
        }
        else if (next_char == ONE_OR_MANY)
        {
            match_and_count(string + 1, pattern, minmax, matcher);
            match_and_count(string + 1, pattern + 2, minmax, matcher);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            match_and_count(string + 1, pattern + 2, minmax, matcher);
            match_and_count(string, pattern + 2, minmax, matcher);
        }

        while (next_char == OR)
        {
            pattern = pattern + 2;
            next_char = *(pattern + 1);
        }

        match_and_count(string + 1, pattern + 1, minmax, matcher);
    }

    if (next_char == ZERO_OR_MANY || next_char == ZERO_OR_ONE || next_char == OR)
        match_and_count(string, pattern + 2, minmax, matcher);

    return 0;
}

int why_matcher_next(why_matcher *matcher, char *pattern, int greedy)
{
    int (*minmax)();

    minmax = greedy ? max : min_but_nonzero;

    while (*(matcher->current_position) != '\0')
    {
        match_and_count(matcher->current_position, pattern, minmax, matcher);

        if (matcher->match_length)
            return matcher->match_length;

        matcher->current_position ++;
    }

    return 0;
}

char *why_matcher_get_next_match(why_matcher *matcher, char *pattern, int greedy)
{
    char *string;
    char *substring;
    int match_length;

    match_length = why_matcher_next(matcher, pattern, greedy);
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