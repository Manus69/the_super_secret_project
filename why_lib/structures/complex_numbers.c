#include "why_complex_structure.h"
#include "why_typedefs.h"
#include "why_memory_functions.h"
#include "why_math_functions.h"

void why_complex_set(why_complex *z, double x, double y)
{
    z->x = x;
    z->y = y;
}

why_complex *why_complex_create(double x, double y)
{
    why_complex *z;

    if (z = malloc(sizeof(why_complex)))
    {
        why_complex_set(z, x, y);

        return z;
    }

    return NULL;
}

why_complex *why_complex_add(const why_complex *z, const why_complex *w)
{
    return why_complex_create(z->x + w->x, z->y + w->y);
}

why_complex *why_complex_multiply(const why_complex *z, const why_complex *w)
{
    double x;
    double y;

    x = z->x * w->x - z->y * w->y;
    y = z->x * w->y + z->y * w->x;

    return why_complex_create(x, y);
}

double why_complex_modulus(const why_complex *z)
{
    double distance_squared;

    distance_squared = z->x * z->x + z->y * z->y;

    return why_math_sqrt(distance_squared);
}

double why_complex_argument(const why_complex *z)
{
    ;
}