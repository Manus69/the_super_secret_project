#include "why_lib.h"

#include <stdio.h>
#include <time.h>

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
    why_buffer *buffer;
    why_vector *vector;
    char *string;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    vector = why_file_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);
    why_buffer_destroy(&buffer);

    string = why_vector_accumualte(vector, 0, why_vector_get_length(vector), why_string_concat_destroy_left_rvp);
    printf("%s\n", string);

    why_vector *lines = why_string_split(string, '1');
    why_display_vector(lines, why_display_string);
    free(string);
    why_vector_destroy(&lines);

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

void print_test()
{
    why_buffer *buffer;
    why_vector *vector;
    char *string;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    why_file_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);

    string = why_vector_pop(vector);

    why_string_get_formatted_string(string);
    // printf("%qqxxx", "ass");

    why_vector_destroy(&vector);
    why_buffer_destroy(&buffer);
    free(string);
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

void print_format_test()
{
    char *string;

    //
    // printf("%.0f\n", 1.49);
    // string = why_string_itoa(-14, 10);
    // printf("%s\n", string);
    //
    // string = why_string_ftoa(3.95, 0);
    // printf("%s\n", string);
    // free(string);


    // string = why_string_get_formatted_string("this is a test");
    string = why_file_read_file_into_string("text_file.txt");
    printf("%s\n", string);
    free(string);

}

//create apply functions for all containers?
//make it so that hash table is "derived" from vector?
//make functions either all safe or all unsafe?
//unfuck the headers
//unfuck the headers

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // string_sort_test();
    // split_test();
    // list_test();
    // hash_test();
    // print_test();
    // matcher_test();
    // matcher_test2();
    print_format_test();

    end = clock();

    printf("\ntime elapsed: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}