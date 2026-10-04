// cl: /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Target evidence: RenderObjClass vftable VA 0x00BD2F68 entry 42 (+0xA8, the
// slot every BFME 2 caller reaches Update_Sub_Object_Transforms through, e.g.
// call [eax+0xA8] in Animatable3DObjClass::Update_Sub_Object_Transforms at
// 0x001A5900) points to RVA 0x0069E440, whose retail body is the one-byte RET
// folded with DX8_Assert. That same override calls 0x0069E440 directly where
// the source chains to the base implementation. Entry 41 (+0xA4, 0x000B3FD0)
// is the shim's unidentified _bfme_ro_v40, not this function.
// Donor provenance: Open-BFME-1 WW3D2/rendobj.cpp at 071013b3c6f1228dfda315732197bed0fd191209
// defines this default virtual as empty; the donor behavior agrees with retail.
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

void RenderObjClass::Update_Sub_Object_Transforms(void)
{
}
