// ?rva005687DF@@YAHABI0@Z
// partial score=1.0 date=2026-10-05
// cl: /O1 /Ob1
// Donor BFME1@6583b3c1ff21db4a561285717028fdafc780b7db,
// game/GameEngine/Source/Common/BfmeConv881.cpp blob8831c2f9dfa0d0d35893925ba29bca090c78610c.
// Full source profile /O2 /Ob1 /GX- /GS /G7 /arch:SSE places two tied
// STLport distance labels at5687DF/16. Native reads two referenced raw32
// words, subtracts, and arithmetic-shifts by2. Pointer element type and
// original STL identity remain donor-only. No standalone Ghidra, E8/E9,
// or absolute-VA entry witness; packed RET boundaries alone do not prove
// a standalone function. This exact raw-ABI body is evidence, not progress.
int __cdecl rva005687DF(const unsigned int &first, const unsigned int &last)
{
    return static_cast<int>(last - first) >> 2;
}
