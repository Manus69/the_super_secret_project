#include "why_lib.h"

#include <stdio.h>


int main()
{
    char *test = "01234";

    printf("%s\n", why_string_substring(test, 1, 2));

    return 0;
}