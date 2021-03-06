#ifndef WHY_UTILITY_FUNCTIONS_H
#define WHY_UTILITY_FUNCTIONS_H

//check which one is better
int why_utility_compare_ints(int *a, int *b);
int why_utility_compare_ints2(int *a, int *b);
int why_utility_compare_doubles(double *x, double *y);

int why_utility_get_type_size(const char *type_string); //make regex for things like this
int why_utility_is_sorted(const void *structure, int size, void *(*at)(), int (*compare)());

#endif