// ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z
// partial score=0.97 date=2026-09-01
// ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z
// partial score=0.97 date=2026-09-01
// Coord3D::CrossProduct(const Coord3DBase &, const Coord3DBase &) at
// 0x00003C70 (97 bytes). Named by exports.csv.
//
// 2026-09-01: two of the three terms are now exact. The lever the previous
// attempt was missing is a NAMED TEMPORARY FOR THE MINUEND. Written as one
// expression, `a - b`, MSVC 7.1 evaluates the subtrahend first and then swaps
// its operands so the load comes from whichever base register was set up
// first; assigning the minuend to a local and subtracting into it forces
// retail's order. That fixed x outright and fixed the first half of y.
//
// One 9-byte window is left, at +0x33: the subtrahend of y.
//     retail:  movss xmm1,[edx]   ; mulss xmm1,[esi+8]   (left.x * right.z)
//     MSVC:    movss xmm1,[esi+8] ; mulss xmm1,[edx]
// Everywhere else - five of the six products - MSVC loads whichever operand is
// written first, which is how the source below is ordered. Only this one gets
// swapped. Refuted as the lever: writing it right.z * left.x, a named local
// for the whole subtrahend, a named local for left.x (both immediately before
// the statement and hoisted to the top of the function, the latter costing
// four bytes), computing the subtrahend before the minuend, minuend temps for
// all three terms, right's three members hoisted into locals, a pointer
// instead of a reference for right, and writing every product left-first.
//
// Next lever to try: something that changes which of edx/esi is live at that
// point - the register assignment is the only thing that distinguishes this
// product from the five that work.

Coord3D &Coord3D::CrossProduct(const Coord3DBase &left, const Coord3DBase &right)
{
    const float mx = right.z * left.y;
    x = mx - right.y * left.z;
    const float my = right.x * left.z;
    y = my - left.x * right.z;
    z = left.x * right.y - right.x * left.y;

    return *this;
}
