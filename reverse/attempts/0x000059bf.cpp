// ?GetLengthSqrd@Coord2D@@QBEMXZ
// partial score=0.9 date=2026-08-31
// Coord2D::GetLengthSqrd at 0x000059BF (20 bytes) and Coord2D::GetLength at
// 0x0000599F (32 bytes), which is the same expression under a sqrt.
//
// Everything matches except the order of the first two x87 loads. Retail loads
// x then y; MSVC 7.1 loads y then x for this shape no matter which way the sum
// is written - `x * x + y * y` and `y * y + x * x` compile to identical bytes,
// so the operand order in the source is not what decides it. Something else
// about how the two components reach the expression does.

float Coord2D::GetLengthSqrd() const
{
    return y * y + x * x;
}

float Coord2D::GetLength() const
{
    return (float)sqrt((double)(y * y + x * x));
}
