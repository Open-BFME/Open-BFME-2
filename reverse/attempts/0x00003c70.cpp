// ?d_00003c70@@YAXXZ
// partial score=0.95 date=2026-08-31
// ?d_00003c70@@YAXXZ
// partial score=0.95 date=2026-08-31
// cl: /O1 /arch:SSE2
// exports.csv names 0x00003C70 ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z.
// 97 bytes against 97, every instruction the same kind in the same place, and
// the arithmetic is confirmed: the result is cross(param1, param2) written into
// this and this returned.
//
// What is left is the operand side of two products. Retail loads the param2
// member into the register and multiplies by the param1 member:
//     movss xmm0,[esi+8] ; mulss xmm0,[edx+4]
// MSVC 7.1 emits the swap for the first two terms, and hoists that load ahead
// of `push esi` because param1 is already in edx:
//     movss xmm1,[edx+8] ; push esi ; ... ; mulss xmm1,[esi+4]
// The third term already matches. Writing the products the other way round
// changes nothing - MSVC canonicalizes a*b and b*a to the same code here - and
// neither do float temporaries per term nor split assign-then-subtract
// statements. The remaining lever is whatever makes the second argument the
// first thing loaded.
Coord3D &Coord3D::CrossProduct(const Coord3DBase &left, const Coord3DBase &right)
{
    x = right.z * left.y - right.y * left.z;
    y = right.x * left.z - left.x * right.z;
    z = left.x * right.y - left.y * right.x;

    return *this;
}
