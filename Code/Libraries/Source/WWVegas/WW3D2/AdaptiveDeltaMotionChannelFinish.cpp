// ??0AdaptiveDeltaMotionChannelClass@@QAE@XZ @0x00195F60 133B.
//
// Constructor for the 0x1C-byte channel read_channel allocates at 0x0018F230
// (a sibling body matched in hcanim.cpp).
// The address is pinned in reverse/symbols.csv from the retail REL32 at
// 0x0018F261, and this body confirms the 0x1C layout the matched loader
// (AdaptiveDeltaLoadW3D.cpp) already reads: the seven fields zeroed through
// +0x18, then the one-time filter-table build.
//
// Two codegen facts this body depends on, both read off the retail bytes:
// the flag load may not be hoisted above the member stores (retail loads it at
// 0x195F80, after the last store at 0x195F7F), and the loop closes on a SIGNED
// `jl` back-edge. See the comments at each site.
// cl: /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /EHsc
#include "wwmath.h"
static float filtertable[256] = { 0.00000001f, 0.0000001f, 0.000001f, 0.00001f, 0.0001f, 0.001f, 0.01f, 0.1f, 1.0f, 10.0f, 100.0f, 1000.0f, 10000.0f, 100000.0f, 1000000.0f, 10000000.0f };
static bool table_valid = false;
class AdaptiveDeltaMotionChannelClass {
public:
    AdaptiveDeltaMotionChannelClass();
private:
    unsigned long PivotIdx;
    unsigned long Type;
    int VectorLen;
    unsigned long NumFrames;
    unsigned long DataByteCount;
    float Scale;
    unsigned long *Data;
};
AdaptiveDeltaMotionChannelClass::AdaptiveDeltaMotionChannelClass()
{
    PivotIdx = 0;
    Type = 0;
    VectorLen = 0;
    NumFrames = 0;
    DataByteCount = 0;
    Scale = 0.0f;
    Data = 0;

    // Read the flag through a volatile byte so the load cannot be hoisted above
    // the member stores: retail stores all seven fields first (0x195F6A..0x195F7F)
    // and only then loads the flag and branches (0x195F80). MSVC's scheduler
    // otherwise sinks the stores below the independent flag load.
    volatile char *const flag = (volatile char *)&table_valid;
    if (0 == *flag) {
        float ratio = 0.0f;
        // Retail walks edx from filtertable+16 up to filtertable+256 and closes
        // the loop with a SIGNED `jl` back-edge (0x195FD8, 7c cb). Comparing two
        // POINTERS makes MSVC emit the unsigned `jb` (72 cb) instead, which was
        // the last mismatching byte in this body; comparing the same two values
        // as int keeps the identical `cmp edx,0xDB6BD8` and yields the signed
        // form retail has.
        float *const end = filtertable + 256;
        float *entry = filtertable + 16;
        do {
            *entry = 1.0f - WWMath::Sin(DEG_TO_RADF(0.375f * ratio));
            ratio += 1.0f;
            ++entry;
        } while ((const int)entry < (const int)end);
        table_valid = true;
    }
}
