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
static const double signs[] = {1, 1, -1, -1};

int get_quadrant(double phi)
{
    // double value = phi / (PI / 2);
    
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
    // int sign;

    phi = why_math_modulus(phi, 2 * PI);
    quadrant = get_quadrant(phi);
    delta = phi - (PI / 2) * quadrant;
    n = N_TAYLOR_TERMS - 1;
    f = 0;
    // sign = 1;

    while (n)
    {
        if (n % 2)
        {
            coefficient = cos_values[quadrant];
        }
        else
            coefficient = sin_values[quadrant];
        
        f = f + coefficient * signs[n % 4];
        f = (f * delta) / n;

        n --;
    }
    f = f + sin_values[quadrant] * signs[0];
    // f = (f * delta);

    return f;
}

// double why_math_sin(double phi)
// {
//     double f;
//     int n;

//     f = 0;
//     n = N_TAYLOR_TERMS - 1;
//     phi = why_math_modulus(phi, 2 * PI);
//     while (n)
//     {
//         if (n % 2)
//         {
//             f += signs[n % 4];
//         }
//         f = (f * phi) / n;

//         n --;
//     }

//     return f;
// }