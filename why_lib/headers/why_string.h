#ifndef WHY_STRING_H
#define WHY_STRING_H

#include "why_memory.h"
#include "why_constants.h"

char *why_string_create(const char *literal);
char *why_string_create_shallow(const char *char_string);
char *why_string_create_from_char_array(const char *char_array, int left_index, int length); //why not use substring?
char *why_string_substring(const char *string, int left_index, int length);
char *why_string_copy(const char *old_string);
char *why_string_concat(const char *left, const char *right);
char *why_string_concat_and_destroy(char *lhs, char *rhs);
char *why_string_concat_destroy_left(char *lhs, char *rhs);
char *why_string_join(const char *lhs, const char *joint, const char *rhs);
char *why_string_find_char(const char *string, const char *set);
char *why_string_itoa(int number, int base);
char *why_string_ftoa(double x, int precision);

void why_string_destroy(char **string);

int why_string_get_length(const char *literal);
int why_string_get_index_of(const char *literal, char c);
int why_string_search_char_array(const char *array, char c, int left_index, int number_of_bytes);
int why_string_get_index_of_any(const char *string, const char *char_set, int starting_index);
int why_string_compare(const char *lhs, const char *rhs);
int why_string_compare_mk2(const char *lhs, const char *rhs);
int why_string_atoi_buffer(int number, int base, char *buffer);
int why_string_itoa_buffer(int number, int base, char *buffer);

int why_string_compare_test(const void *lhs, const void *rhs); //

//assumes ascii char set
int why_string_is_digit(char c);
int why_string_is_letter(char c);
int why_string_atoi(const char *string); //this is rather permissive

struct why_vector *why_string_split(const char *literal, char separator);

#endif