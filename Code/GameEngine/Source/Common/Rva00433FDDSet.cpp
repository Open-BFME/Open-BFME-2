// cl: /MD
// ?rva00433FDD@AptSaveLoad@@QAEXXZ, retail 0x00433FDD, 22 bytes.
// Sets +0x27C to 3 if dword at +0x280 is nonzero else 1.
// Evidence: callers at 0x004344E5 0x00435811 share +0x27C +0x280 layout; both
// are AptSaveLoad methods calling it on their own this (state, pending).
#include "../../Include/GameClient/AptSaveLoad.h"
void AptSaveLoad::rva00433FDD()
{
	field27C = field280 ? 3 : 1;
}
// ?rva00433D96@AptSaveLoad@@QAEXXZ, retail 0x00433D96, 27 bytes.
// Sets +0x27C to 10 after pinned Rva00437E9C(1), then tail-jmps rowed Rva00433D27Enable.
// Evidence: same +0x27C layout as sibling 0x00433FDD; callees pinned 0x00437E9C and rowed 0x00433D27; caller 0x002409BD.
void Rva00437E9C(int);
void Rva00433D27Enable();
void AptSaveLoad::rva00433D96()
{
	Rva00437E9C(1);
	field27C = 10;
	Rva00433D27Enable();
}
