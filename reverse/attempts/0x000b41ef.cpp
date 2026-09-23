// BfmeFixedObject60CopyCtorCandidate
// partial score=0.54 date=2026-09-23
// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ivendor/stlport
// Neutral target-shaped record view: 3 scalar words followed by three 16-byte blocks.
// The original element name and the 16-byte block's public identity are unknown.
// Target: 0xB41EF spans 122 bytes and returns with ret 4 at 0xB4266..0xB4268.
// The compiler-emitted array constructor calls a thiscall no-op block ctor and
// the __stdcall vector constructor iterator; both helpers match independently.
// Partial only: 114 non-relocation bytes, 61 match (score 0.54); public names unknown.
#include <vector>
#include <stl/_uninitialized.h>
struct BfmeFixedBlock16 {
    unsigned int words[4];
    BfmeFixedBlock16() {}
};
struct BfmeFixedObject60 {
    unsigned int word_00, word_04, word_08;
    BfmeFixedBlock16 blocks_0C[3];
    BfmeFixedObject60(const BfmeFixedObject60& rhs)
      : word_00(rhs.word_00), word_04(rhs.word_04), word_08(rhs.word_08) {
        blocks_0C[0].words[0] = rhs.blocks_0C[0].words[0];
        blocks_0C[0].words[1] = rhs.blocks_0C[0].words[1];
        blocks_0C[0].words[2] = rhs.blocks_0C[0].words[2];
        blocks_0C[0].words[3] = rhs.blocks_0C[0].words[3];
        blocks_0C[1].words[0] = rhs.blocks_0C[1].words[0];
        blocks_0C[1].words[1] = rhs.blocks_0C[1].words[1];
        blocks_0C[1].words[2] = rhs.blocks_0C[1].words[2];
        blocks_0C[1].words[3] = rhs.blocks_0C[1].words[3];
        blocks_0C[2].words[0] = rhs.blocks_0C[2].words[0];
        blocks_0C[2].words[1] = rhs.blocks_0C[2].words[1];
        blocks_0C[2].words[2] = rhs.blocks_0C[2].words[2];
        blocks_0C[2].words[3] = rhs.blocks_0C[2].words[3];
    }
};
template void _STL::_Construct<BfmeFixedObject60, BfmeFixedObject60>(BfmeFixedObject60 *, const BfmeFixedObject60&);
