#include "why_lib.h"

#include <stdio.h>
#include <time.h>

void string_sort_test()
{
    why_buffer *buffer;
    why_vector *vector;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    why_buffer_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);
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
    vector = why_buffer_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);
    why_buffer_destroy(&buffer);

    string = why_vector_accumualte(vector, 0, why_vector_get_length(vector), why_string_concat_destroy_left);
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

    why_buffer_read_all_lines_into_structure(buffer, '\n', table, why_hash_table_add);
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

    why_buffer_read_all_lines_into_structure(buffer, '\n', list, why_list_push);
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
    why_buffer_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);

    string = why_vector_pop(vector);

    why_string_get_formatted_string(string);

    why_vector_destroy(&vector);
    why_buffer_destroy(&buffer);
    free(string);
}

//create apply functions for all containers?
//make it so that hash table is "derived" from vector?
//pritntf; make formatters first?

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    // string_sort_test();
    // split_test();
    // list_test();
    // hash_test();
    print_test();

    end = clock();

    printf("\ntime elapsed: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}