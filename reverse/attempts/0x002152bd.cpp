// ?Rva002152BDCompute@@YAXPAMMM@Z
// partial score=0.74 date=2026-10-07
#include <math.h>

struct Rva002152BDVector
{
    float X, Y, Z;
    float Length2() const
    {
        return X * X + Y * Y + Z * Z;
    }
};

class WWMath
{
public:
    static float __fastcall Inv_Sqrt(float value);
};

void Rva002152BDCompute(float *out, float a, float b)
{
    Rva002152BDVector direction;
    float first = *(volatile const float *)&b * 0.017453292f;
    float firstSine = (float)sin(first);
    float second = *(volatile const float *)&a * 0.017453292f + 1.57079637f;
    direction.X = -(float)cos(second) * firstSine;
    direction.Y = -(float)sin(second) * firstSine;
    direction.Z = -(float)cos(first);
    float lengthSquared = direction.Length2();
    if (lengthSquared != 0.0f)
    {
        float inverseLength = WWMath::Inv_Sqrt(lengthSquared);
        direction.X *= inverseLength;
        direction.Y *= inverseLength;
        direction.Z *= inverseLength;
    }
    direction.X *= 10000.0f;
    direction.Y *= 10000.0f;
    direction.Z *= 10000.0f;
    out[0] = direction.X;
    out[1] = direction.Y;
    out[2] = direction.Z;
}