#ifndef WHY_MATCHER_FUNCTIONS_H
#define WHY_MATCHER_FUNCTIONS_H

#include "why_typedefs.h"

why_matcher *why_matcher_create(const char *string);

char *why_matcher_get_next_match(why_matcher *matcher, char *pattern, int greedy, int inclusive);

int why_matcher_shift_position(why_matcher *matcher, int shift);

void why_matcher_reset(why_matcher *matcher, const char *string);
void why_matcher_destroy(why_matcher **matcher);

#endif