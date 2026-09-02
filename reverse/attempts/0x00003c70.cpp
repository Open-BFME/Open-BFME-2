// ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z
// partial score=0.98 date=2026-09-02
// ?CrossProduct@Coord3D@@QAEAAV1@ABUCoord3DBase@@0@Z
// partial score=0.98 date=2026-09-02
// cl: /O2 /arch:SSE /DNDEBUG /MD
//
// The SSE scalar cross product at 0x00003C70. Returning Coord3D & rather
// than void is the lever the two earlier banks were missing: it is what
// produces the mov eax, ecx and the push esi / pop esi that the void form
// could not account for, and it takes the body from 93 bytes to exactly 97.
//
// 81 of 97 bytes now match, in one window: 0x00 through 0x32 and 0x4F to the
// end are exact, and every difference is inside 0x33..0x4E. Both differences
// are the same thing - retail loads left.x into a register and multiplies by
// the right operand, cl 13.10 loads the right operand and multiplies by
// left.x. Naming the minuends is what fixed the x term and the first half of
// y; naming the subtrahends too changes nothing, swapping the operands in the
// source changes nothing (cl canonicalises), and hoisting left.x into a local
// is much worse - it moves the first difference from 0x33 back to 0x03.
//
// The name is still inferred: ret 8 with two stack arguments, the destination
// in ecx and returned in eax makes it a two-argument member returning a
// reference. Nothing in the image calls this body directly to settle it.
struct Coord3DBase
{
    float x;
    float y;
    float z;
};

class Coord3D : public Coord3DBase
{
public:
    Coord3D &CrossProduct(const Coord3DBase &left, const Coord3DBase &right);
};

Coord3D &Coord3D::CrossProduct(const Coord3DBase &left, const Coord3DBase &right)
{
    const float xt = left.y * right.z;
    x = xt - left.z * right.y;
    const float yt = left.z * right.x;
    y = yt - left.x * right.z;
    const float zt = left.x * right.y;
    z = zt - left.y * right.x;
    return *this;
}
