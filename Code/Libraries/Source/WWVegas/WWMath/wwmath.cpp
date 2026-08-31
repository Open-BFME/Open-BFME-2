// cl: /O1 /arch:SSE2 /Oi

#include <math.h>

#pragma intrinsic(sin, cos, tan, asin, acos)

// The tolerance is compared against the raw difference twice rather than
// against its absolute value: retail negates the tolerance with the usual
// xorps/subss pair instead of masking a sign bit.
bool areApproxEqual(float a, float b, float tolerance)
{
    float delta = a - b;

    return delta < tolerance && delta > -tolerance;
}

// The x87 transcendentals survive /arch:SSE2 untouched: the float argument is
// loaded straight off the stack with fld and the result is left in ST0, with no
// rounding store on the way out.
float Sin(float value)
{
    return (float)sin(value);
}

float Cos(float value)
{
    return (float)cos(value);
}

float Tan(float value)
{
    return (float)tan(value);
}

float ASin(float value)
{
    return (float)asin(value);
}

float ACos(float value)
{
    return (float)acos(value);
}
