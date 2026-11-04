// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BAA2D@ScriptActions@@QAEXM@Z @0x003BAA2D 25B: ScriptActions member one float forwarding to Display slot 0xd0.
// Evidence: ret 4 one float arg; mov ecx TheDisplay fld [esp+4] mov eax [ecx] push ecx fstp [esp] call [eax+0xd0]; caller 0x003CAB22.
#include "../../../Include/GameClient/Display.h"

void ScriptActions::Rva003BAA2D(float a0)
{
	TheDisplay->slot52(a0);
}
