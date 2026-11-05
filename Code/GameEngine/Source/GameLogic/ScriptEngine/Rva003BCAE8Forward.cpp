// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCAE8Forward@ScriptActions@@QAEXXZ @0x003BCAE8 14B: script forwards to TheTacticalView slot 0xa4.
// Evidence: mov ecx,[0xDFEA3C]=TheTacticalView mov eax,[ecx] jmp [eax+0xa4]; caller 0x003CD77D; sibling Rva003BCADAForward same tail shape slot 0xa0.
#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;

void ScriptActions::Rva003BCAE8Forward()
{
	TheTacticalView->cameraDisableSlaveMode();
}
