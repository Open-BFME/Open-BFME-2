// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
// partial score=0.97 date=2026-09-01
// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
// partial score=0.97 date=2026-09-01
// Matrix4D(const Coord3D &axis, float angle) at 0x00004079 (357 bytes).
//
// The formula is confirmed instruction by instruction: the first 75 bytes are
// exact (frame, fsincos pair, the 1.0f load at 0x00BBB8D8 into xmm1, cosine
// into xmm5, sine into xmm4, and values[0]), and every product, sign and store
// offset after that agrees with the source below, including the reused
// (1.0f - cosine) in xmm2 and the store of values[7] ahead of values[6].
//
// The body compiles to 359 bytes, not 357. The whole two-byte excess is one
// scheduling choice repeated twice, in values[1] and values[4]: retail emits
// `movaps xmm3, xmm4 / mulss xmm3, [edx+8]` for the sine * axis.z term (copy
// the sine register, multiply by memory - 8 bytes), MSVC 7.1 here emits
// `movss xmm3, [edx+8] / mulss xmm3, xmm4` (load memory, multiply by the
// register - 9 bytes), and it also finishes that term before the left-hand
// product instead of after. Retail uses the memory-first form for the
// axis.y * sine and axis.x * sine terms in values[2], [6], [8] and [9], which
// MSVC reproduces, so the operand order in the source is not the lever:
// writing the term as axis.z * sine changes nothing, and hoisting
// (1.0f - cosine) into a named local makes it worse by sinking the subtraction
// ahead of values[0].
//
// Next shapes worth trying: something that raises register pressure across
// values[1]/[4] so the sine register has to be copied, a different statement
// order for the sixteen assignments, or /Ob/inline settings on the TU.

Matrix4D::Matrix4D(const Coord3D &axis, float angle)
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

    values[0] = axis.x * axis.x + (1.0f - axis.x * axis.x) * cosine;
    values[1] = axis.y * axis.x * (1.0f - cosine) - axis.z * sine;
    values[2] = axis.x * (1.0f - cosine) * axis.z + axis.y * sine;
    values[3] = 0.0f;
    values[4] = axis.y * axis.x * (1.0f - cosine) + axis.z * sine;
    values[5] = axis.y * axis.y + (1.0f - axis.y * axis.y) * cosine;
    values[6] = axis.y * (1.0f - cosine) * axis.z - axis.x * sine;
    values[7] = 0.0f;
    values[8] = axis.x * (1.0f - cosine) * axis.z - axis.y * sine;
    values[9] = axis.y * (1.0f - cosine) * axis.z + axis.x * sine;
    values[10] = axis.z * axis.z + (1.0f - axis.z * axis.z) * cosine;
    values[11] = 0.0f;
    values[12] = 0.0f;
    values[13] = 0.0f;
    values[14] = 0.0f;
    values[15] = 1.0f;
}
