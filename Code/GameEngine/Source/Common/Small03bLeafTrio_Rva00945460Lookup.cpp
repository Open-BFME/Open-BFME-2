// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// ?Rva00945460Lookup@@YAHHH@Z
// retail 0x00143310, 19 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/Small03bLeafTrio.cpp (reference/open-bfme-1),
// recompiled /Os: byte-identical to retail once relocations are masked (unique
// masked placement on unclaimed .text). Only the placed body is defined here;
// the donor's other two definitions are omitted.
//
// WHAT THE BYTES SHOW.  Two stack arguments, `shl eax,5` on the first and an
// indexed load on the second, so this is a lookup into an 8x32 table of dwords:
// the scale is 32 entries of 4 bytes.  ecx is untouched, so this is __cdecl and
// caller-cleaned -- both indices arrive on the stack.
//
// THE TABLE.  0x009ECA38 is the data ledger's DX8Wrapper::TextureStageStates
// (protected, dx8wrapper.cpp; WW3D2 declares it unsigned [MAX_TEXTURE_STAGES][32]),
// so this function reads it as a friend of the canonical DX8WrapperClass.h. The
// function's own identity is still not recovered.

#include "../../../Libraries/Source/WWVegas/WW3D2/DX8WrapperClass.h"

// shl eax,5 / add / indexed load off the texture-stage-state table.
int __cdecl Rva00945460Lookup(int a, int b)
{
	return DX8Wrapper::TextureStageStates[a][b];
}