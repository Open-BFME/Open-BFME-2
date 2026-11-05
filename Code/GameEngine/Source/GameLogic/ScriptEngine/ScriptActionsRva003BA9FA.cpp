// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameClient/Display.h"
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BA9FA@ScriptActions@@QAEXMMMM@Z @0x003BA9FA 51B: ScriptActions member four floats forwarding to Display slot 0xcc.
// Evidence: ret 16 four float args; fld [esp+0x10] mov ecx [TheDisplay] sub esp 0x10 four fld-fstp to [esp]; call [eax+0xcc]; caller 0x003CAB07.
extern Display *TheDisplay;

void ScriptActions::Rva003BA9FA(float a0, float a1, float a2, float a3)
{
	TheDisplay->slot51(a0, a1, a2, a3);
}
