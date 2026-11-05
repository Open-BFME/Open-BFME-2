// cl: /MD -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoDYF@@YAXPBD@Z
// retail 0x0041270D, 36 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/Common/BfmeConv796.cpp. Recompiled /Os the
// donor body is byte-identical to retail once relocations are masked (unique
// hit on unclaimed .text). Only the placed body is defined here; the donor's
// other definitions are omitted.
//
// Target-side correction: the donor's member view is named BfmeGlobDYF, but
// the call this body makes lands on retail 0x001EE5BE, which the ledger
// already carries as the matched
// ?_bfme_setEngineVisibility@Mouse@@QAEX_N@Z. The call is therefore made
// through the established retail name, the same spelling the already-matched
// call sites use (e.g. GameEngineClientSubsystems.cpp), rather than through
// a second name for one address.
// Target-side correction: the donor compares against its named string global
// bfmeStrDYF, but retail's push reads VA 0x00BBC408, the narrow literal "true"
// (the ledger's string-initializer evidence puts "true" at 0x00BBC408 and
// "false" at 0x00BBC410). Spelling the literal directly keeps the same push
// shape and gives this unit a definition for the operand, so it links.
#include <string.h>

// Retail's singleton at 0x012F4C5C is EA's Mouse *TheMouse (defined once in
// GameEngine/Source/GameClient/Input/Mouse.cpp), so the extern must be spelled
// Mouse * to mangle to ?TheMouse@@3PAVMouse@@A.
class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

extern Mouse *TheMouse;

void bfmeGoDYF(const char *s)
{
	TheMouse->_bfme_setEngineVisibility(_strcmpi(s, "true") == 0);
}