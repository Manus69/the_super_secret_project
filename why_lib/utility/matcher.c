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
    matcher->token_length = 0;
    matcher->min_pattern_length = 0;

    return matcher;
}

void why_matcher_reset(why_matcher *matcher)
{
    matcher->current_position = matcher->string;
    matcher->token_length = 0;
}

int why_matcher_get_token_length(const why_matcher *matcher)
{
    return matcher->token_length;
}

int why_matcher_get_min_pattern_length(const why_matcher *matcher)
{
    return matcher->min_pattern_length;
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

int get_min_pattern_length(char *pattern)
{
    int length;
    char next_char;

    if (!pattern)
        return 0;

    length = 0;
    while (*pattern != '\0')
    {
        next_char = *(pattern + 1);
        if (*pattern == ESCAPE)
        {
            pattern ++;
        }
        else if (next_char == ZERO_OR_ONE || next_char == ZERO_OR_MANY || next_char == OR)
        {
            pattern += 2;
        }
        else
        {
            length ++;
            pattern ++;
        }
    }

    return length ? length : 1;
}

int match_and_count(char *string, char *pattern)
{
    char string_char;
    char pattern_char;
    char next_char;

    int shift_match;
    int skip_match;

    string_char = *string;
    pattern_char = *pattern;

    if (string_char == '\0')
        return 0;

    if (pattern_char == '\\')
        pattern_char = *(pattern + 1);

    if (pattern_char == '\0')
        return 0;

    next_char = *(pattern + 1);
    if (match_character(string_char, pattern_char))
    {
        if (next_char == ZERO_OR_MANY)
        {
            shift_match = match_and_count(string + 1, pattern);

            if (*(pattern + 2) == '\0')
                return 1;

            skip_match = match_and_count(string, pattern + 2);

            if (!shift_match && !skip_match)
                return 0;

            return MAX(1 + shift_match, skip_match);
            // return MIN(1 + shift_match, skip_match);

        }
        else if (next_char == ONE_OR_MANY)
        {
            shift_match = match_and_count(string + 1, pattern);

            if (*(pattern + 2) == '\0')
                return 1;

            skip_match = match_and_count(string + 1, pattern + 2);

            if (!shift_match && !skip_match)
                return 0;

            return 1 + MAX(shift_match, skip_match);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            shift_match = match_and_count(string + 1, pattern + 2);

            if (*(pattern + 2) == '\0')
                return 1;

            skip_match = match_and_count(string, pattern + 2);

            if (!shift_match && !skip_match)
                return 0;

            return MAX(1 + shift_match, skip_match);
        }

        while (next_char == OR)
        {
            pattern = pattern + 2;
            next_char = *(pattern + 1);
        }

        return 1 + match_and_count(string + 1, pattern + 1);
    }

    if (next_char == ZERO_OR_MANY || next_char == ZERO_OR_ONE || next_char == OR)
    {
        return match_and_count(string, pattern + 2);
    }

    return 0;
}

int match_and_count_mk2(char *string, char *pattern, int (*minmax)())
{
    char next_char;
    int shift_match;
    int skip_match;

    if (*string == '\0')
        return 0;

    if (*pattern == '\\')
        pattern = pattern + 1;

    if (*pattern == '\0')
        return 0;

    next_char = *(pattern + 1);
    if (match_character(*string, *pattern))
    {
        if (next_char == ZERO_OR_MANY)
        {
            shift_match = match_and_count_mk2(string + 1, pattern, minmax);

            if (*(pattern + 2) == '\0')
                return 1 + shift_match; //// 
                // return 1;

            skip_match = match_and_count_mk2(string, pattern + 2, minmax);

            if (!shift_match && !skip_match)
                return 0;

            return minmax(1 + shift_match, skip_match);
        }
        else if (next_char == ONE_OR_MANY)
        {
            shift_match = match_and_count_mk2(string + 1, pattern, minmax);

            if (*(pattern + 2) == '\0')
                return 1 + shift_match;

            skip_match = match_and_count_mk2(string + 1, pattern + 2, minmax);

            if (!shift_match && !skip_match)
                return 0;

            return 1 + minmax(shift_match, skip_match);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            shift_match = match_and_count_mk2(string + 1, pattern + 2, minmax);

            if (*(pattern + 2) == '\0')
                return 1 + shift_match;

            skip_match = match_and_count_mk2(string, pattern + 2, minmax);

            if (!shift_match && !skip_match)
                return 0;

            return minmax(1 + shift_match, skip_match);
        }

        while (next_char == OR)
        {
            pattern = pattern + 2;
            next_char = *(pattern + 1);
        }

        return 1 + match_and_count_mk2(string + 1, pattern + 1, minmax);
    }

    if (next_char == ZERO_OR_MANY || next_char == ZERO_OR_ONE || next_char == OR)
        return match_and_count_mk2(string, pattern + 2, minmax);

    return 0;
}

int why_matcher_next(why_matcher *matcher, char *pattern, int greedy)
{
    int match_length;
    int (*minmax)();

    // minmax = greedy ? max : min;
    minmax = greedy ? max : min_but_nonzero;

    while (*(matcher->current_position) != '\0')
    {
        // match_length = match_and_count(matcher->current_position, pattern);
        match_length = match_and_count_mk2(matcher->current_position, pattern, minmax);
        if (match_length)
        {
            matcher->token_length = match_length;

            return match_length;
        }

        matcher->current_position ++;
    }

    return 0;
}

char *why_matcher_get_next_match(why_matcher *matcher, char *pattern, int greedy)
{
    char *string;
    char *substring;

    if (pattern != matcher->pattern)
    {
        matcher->pattern = pattern;
        matcher->min_pattern_length = get_min_pattern_length(pattern);
    }

    why_matcher_next(matcher, pattern, greedy);
    string = matcher->current_position;
    if (matcher->token_length >= matcher->min_pattern_length)
    {
        substring = why_string_substring(string, 0, matcher->token_length);
        matcher->current_position += matcher->token_length;
        matcher->token_length = 0;

        return substring;
    }

    return NULL;
}

void why_matcher_destroy(why_matcher **matcher)
{
    // free((*matcher)->string);
    why_memory_destroy((void **)matcher);
}