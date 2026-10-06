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
// IDENTITY IS NOT RECOVERED.  Nothing in the image names the table, so the
// global is named for the lookup and disclaims identity.
//
// The table is declared here rather than taken from a retail header because
// none of the image's names resolve to it; it is the storage this body reads,
// and nothing else in the image writes through a symbol for it.

// shl eax,5 / add / indexed load off the ScreenTextureStageStates table.
extern unsigned int ScreenTextureStageStates[8][32];

int __cdecl Rva00945460Lookup(int a, int b)
{
	return ScreenTextureStageStates[a][b];
}