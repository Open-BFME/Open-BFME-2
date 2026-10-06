// cl: /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// RenderObjClass default ctor at retail 0x0013BF00 (262B).
//
// BFME2 wrote a new body here (BFME1's ctor is a near-empty init list):
// the C4 layout carries float@0x84, int -1s at 0x8C/0x98 and the indexed
// 1.0f factors at 0x90/0x94. The two -1 stores stay immediate (C7) only
// when split across the init-list/body boundary: _bfme_unk_8c(-1) rides
// with the member-ordered inits while _bfme_unk_98 = -1 stays in the body.
// Sharing one -1 in ecx (or ecx,-1 + reg stores) is 5 bytes short, and any
// same-region spelling reproduces it; _bfme_float_84(0.0f) leads the pair
// in member order so its movss precedes them.
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "rendobj.h"
#include "aabox.h"

typedef char RenderObjSizeMatchesRetail[(sizeof(RenderObjClass) == 0xC4) ? 1 : -1];

// ??0RenderObjClass@@QAE@XZ
RenderObjClass::RenderObjClass(void) :
    Bits(DEFAULT_BITS), _bfme_unk_14(1), Transform(1), ObjectScale(1.0f),
    CachedBoundingSphere(Vector3(0, 0, 0), 1.0f),
    CachedBoundingBox(Vector3(0, 0, 0), Vector3(1, 1, 1)),
    IsTransformIdentity(false), Scene(NULL), Container(NULL), User_Data(NULL),
    _bfme_float_84(0.0f),
    _bfme_unk_88(0), _bfme_unk_8c(-1), _bfme_unk_bc(false), _bfme_unk_c0(NULL)
{
    _bfme_opaque_9c[0] = 0;
    _bfme_unk_98 = -1;
    _bfme_unk_bd = true;
    for (int i = 0; i < 2; ++i) {
        _bfme_indexed_factors[i] = 1.0f;
    }
}
