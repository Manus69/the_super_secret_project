#include "why_lib.h"

#include <stdio.h>
#include <time.h>
#include <float.h>

void string_sort_test()
{
    why_buffer *buffer;
    why_vector *vector;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    why_file_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);
    why_buffer_destroy(&buffer);

    why_sort_vector_heapsort(vector, why_string_compare_mk2);
    // why_sort_vector_merge_mk2(vector, why_string_compare_mk2);
    why_display_vector(vector, why_display_string);

    // why_display_string(why_vector_pop(vector));


    why_vector_destroy(&vector);
}

void split_test()
{
    // why_buffer *buffer;
    why_vector *vector;

    // buffer = why_buffer_create("text_file.txt", DEFAULT, DEFAULT);
    vector = why_file_read_all_lines("text_file.txt");
    why_display_vector(vector, why_display_string);

    why_vector_destroy(&vector);
}

void hash_test()
{
    why_hash_table *table;
    why_buffer *buffer;

    table = why_hash_table_create(10, why_hash_string, NULL, NULL);
    buffer = why_buffer_create("text_file.txt", 0, 0);

    why_file_read_all_lines_into_structure(buffer, '\n', table, why_hash_table_add);
    why_display_hash_table(table, why_display_list);

    why_buffer_destroy(&buffer);
    why_hash_table_destroy(&table);
}

void list_test()
{
    why_buffer *buffer;
    why_list *list;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    list = why_list_create(NULL, NULL);

    why_file_read_all_lines_into_structure(buffer, '\n', list, why_list_push);
    why_display_list(list, why_display_string);

    why_buffer_destroy(&buffer);
    why_list_destroy(&list);
}

void matcher_test()
{
    why_buffer *buffer;
    why_vector *vector;
    why_matcher *matcher;
    char *string;
    char *pattern;

    buffer = why_buffer_create("match_test.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    why_file_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);

    
    while (why_vector_get_length(vector))
    {
        pattern = why_vector_pop(vector);
        string = why_vector_pop(vector);
        matcher = why_matcher_create(string);

        if (!string)
            break ;

        char *substring;
        printf("string: %s\npattern: %s\n\n", string, pattern);

        while ((substring = why_matcher_get_next_match(matcher, pattern, false, false)))
        {
            printf("%s\n", substring);
            free(substring);
        }

        printf("---------------\n");

        free(string);
        free(pattern);
        why_matcher_destroy(&matcher);
    }

    why_vector_destroy(&vector);
    why_buffer_destroy(&buffer);
}

void matcher_test2()
{
    why_buffer *buffer;
    why_vector *vector;
    why_matcher *matcher;
    char *string;
    char *pattern;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    why_file_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);

    pattern = "c.*k";
    matcher = why_matcher_create(NULL);
    while (why_vector_get_length(vector))
    {
        string = why_vector_pop(vector);
        why_matcher_reset(matcher, string);

        char *substring;

        // printf("string: %s\npattern: %s\n\n", string, pattern);

        while ((substring = why_matcher_get_next_match(matcher, pattern, false, true)))
        {
            printf("%s\n", substring);
            free(substring);
        }

        // printf("---------------\n");

        free(string);
    }

    why_matcher_destroy(&matcher);
    why_vector_destroy(&vector);
    why_buffer_destroy(&buffer);
}

void string_buffer_test()
{
    why_string_buffer *buffer;
    char *string;
    int n;

    n = 11;
    buffer = NULL;
    while (n)
    {
        buffer = why_string_buffer_append_string_rvp(buffer, "012");
        n --;
    }


    string = why_string_buffer_get_content(buffer);
    free(buffer);
    printf("%s\n", string);


    free(string);
}

void print_format_test()
{
    char *string;

    // string = "%d";
    // why_printf(string, -10);

    //
    // string = why_sprintf("this is a test %10d\n ??? %3f\n", -1, 3.14159);
    // why_printf(string);
    // free(string);

    string = why_file_read_file_into_string("text_file.txt");
    
    why_printf("%s\n", string);
    free(string);

    // why_fprintf("this is a test %666d!\n", "text_file.txt", FILE_MODE_TRUNCATE | FILE_MODE_WRITE, -1);

}

char *file_read_test()
{
    char *file_name;
    char *string;

    file_name = "text_file.txt";
    string = why_file_read_file_into_string(file_name);

    return string;
}

void sqrt_test()
{
    why_vector *vector;
    why_vector *number_strings;
    why_vector *square_roots;


    vector = why_file_read_all_lines("text_file.txt");
    number_strings = why_string_split(why_vector_at(vector, 0), ' ');
    square_roots = why_vector_create(DEFAULT, why_memory_copy_double, why_memory_destroy);

    int n = 0;
    char *current;
    double x;
    
    while (n < why_vector_get_length(number_strings))
    {
        current = why_vector_at(number_strings, n);
        x = why_string_atof(current);
        x = why_math_sqrt(x);
        why_vector_push(square_roots, &x);
        n ++;
    }

    why_display_vector(square_roots, why_display_double);

    why_vector_destroy(&vector);
    why_vector_destroy(&number_strings);
    why_vector_destroy(&square_roots);
}

void sqrt_test2()
{
    double root;
    double x;

    x = (double)INT_MAX;
    root = why_math_sqrt(x);
    why_printf("%.20f", root);
}

void p_test()
{
    why_real_polynomial *p;

    p = why_polynomial_from_string("x^3");
    why_display_polynomial(p);

    why_polynomial_destroy(&p);
}

void math_test()
{
    double x;
    double pi;

    pi = PI;
    x = pi / 2;
    // x = why_math_modulus(-x, 2 * pi);
    // why_printf("%f\n", x);
    
    double y;
    y = why_math_sin(PI/4);
    why_printf("%f\n", y);
}

//create apply functions for all containers?
//make it so that hash table is "derived" from vector?
//make functions either all safe or all unsafe?
//complex
//matrix
//polynomial
//sqrt

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // string_sort_test();
    // split_test();
    // list_test();
    // hash_test();
    // matcher_test();
    // matcher_test2();
    // print_format_test();
    // string_buffer_test();
    // sqrt_test();
    // sqrt_test2();
    // p_test();
    math_test();

    // char *test = file_read_test();

    end = clock();

    printf("\ntime elapsed: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}