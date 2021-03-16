#include "why_constants.h"
#include "why_math_functions.h"
#include "why_memory_functions.h"

enum function
{
    SIN, COS,
};

#define N_TAYLOR_TERMS 3

static const double cos_values[] = {1, 0, -1, 0};
static const double sin_values[] = {0, 1, 0, -1};

int get_quadrant(double phi)
{
    return (int)(phi / (PI / 2)) % 4;
}

//f(x) = f'(n)/n! (x - a)^n + ... + f(a)
double why_math_sin(double phi)
{
    double f;
    double delta;
    double coefficient;
    int quadrant;
    int n;

    phi = why_math_modulus(phi, 2 * PI);
    quadrant = get_quadrant(phi);
    delta = phi - (PI / 2) * quadrant;
    n = N_TAYLOR_TERMS;
    f = 0;

    while (n >= 0)
    {
        if (n % 2)
            coefficient = (-1) * cos_values[quadrant];
        else
            coefficient = sin_values[quadrant];
        
        if (n)
            f = (f * delta) / n + coefficient;
        else
            f = f * delta + coefficient;

        n --;
    }

    return f;
}