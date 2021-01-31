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

void why_matcher_reset(why_matcher *matcher)
{
    matcher->current_position = matcher->string;
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

//get rid of this
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

    if (*pattern == OR)
        pattern ++;

    if (*pattern == '\\')
        pattern ++;

    if (*pattern == '\0')
        return 0;

    next_char = *(pattern + 1);
    if (match_character(*string, *pattern))
    {
        if (next_char == ZERO_OR_MANY)
        {
            shift_match = match_and_count_mk2(string + 1, pattern, minmax);

            if (*(pattern + 2) == '\0' || *(pattern + 2) == OR)
                return 1 + shift_match; //// 

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

int get_quantifier(const char *quantifiers, char c)
{
    int index; 

    index = why_string_get_index_of(quantifiers, c);
    if (index >= 0)
        return quantifiers[index];
    return 0;
}

int match_and_count_mk3(char *string, char *pattern, int (*minmax)(), why_matcher *matcher)
{
    char next_char;
    int shift_match;
    int skip_match;

    if ((*string == '\0' && *pattern == '\0') || *pattern == '\0')
    {
        // matcher->match_length = string - matcher->current_position;
        matcher->match_length = minmax(matcher->match_length, string - matcher->current_position);
        return matcher->quantifier ? 1 : 0;
    }

    next_char = *(pattern + 1);

    if (*string == '\0')
        return 0;

    if (*pattern == OR || *pattern == '\\')
        pattern ++;

    matcher->quantifier = get_quantifier(QUANTIFIERS, next_char);
    if (match_character(*string, *pattern))
    {
        if (next_char == ZERO_OR_MANY)
        {
            shift_match = match_and_count_mk3(string + 1, pattern, minmax, matcher);
            skip_match = match_and_count_mk3(string, pattern + 2, minmax, matcher);

            // if(!matcher->match_length)
            //     return 0;

            return minmax(1 + shift_match, skip_match);
        }
        else if (next_char == ONE_OR_MANY)
        {
            shift_match = match_and_count_mk3(string + 1, pattern, minmax, matcher);
            skip_match = match_and_count_mk3(string + 1, pattern + 2, minmax, matcher);

            if(!matcher->match_length)
                return 0;

            return 1 + minmax(shift_match, skip_match);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            shift_match = match_and_count_mk3(string + 1, pattern + 2, minmax, matcher);
            skip_match = match_and_count_mk3(string, pattern + 2, minmax, matcher);

            if(!matcher->match_length)
                return 0;

            return minmax(1 + shift_match, skip_match);
        }

        while (next_char == OR)
        {
            pattern = pattern + 2;
            next_char = *(pattern + 1);
        }

        return 1 + match_and_count_mk3(string + 1, pattern + 1, minmax, matcher);
    }

    if (next_char == ZERO_OR_MANY || next_char == ZERO_OR_ONE || next_char == OR)
        return match_and_count_mk3(string, pattern + 2, minmax, matcher);

    return 0;
}
//

//the return value is fictitious
int match_and_count_mk4(char *string, char *pattern, int (*minmax)(), why_matcher *matcher)
{
    char next_char;

    if ((*string == '\0' && *pattern == '\0') || *pattern == '\0')
    {
        return (matcher->match_length = minmax(matcher->match_length, string - matcher->current_position));
    }

    next_char = *(pattern + 1);

    if (*string == '\0' && (next_char == ZERO_OR_ONE || next_char == ZERO_OR_MANY))
    {
        return (matcher->match_length = minmax(matcher->match_length, string - matcher->current_position));
    }

    if (*pattern == OR || *pattern == '\\')
        pattern ++;

    if (match_character(*string, *pattern))
    {
        if (next_char == ZERO_OR_MANY)
        {
            match_and_count_mk4(string + 1, pattern, minmax, matcher);
            match_and_count_mk4(string, pattern + 2, minmax, matcher);
        }
        else if (next_char == ONE_OR_MANY)
        {
            match_and_count_mk4(string + 1, pattern, minmax, matcher);
            match_and_count_mk4(string + 1, pattern + 2, minmax, matcher);
        }
        else if (next_char == ZERO_OR_ONE)
        {
            match_and_count_mk4(string + 1, pattern + 2, minmax, matcher);
            match_and_count_mk4(string, pattern + 2, minmax, matcher);
        }

        while (next_char == OR)
        {
            pattern = pattern + 2;
            next_char = *(pattern + 1);
        }

        match_and_count_mk4(string + 1, pattern + 1, minmax, matcher);
    }

    if (next_char == ZERO_OR_MANY || next_char == ZERO_OR_ONE || next_char == OR)
        match_and_count_mk4(string, pattern + 2, minmax, matcher);

    return 0;
}

int why_matcher_next(why_matcher *matcher, char *pattern, int greedy)
{
    int (*minmax)();

    minmax = greedy ? max : min_but_nonzero;

    while (*(matcher->current_position) != '\0')
    {
        // match_and_count_mk3(matcher->current_position, pattern, minmax, matcher);
        match_and_count_mk4(matcher->current_position, pattern, minmax, matcher);

        if (matcher->match_length)
        {
            return matcher->match_length;
        }

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