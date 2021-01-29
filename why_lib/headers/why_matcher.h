#ifndef WHY_TOKENIZER_H
#define WHY_TOKENIZER_H

#define ZERO_OR_MANY '*'
#define ONE_OR_MANY '+'
#define ZERO_OR_ONE '?'
#define ESCAPE '\\'
#define OR '|'
#define WILDCARD '.'
#define WITESPACE ' '
#define ANY_LETTER '@'
#define ANY_DIGIT '#'

struct why_matcher
{
    char *string;
    char *current_position;
    int token_length;
    int min_pattern_length;
};

#endif