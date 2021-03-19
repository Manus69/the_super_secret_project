#include "why_constants.h"
#include "why_math_functions.h"
#include "why_memory_functions.h"

enum function
{
    SIN, COS,
};

#define N_TAYLOR_TERMS 10

static const double cos_values[] = {1, 0, -1, 0};
static const double sin_values[] = {0, 1, 0, -1};
static const double signs[] = {1, 1, -1, -1};

int get_quadrant(double phi)
{    
    return (int)(phi / (PI / 2)) % 4;
}

//f(x) = f'(n)/n! (x - a)^n + ... + f(a)
// double why_math_sin(double phi)
// {
//     double f;
//     double delta;
//     double coefficient;
//     int quadrant;
//     int n;

//     phi = why_math_modulus(phi, 2 * PI);
//     quadrant = get_quadrant(phi);
//     delta = phi - (PI  * quadrant) / 2;
//     n = N_TAYLOR_TERMS - 1;
//     f = 0;

//     while (n)
//     {
//         if (n % 2)
//         {
//             coefficient = cos_values[quadrant];
//         }
//         else
//             coefficient = sin_values[quadrant];
        
//         f = f + coefficient * signs[n % 4];
//         f = (f * delta) / n;

//         n --;
//     }
//     f = f + sin_values[quadrant] * signs[0];

//     return f;
// }

double why_math_sin_test(double phi)
{
    int quadrant;
    int n;
    double coefficient;
    double f;
    double delta;
    double term;


    quadrant = get_quadrant(phi);
    phi = why_math_modulus(phi, 2 * PI);
    n = 1;

    f = sin_values[quadrant];
    delta = phi - quadrant * PI / 2;
    term = 1;

    while (n < N_TAYLOR_TERMS)
    {
        if (n % 2)
            coefficient = cos_values[quadrant];
        else
            coefficient = sin_values[quadrant];
        
        term = (term * delta  / n);
        f = f + term * coefficient * signs[n % 4];
        n ++;
    }

    return f;
}

double why_math_sin(double phi)
{
    double f;
    int n;

    f = 0;
    n = N_TAYLOR_TERMS - 1;
    phi = why_math_modulus(phi, 2 * PI);
    while (n)
    {
        if (n % 2)
        {
            f += signs[n % 4];
        }
        f = (f * phi) / n;

        n --;
    }

    return f;
}