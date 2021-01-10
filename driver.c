#include "why_lib.h"

#include <stdio.h>
#include <time.h>

void test_run()
{
    why_buffer *buffer;
    why_vector *vector;

    buffer = why_buffer_create("text_file.txt", 0, 0);
    vector = why_vector_create(0, NULL, NULL);
    why_buffer_read_all_lines_into_structure(buffer, '\n', vector, why_vector_push);
    why_buffer_destroy(&buffer);
    // why_display_vector(vector, why_display_string);

    why_vector_destroy(&vector);
}

int main()
{
    clock_t start;
    clock_t end;

    start = clock();

    test_run();

    end = clock();

    printf("\ntime elapsed: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);

    return 0;
}