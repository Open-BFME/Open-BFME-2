// ?Normalize@Coord2D@@QAEMXZ
// partial score=0.96 date=2026-08-31
// Coord2D::Normalize, retail 0x000059D3, 83 bytes. 80/83 bytes right: the only
// difference is one extra `fst dword ptr [ebp-4]` (d9 55 fc) emitted before the
// 1.0f constant load. Retail stores the length exactly once, after the constant
// load, then divides. Every other choice below is confirmed byte-for-byte: the
// squares must be computed in x87 (so the operands are doubles, unlike the
// sibling length() which is pure SSE), the reciprocal is a float divss against
// the stored length, and the return value is whatever the sqrt left in ST0.
// Both `float len` and `double len` variants produce the same extra store.
float Coord2D::Normalize()
{
    double dx = x;
    double dy = y;
    double len = sqrt(dx * dx + dy * dy);
    float scale = 1.0f / (float)len;

    x = x * scale;
    y = y * scale;
    return (float)len;
}
