#ifndef WHY_TOKENIZER_H
#define WHY_TOKENIZER_H

#define WILDCARD '*'
#define SINGULAR_WILDCARD '.'
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