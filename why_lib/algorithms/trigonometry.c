#include "why_constants.h"
#include "why_math_functions.h"
#include "why_memory_functions.h"

#define N_TAYLOR_TERMS 11
static const double signs[] = {1, 1, -1, -1};

//unused
// static const double cos_values[] = {1, 0, -1, 0};
// static const double sin_values[] = {0, 1, 0, -1};

double sin_first_quadrant(double phi);
double cos_first_quadrant(double phi);

int get_quadrant(double phi)
{    
    return (int)(phi / (PI / 2)) % 4;
}

double sin_first_quadrant(double phi)
{
    double f;
    int n;
    
    if (phi > (PI / 4))
        return cos_first_quadrant(phi);

    f = 0;
    n = N_TAYLOR_TERMS - 1;

    while (n)
    {
        if (n % 2)
            f += signs[n % 4];
        f = (f * phi) / n;
        n --;
    }

    return f;
}

double cos_first_quadrant(double phi)
{
    double f;
    int n;

    if (phi >= (PI / 4))
        return sin_first_quadrant(phi);

    f = 0;
    n = N_TAYLOR_TERMS - 1;

    while (n)
    {
        if (n % 2 == 0)
            f += signs[n % 4];
        f = (f * phi) / n;
        n --;
    }
    f += 1;

    return f;
}

double why_math_sin(double phi)
{
    int quadrant;

    if (phi < 0)
        return -1 * why_math_sin(-phi);
    
    phi = why_math_modulus(phi, 2 * PI);
    quadrant = get_quadrant(phi);

    if (quadrant == 1)
        return sin_first_quadrant(PI - phi);
    else if (quadrant == 2)
        return -1 * sin_first_quadrant(phi - PI);
    else if (quadrant == 3)
        return -1 * sin_first_quadrant(2 * PI - phi);
    
    return sin_first_quadrant(phi);
}

double why_math_cos(double phi)
{
    int quadrant;

    if (phi < 0)
        return why_math_cos(-phi);
    
    phi = why_math_modulus(phi, 2 * PI);
    quadrant = get_quadrant(phi);

    if (quadrant == 1)
        return -1 * cos_first_quadrant(PI - phi);
    else if (quadrant == 2)
        return -1 * cos_first_quadrant(phi - PI);
    else if (quadrant == 3)
        return cos_first_quadrant(2 * PI - phi);
    
    return cos_first_quadrant(phi);
}