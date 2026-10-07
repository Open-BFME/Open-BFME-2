// ?rva002153C7@Rva002153C7@@QAEPAUCoord3D@@PAU2@@Z
// partial score=0.82 date=2026-10-07
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /ICode/Libraries/Include/Lib
// Native 002153C7..0021545C, 149B. ECX receiver and one output-home word
// at EBP+8; RET4/EAX returns that home. A three-float result view is measured.
// The random helper is rowed WWMath::Random_Float. Helper002152BD is 266B,
// cdecl hidden-result-compatible: three words (result, float, float), RET0.
// Original receiver/method/result type identities remain unproven.
#include "Coord3D.h"
class WWMath
{
public:
    static float Random_Float();
};
Coord3D *Rva002152BD(Coord3D *out, float a, float b);
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
    int choice = static_cast<int>(WWMath::Random_Float() * 100.0f) % 3;
    if (choice == 0)
        Rva002152BD(out, a0, b0);
    else if (choice == 1)
        Rva002152BD(out, a1, b1);
    else if (choice == 2)
        Rva002152BD(out, a2, b2);
    else
        out->x = out->y = out->z = 1000.0f;
    return out;
}
