#ifndef WHY_TOKENIZER_H
#define WHY_TOKENIZER_H

#define ZERO_OR_MANY '*'
#define ONE_OR_MANY '+'
#define ZERO_OR_ONE '?'
#define ESCAPE '\\'
#define OR '|'
#define WILDCARD '.'
#define ANY_LETTER '@'
#define ANY_DIGIT '#'

struct why_tokenizer
{
    char *string;
    char *pattern;
    char *current_position;
    int token_length;
};

#endif