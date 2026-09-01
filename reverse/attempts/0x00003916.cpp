// ?Rotate@Coord2D@@QAEAAV1@M@Z
// partial score=0.96 date=2026-09-01
// ?Rotate@Coord2D@@QAEAAV1@M@Z
// partial score=0.96 date=2026-09-01
// Coord2D::Rotate(float) at 0x00003916 (101 bytes).
//
// 97 of 101 bytes are in place with the source below: prologue, both CRT
// calls, the fsincos block, the mixed x87/SSE tail and both member stores all
// land. What is left is which local sits at [ebp-4].
//
// Retail spills the FIRST call's result to [ebp-4] and the second to [ebp-8].
// MSVC 7.1 does the opposite here: with two float locals that are spilled from
// call returns it fills bottom-up, first spill to [ebp-8], second to [ebp-4].
// Refuted as the deciding factor: declaration order, uninitialised-then-
// assigned, identifier names (cosine/sine, acosine/zsine, aa/zzzz, sine/
// tCosine - no alphabetical or length rule survives all four), the order of
// the two fstp inside the __asm, and the order of the two tail statements.
// The sibling at 0x000039BB, which has no calls before its __asm, DOES follow
// declaration order, so the call spills are what take the choice away.
//
// Swapping the source to call cos() first makes all 101 bytes match except the
// two REL32s, which then point at 0x0062920A/0x00629216 the other way round.
// So either retail called cos first and reverse/ghidra_functions.csv has the
// two thunks swapped, or MSVC needs a shape not tried here. The thunk table
// reads cos/fabs/sin/sqrt at 0x62920A/0x629210/0x629216/0x62921C - alphabetical,
// which is why the ledger pins were left as Ghidra names them.
//
// Next shapes worth trying: a two-element array or a small struct for the pair,
// a helper that returns both, or __asm writing through pointers - anything that
// takes the slot choice away from the call-return spill allocator.
//
// Re-checked 2026-09-01 with the flags spelled -O1 -arch:SSE2 -Oi (leading
// DASHES - Git Bash rewrites a slash-leading argument into a Windows path
// before cl sees it, so a sweep passing "/O1" through the shell tests
// something else): /Oi still gives fcos + fsin and keeps both results in x87
// registers. The fsincos reading stands.

Coord2D &Coord2D::Rotate(float angle)
{
    float sine = (float)sin(angle);
    float tCosine = (float)cos(angle);

    __asm
    {
        fld angle
        fsincos
        fstp tCosine
        fstp sine
    }

    float new_x = tCosine * x - sine * y;

    y = sine * x + tCosine * y;
    x = new_x;
    return *this;
}
