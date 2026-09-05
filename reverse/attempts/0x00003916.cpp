// ?Rotate@Coord2D@@QAEAAV1@M@Z
// partial score=0.95 date=2026-09-04
// cl: /O1 /arch:SSE2
extern "C" double __cdecl sin(double x);
extern "C" double __cdecl cos(double x);
struct Coord2DBase { float x; float y; };
class Coord2D : public Coord2DBase { public: Coord2D &Rotate(float angle); };
Coord2D &Coord2D::Rotate(float angle)
{
    float cosine;
    float sine;
    sine = (float)sin(angle);
    cosine = (float)cos(angle);
    __asm
    {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }
    float rotated = x * cosine - y * sine;
    y = y * cosine + x * sine;
    x = rotated;
    return *this;
}
