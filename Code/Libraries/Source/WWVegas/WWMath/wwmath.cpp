// cl: /O1 /arch:SSE2

// The tolerance is compared against the raw difference twice rather than
// against its absolute value: retail negates the tolerance with the usual
// xorps/subss pair instead of masking a sign bit.
bool areApproxEqual(float a, float b, float tolerance)
{
    float delta = a - b;

    return delta < tolerance && delta > -tolerance;
}
