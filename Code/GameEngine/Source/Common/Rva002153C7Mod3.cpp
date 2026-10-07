// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
// BFME1 donor: Open-BFME-1 824b1048d7 at 0x0040BC50; same random modulo-three selector, three input pairs and 1000.0 fallback.
// Adapted to target fields +0x94..+0xA8 and the spherical helper at 0x002152BD.
#include "Coord3D.h"

class WWMath
{
public:
    static float Random_Float(void);
};
void Rva002152BDCompute(float *out, float a, float b);

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
