// cl: /O1
// BFME1 donor1281192f682ce6f29b8f06b7daea4b5e8fdfbb24,
// game/GameEngine/Source/Common/Bfme5TinyTwentyNine.cpp, compiled /O1.
// Target Ghidra00045837/22B proves control word+14, pointers+8/+C,
// arithmetic division by8, and EAX result0 only when control==1 and count0.
// The element payload and original names remain unknown. Constness and
// the unsigned count expression are donor/source inferences. The whole
// donor unit places only this body under these settings.
struct Rva00045837Element
{
	unsigned int opaque[2];
};

// Callers name the owner: W3DDisplay's +0x188 object and MilesAudioManager's
// +0xBE8 window both reach this query and free the same object through the
// SubTitleWindow destructor 0x00260A3C, and that constructor (0x00260865)
// puts the record vector at +8/+C and the state word (initially 4) at +0x14.
// Both callers test al, so the query returns bool; one returned expression
// gives retail's xor eax,eax false path. Its name stays address-derived.
#include "../../Include/GameClient/SubTitleWindow.h"

bool SubTitleWindow::rva00045837() const
{
	return !(field14 == 1 && !((unsigned int)(field0C - field08) > 0));
}
