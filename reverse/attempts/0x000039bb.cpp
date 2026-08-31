// ?Rotate@Coord2D@@QAEAAV1@ABV1@M@Z
// partial score=0.9 date=2026-08-31
// Coord2D::Rotate(const Coord2D &, float) at 0x000039BB (80 bytes).
//
// The arithmetic is right; the sine and cosine are not. Retail opens with
// `fld [ebp+0xc]; fsincos`, which MSVC 7.1 emits only under /Oi. This file
// cannot have /Oi: it turns the four fabs calls in GetLengthEstimate into the
// fabs instruction and breaks three landed bodies. The overload at 0x00003916
// carries BOTH the library calls and an fsincos, so whichever unit these two
// live in has /Oi and reaches sin and cos some other way as well.

Coord2D &Coord2D::Rotate(const Coord2D &that, float angle)
{
    const float cosine = (float)cos(angle);
    const float sine = (float)sin(angle);

    x = that.x * cosine - that.y * sine;
    y = that.y * cosine + that.x * sine;

    return *this;
}
