// ?Rotate@Coord2D@@QAEAAV1@M@Z
// partial score=0.95 date=2026-09-05
// ?Rotate@Coord2D@@QAEAAV1@M@Z
// partial score=0.95 date=2026-09-05
//
// Coord2D::Rotate(float) at 0x00003916, 101 bytes. The in-place overload of
// the Rotate already landed at 0x000039BB
// (Code/Libraries/Source/WWVegas/WWMath/coord2d_rotate.cpp). THIS BODY BELONGS
// IN THAT FILE as a sibling, not in a new TU -- the two-argument overload
// there already establishes the `// cl: /O1 /arch:SSE2` line and the
// four-x87-instruction convention for the fsincos MSVC 7.1 will not fuse.
//
// SETTLED, do not re-derive:
//
//   * retail really does the trigonometry TWICE. It calls sin then cos through
//     the CRT import thunks, spills both results, and then overwrites both
//     with fsincos over the same angle. reverse/ghidra_functions.csv names the
//     thunks independently of reverse/symbols.csv's pins (which were derived
//     from this very body, so they would otherwise be circular):
//       0x00629216 sin  -- called first, at +0x10, result to [ebp-4]
//       0x0062920A cos  -- called second, at +0x1E, result to [ebp-8]
//   * the slot roles are fixed three independent ways and all three agree on
//     sine=[ebp-4], cosine=[ebp-8]: the two call spills above; fsincos leaves
//     cosine on top of the x87 stack, so retail's `fstp [ebp-8]` ahead of
//     `fstp [ebp-4]` pops cosine into the lower slot; and the products read
//     [ebp-8] against x and [ebp-4] against y, i.e. x' = x*cos - y*sin.
//   * length, instruction selection and register use are all exactly right.
//     The frame is `push ecx / push ecx`, eight bytes, two float slots and no
//     third local -- `rotated` stays in a register.
//
// THE ONE REMAINING GAP is which of the two locals gets [ebp-4]. MSVC 7.1 puts
// the variable holding the COSINE at [ebp-4] and the sine at [ebp-8]; retail
// is the other way round. That inverts the two call spills, the two asm
// stores, and the operand order of the four products -- about ten bytes, and
// nothing else in the body differs.
//
// FOUR PERMUTATIONS MEASURED, all four produce cosine=[ebp-4]. The lever is
// none of the three obvious ones, so do not spend time on them again:
//
//   C++ assignment order   asm fstp order      result
//   sine, cosine           cosine, sine        cosine=[ebp-4]
//   cosine, sine (decls)   cosine, sine        cosine=[ebp-4]
//   sine, cosine           sine, cosine        cosine=[ebp-4]
//   cosine, sine           cosine, sine        cosine=[ebp-4]
//
// Declaration order, initialised-vs-assigned declarations, and the order the
// __asm block names the locals were each varied independently and none of them
// moved the assignment. A rename probe (zzz for the cosine, aaa for the sine)
// also left the cosine in [ebp-4], so it is not symbol-table or alphabetical
// order either.
//
// What that leaves, and what the next pass should try: the slot is being
// chosen by something outside the two locals -- most likely the ORDER MSVC
// assigns homes to inline-asm-referenced locals relative to the x87 stack
// state it has to model across the __asm block. Worth trying, in order:
// writing the two stores as one `fstp` plus one `fstp` separated by other asm;
// giving the asm block an explicit `fld`/`fxch` so the top-of-stack variable
// is the sine; declaring a third dummy float to shift the frame; and
// /arch:SSE (not SSE2) or /Oy- to see whether the frame layout changes at all.
//
// cl: /O1 /arch:SSE2

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
    float sine = (float)sin(angle);
    float cosine = (float)cos(angle);

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
