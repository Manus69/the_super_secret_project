#include "why_lib.h"
#include "why_matcher.h"

#include "why_math.h"

int int_max_test(int a, int b)
{
    return a > b ? a : b;
}

why_matcher *why_matcher_create(const char *string)
{
    why_matcher *matcher;

    matcher = malloc(sizeof(why_matcher));
    if (!matcher)
        return NULL;
    
    // matcher->string = why_string_create(string); //check return?
    matcher->string = (char *)string;
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

    return length;
}

int match_and_count(char *string, char *pattern)
{
    char string_char;
    char pattern_char;
    char next_char;

    int shift_match;
    int skip_match;

    // int chars_matched; 

    string_char = *string;
    pattern_char = *pattern;

    if (string_char == '\0')
        return 0;

    if (pattern_char == '\\')
        pattern_char = *(pattern + 1);

    if (pattern_char == '\0')
        return 0;

    // chars_matched = 0;
    next_char = *(pattern + 1);
    if (match_character(string_char, pattern_char))
    {
        // chars_matched ++;
        if (next_char == ZERO_OR_MANY)
        {
            shift_match = match_and_count(string + 1, pattern);
            skip_match = match_and_count(string, pattern + 2);

            // return skip_match >= shift_match ? skip_match : shift_match + 1; //if the character in the pattern is skipped, dont count it
            return MAX(1 + shift_match, skip_match);
        }
        else if (next_char == ONE_OR_MANY)
        {
            shift_match = match_and_count(string + 1, pattern);
            skip_match = match_and_count(string + 1, pattern + 2);

            return 1 + MAX(shift_match, skip_match);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            shift_match = match_and_count(string + 1, pattern + 2);
            skip_match = match_and_count(string, pattern + 2);

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

int match_and_count_mk2(why_matcher *matcher, char *pattern)
{
    char string_char;
    char pattern_char;
    char next_char;

    int shift_match;
    int skip_match;

    // int chars_matched; 

    string_char = *matcher->current_position;
    pattern_char = *pattern;

    if (string_char == '\0')
        return 0;

    if (pattern_char == '\\')
        pattern_char = *(pattern + 1);

    if (pattern_char == '\0')
        return 0;

    // chars_matched = 0;
    next_char = *(pattern + 1);
    if (match_character(string_char, pattern_char))
    {
        // chars_matched ++;
        if (next_char == ZERO_OR_MANY)
        {
            shift_match = match_and_count(matcher->current_position + 1, pattern);
            skip_match = match_and_count(matcher->current_position, pattern + 2);

            // return skip_match >= shift_match ? skip_match : shift_match + 1; //if the character in the pattern is skipped, dont count it
            return MAX(1 + shift_match, skip_match);
        }
        else if (next_char == ONE_OR_MANY)
        {
            shift_match = match_and_count(matcher->current_position + 1, pattern);
            skip_match = match_and_count(matcher->current_position + 1, pattern + 2);

            return 1 + MAX(shift_match, skip_match);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            shift_match = match_and_count(matcher->current_position + 1, pattern + 2);
            skip_match = match_and_count(matcher->current_position, pattern + 2);

            return MAX(1 + shift_match, skip_match);
        }

        while (next_char == OR)
        {
            pattern = pattern + 2;
            next_char = *(pattern + 1);
        }

        return 1 + match_and_count(matcher->current_position + 1, pattern + 1);
    }

    if (next_char == ZERO_OR_MANY || next_char == ZERO_OR_ONE || next_char == OR)
    {
        return match_and_count(matcher->current_position, pattern + 2);
    }

    return 0;
}

int why_matcher_next(why_matcher *matcher, char *pattern)
{
    int match_length;

    while (*(matcher->current_position) != '\0')
    {
        match_length = match_and_count(matcher->current_position, pattern);
        if (match_length)
        {
            matcher->token_length = match_length;

            return match_length;
        }

        matcher->current_position ++;
    }

    return 0;
}

char *why_matcher_get_matching_substring(why_matcher *matcher, char *pattern)
{
    char *string;
    char *substring;

    why_matcher_next(matcher, pattern);
    string = matcher->current_position;
    if (matcher->token_length)
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