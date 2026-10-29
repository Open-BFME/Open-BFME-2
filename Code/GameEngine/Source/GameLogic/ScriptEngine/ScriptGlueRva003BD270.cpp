// cl: -O1 -arch:SSE -G7 -DNDEBUG -MD /I. /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "Code/GameEngine/Include/GameLogic/ScriptActionsBFME2.h"
//
// Two small stdcall free functions from the 0x003BD2xx ScriptEngine/GameLogic
// glue area (dump range 18).
//
// ?doHeroSelectButtonFlash@ScriptActions@@IAEXHH@Z @0x003BD270 29B: forwards to the 0x002D36AE host
// method (pinned) on the 0x00DFF028 global with (a, BfmeClientFramesPerSecond * b). The
// callee null-guards its inner delegate and tail-jumps, so no return value
// is taken here; void is the honest reading.
//
// ?rva003BD2A6@@YGXH@Z @0x003BD2A6 40B: guarded GameLogic byte setter: when
// GameLogic+0x11C differs from the argument's low byte, calls the rowed
// 0x0023D68E GameLogic walker (pinned; ecx arrives as TheGameLogic, which the
// caller holds across the compare) and then stores the byte. Argument stays
// a full dword in ebx (no movzx), hence int rather than unsigned char.
extern int BfmeClientFramesPerSecond;

class Rva002D36AEHost
{
public:
	void rva002D36AE(int a, int b);
};

class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;



void ScriptActions::doHeroSelectButtonFlash(int a, int b)
{
	((Rva002D36AEHost *)theRadarWindowOverrideSource)->rva002D36AE(a, BfmeClientFramesPerSecond * b);
}

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

void ScriptActions::rva003BD2A6(bool value)
{
	if (TheGameLogic->m_field11C != (unsigned char)value) {
		TheGameLogic->rva0023D68E((bool &)value); // retail pushes the same ebx it compared as bl
		TheGameLogic->m_field11C = (unsigned char)value;
	}
}
