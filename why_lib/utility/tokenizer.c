#include "why_lib.h"
#include "why_tokenizer.h"

#include "why_math.h"

int int_max_test(int a, int b)
{
    return a > b ? a : b;
}

why_tokenizer *why_tokenizer_create(const char *string)
{
    why_tokenizer *tokenizer;

    tokenizer = malloc(sizeof(why_tokenizer));
    if (!tokenizer)
        return NULL;
    
    // tokenizer->string = why_string_create(string); //check return?
    tokenizer->string = (char *)string;
    tokenizer->current_position = tokenizer->string;
    tokenizer->token_length = 0;
    tokenizer->pattern = NULL;

    return tokenizer;
}

void why_tokenizer_reset(why_tokenizer *tokenizer)
{
    tokenizer->current_position = tokenizer->string;
    tokenizer->token_length = 0;
}

int why_tokenizer_get_token_length(const why_tokenizer *tokenizer)
{
    return tokenizer->token_length;
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

int match_from_current_position(char *string, char *pattern) //this works somewhat
{
    char string_char;
    char pattern_char;
    char next_char;

    string_char = *string;
    pattern_char = *pattern;

    if (pattern_char == '\0')
        return true;

    if (string_char == '\0')
        return false;

    next_char = *(pattern + 1);
    if (match_character(string_char, pattern_char))
    {
        if (next_char == ZERO_OR_MANY)
        {
            return match_from_current_position(string + 1, pattern) || match_from_current_position(string, pattern + 2);
        }
        return match_from_current_position(string + 1, pattern + 1);
        // else
        // {
        //     return match_from_current_position(string + 1, pattern + 1);
        // }
    }
    else // no match
    {
        if (next_char == ZERO_OR_MANY)
        {
            return match_from_current_position(string, pattern + 2);
        }
        return false;
        // else
        // {
        //     // return match_from_current_position(string - 1, pattern + 1);
        //     return false;
        // }
    }
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
            skip_match = match_and_count(string, pattern + 2);

            return skip_match > shift_match ? skip_match : shift_match + 1; //if the character in the pattern is skipped, dont count it
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

            return skip_match > shift_match ? skip_match : shift_match + 1;
        }

        return 1 + match_and_count(string + 1, pattern + 1);
    }

    if (next_char == ZERO_OR_MANY)
    {
        return match_and_count(string, pattern + 2);
    }
    else if (next_char == ZERO_OR_ONE)
    {
        return match_and_count(string, pattern + 2);
    }

    return 0;
}

int match_from_current_position_mk2(why_tokenizer *tokenizer, char *pattern)
{
    char string_char;
    char pattern_char;
    char next_char;

    string_char = *tokenizer->current_position;
    pattern_char = *pattern;

    if (pattern_char == '\0')
        return true;

    if (string_char == '\0')
        return false;

    next_char = *(pattern + 1);
    if (match_character(string_char, pattern_char))
    {
        tokenizer->token_length ++;
        tokenizer->current_position ++;
        if (next_char == ZERO_OR_MANY)
        {
            return match_from_current_position_mk2(tokenizer, pattern) || match_from_current_position_mk2(tokenizer, pattern + 2);
        }
        else
        {
            return match_from_current_position_mk2(tokenizer, pattern + 1);
        }
    }
    else // no match
    {
        if (next_char == ZERO_OR_MANY)
        {
            tokenizer->current_position ++;
            return match_from_current_position_mk2(tokenizer, pattern + 2);
        }
        else
        {
            // tokenizer->current_position --;
            return match_from_current_position_mk2(tokenizer, pattern);
        }
    }
}

char *why_tokenizer_next(why_tokenizer *tokenizer, char *pattern)
{
    ;
}

char *why_tokenizer_get_matching_substring(why_tokenizer *tokenizer, char *pattern)
{
    char *string;
    char *substring;

    string = why_tokenizer_next(tokenizer, pattern);
    substring = why_string_substring(string, 0, tokenizer->token_length);
    tokenizer->token_length = 0;

    return substring;
}

void why_tokenizer_destroy(why_tokenizer **tokenizer)
{
    // free((*tokenizer)->string);
    why_memory_destroy((void **)tokenizer);
}