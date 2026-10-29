// cl: /Oi
// stlport46

// Preserve the CRT inline overloads used by the retail intrinsic wrappers,
// without emitting their incompatible out-of-line float-wrapper copies.
#pragma push_macro("inline")
#define inline __declspec(dllimport) __forceinline
#include <math.h>
#pragma pop_macro("inline")

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

// Native 0x001333F0..0x001333FB: two float stack arguments, FPATAN and RET.
// The BFME1 small-body sweep found identical atan2 float wrappers, including
// WWMath::Atan2, but their folded names do not identify this unreferenced
// retail copy. Keep the original spelling unknown and name its proven effect.
float Rva001333F0Atan2(float y, float x)
{
    return static_cast<float>(atan2(y, x));
}
