// ?Rotate@Coord2D@@QAEAAV1@M@Z
// partial score=0.95 date=2026-09-02
// cl: /O1 /arch:SSE2
//
// 2026-09-03: three more shapes refuted for the slot swap - declaring a third
// unused float, initialising the two locals in their declarations instead of
// assigning after, and declaring cosine first while keeping the assignment
// order. All four spellings give the identical 23 bytes with the first
// difference at 0x17, so the allocation is not driven by declaration order,
// initialisation order, or the number of locals. It is the __asm block.
// Coord2D::Rotate(float) at 0x00003916 - the in-place twin of the two-argument
// Rotate at 0x000039BB.
//
// Retail computes the sine and cosine THREE times over: a call to sin, a call
// to cos, and then the same fsincos block the other overload carries, which
// overwrites both. The library calls are dead by the time the asm runs and the
// compiler keeps them anyway, so the source has to spell all three out - that
// is 0x17 bytes of the body and it matches exactly.
//
// STILL OPEN: the two float slots are swapped. Retail puts sin's result at
// [ebp-4] and cos's at [ebp-8]; MSVC 7.1 does the reverse, and every later
// reference follows, so 23 of the 101 bytes differ even though the length and
// the instruction sequence are right. The slot choice is driven by the __asm
// block, not by the declarations: swapping the declaration order, splitting
// the declarations from the assignments, and swapping both the fstp order and
// the names in the arithmetic all leave it where it is.

extern "C" double __cdecl sin(double x);
extern "C" double __cdecl cos(double x);

struct Coord2DBase
{
    float x;
    float y;
};

class Coord2D : public Coord2DBase
{
public:
    Coord2D &Rotate(float angle);
};

Coord2D &Coord2D::Rotate(float angle)
{
    float sine;
    float cosine;

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
