// ?Rotate@Coord2D@@QAEAAV1@ABV1@M@Z
// partial score=0.5 date=2026-08-31
// Coord2D::Rotate(const Coord2D &, float), retail 0x000039BB, 80 bytes.
// The SSE tail is right by construction and the algebra is certain
//   x = coord.x * cosine - coord.y * sine
//   y = coord.y * cosine + coord.x * sine
// but retail gets both trig values from a single x87 `fsincos` (d9 fb) and
// spills them to float locals, while a plain sin()/cos() pair compiles to two
// calls into the CRT and then stays in x87 for the whole body. /Oi does turn
// the calls into intrinsics but emits separate fcos/fsin (d9 ff / d9 fe), still
// not fsincos, and it also drags the rest of the TU off its matched shape. The
// missing piece is whatever gave BFME 2 a fused sincos - most likely a small
// inline helper - not the expression below.
Coord2D &Coord2D::Rotate(const Coord2D &coord, float angle)
{
    float cosine = (float)cos(angle);
    float sine = (float)sin(angle);

    x = coord.x * cosine - coord.y * sine;
    y = coord.y * cosine + coord.x * sine;
    return *this;
}
