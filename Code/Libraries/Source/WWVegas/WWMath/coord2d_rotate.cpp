// cl: /O1 /arch:SSE2
// Coord2D::Rotate(const Coord2D &, float) at 0x000039BB.
//
// Split out of coord2d.cpp because this is the one body in the class whose
// trigonometry is not a library call: retail opens with `fld angle; fsincos`
// and spills both results to float locals, then does the four products in SSE.
// MSVC 7.1 never fuses sin() and cos() into fsincos - with /Oi it emits fcos
// and fsin and keeps the results in x87 registers, so the whole tail changes
// shape - and /Oi is not available to coord2d.cpp anyway because it turns the
// four fabs calls in GetLengthEstimate into the fabs instruction. The four
// x87 instructions are written out; the arithmetic below is ordinary C++ and
// the ebp frame retail carries is the one MSVC forces on any function that
// contains an __asm block.

struct Coord2DBase
{
    float x;
    float y;
};

class Coord2D : public Coord2DBase
{
public:
    Coord2D &Rotate(const Coord2D &that, float angle);
};

Coord2D &Coord2D::Rotate(const Coord2D &that, float angle)
{
    float cosine;
    float sine;

    __asm
    {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }

    x = that.x * cosine - that.y * sine;
    y = that.y * cosine + that.x * sine;

    return *this;
}
