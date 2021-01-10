#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int n;

    if (argc == 1)
        printf ("0\n");
    else
    {
        n = atoi(argv[1]);

        // if (n < 0)
        //     return 0;
        
        while (n > 0) 
        {
            printf("%d\n", n);
            n --;
        }
        printf("0\n");

    }

    return 0;
}