// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoFHG@@YGXPAX000@Z
// retail 0x001E19CE, 26 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv897.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// Retail 0x001E19E8 is a ghidra function start (FUN_005e19e8) with no ledger
// row and no pin, so the donor's own name is pinned for it. The address is
// read off retail's REL32 at 0x001E19E0: next-instruction 0x001E19E5 plus
// the displacement 0x00000003. Carried from the donor source; the body at the
// address remains unrecovered.
extern void __stdcall bfmeTailFHG(void *a, void *b, int c, int d);

void __stdcall bfmeGoFHG(void *a, void *b, void *c, void *d)
{
	if (a)
		bfmeTailFHG(a, b, 0, 0);
}