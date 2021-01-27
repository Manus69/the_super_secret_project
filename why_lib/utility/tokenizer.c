#include "why_lib.h"
#include "why_tokenizer.h"


//c*k
//*x.

//*k
//ck
//cok
//cock

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

static int match_character(char string_char, char pattern_char)
{
    if (string_char == pattern_char)
        return true;
    else if (pattern_char == WILDCARD)
        return true;
    else if (pattern_char == SINGULAR_WILDCARD)
        return true;
    else if (why_string_is_digit(string_char) && (pattern_char == ANY_DIGIT))
        return true;
    else if (why_string_is_letter(string_char) && (pattern_char == ANY_LETTER))
        return true;

    return false;
}

char *why_tokenizer_next(why_tokenizer *tokenizer, const char *pattern)
{
    char *current_pattern_position;

    if (!pattern)
        return NULL;

    current_pattern_position = (char *)pattern;

    while (*tokenizer->current_position != '\0')
    {
        if (*current_pattern_position == '\0')
        {
            return tokenizer->current_position - tokenizer->token_length;
        }

        if (match_character(*tokenizer->current_position, *current_pattern_position))
        {
            tokenizer->token_length ++;
            if (*current_pattern_position != WILDCARD)
                current_pattern_position ++;
        }
        else
        {
            tokenizer->token_length = 0;
            current_pattern_position = (char *)pattern;
        }
        tokenizer->current_position ++;
    }

    return tokenizer->token_length ? tokenizer->current_position - tokenizer->token_length : NULL;
}

char *why_tokenizer_get_matching_substring(why_tokenizer *tokenizer, const char *pattern)
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