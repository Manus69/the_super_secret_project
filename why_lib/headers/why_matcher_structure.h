#ifndef WHY_MATCHER_STRUCTURE_H
#define WHY_MATCHER_STRUCTURE_H

struct why_matcher
{
    char *string;
    char *current_position;

    int match_length;
};

#endif