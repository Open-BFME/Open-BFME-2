// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
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
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
extern "C" unsigned char bfmeStrDYF[];

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
	TheMouse->_bfme_setEngineVisibility(_strcmpi(s, (const char *)bfmeStrDYF) == 0);
}