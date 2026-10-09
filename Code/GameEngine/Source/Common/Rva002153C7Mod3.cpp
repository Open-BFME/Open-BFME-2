// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
// BFME1 donor: Open-BFME-1 824b1048d7 at 0x0040BC50; same random modulo-three selector, three input pairs and 1000.0 fallback.
// Adapted to target fields +0x94..+0xA8 and the spherical helper at 0x002152BD.
// The helper (BFME1 BfmeFillBC spherical direction) is rebuilt from retail: cos of the
// second angle comes first, the first angle gains PI/2, and its sine is taken twice.
#include <math.h>
#include "Coord3D.h"

class WWMath
{
public:
    static float Random_Float(void);
    static float __fastcall Inv_Sqrt(float value);
};

struct Rva002152BDVector
{
    float X, Y, Z;
    float Length2() const
    {
        return X * X + Y * Y + Z * Z;
    }
};

void Rva002152BDCompute(float *out, float a, float b)
{
    Rva002152BDVector direction;
    float theta = b * 0.017453292f;
    float cosTheta = (float)cos((double)theta);
    float phi = a * 0.017453292f + 1.57079637f;
    direction.X = -((float)sin((double)phi) * cosTheta);
    float sinTheta = (float)sin((double)theta);
    direction.Y = -((float)sin((double)phi) * sinTheta);
    direction.Z = -(float)cos((double)phi);
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

class Rva002153C7
{
public:
    Coord3D *rva002153C7(Coord3D *out);
private:
    char unknown00[0x94];
    float a0, b0, a1, b1, a2, b2;
};

Coord3D *Rva002153C7::rva002153C7(Coord3D *out)
{
    int r = static_cast<int>(WWMath::Random_Float() * 100.0f) % 3;
    if (r == 0)
    {
        Rva002152BDCompute(reinterpret_cast<float *>(out), a0, b0);
        return out;
    }
    if (r == 1)
    {
        Rva002152BDCompute(reinterpret_cast<float *>(out), a1, b1);
        return out;
    }
    if (r == 2)
    {
        Rva002152BDCompute(reinterpret_cast<float *>(out), a2, b2);
        return out;
    }
    out->x = 1000.0f;
    out->y = 1000.0f;
    out->z = 1000.0f;
    return out;
}
