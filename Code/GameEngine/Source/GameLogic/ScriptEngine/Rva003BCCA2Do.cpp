// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameClient/Display.h"
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCCA2Do@ScriptActions@@QAEXXZ @0x003BCCA2 36B: free check GlobalData byte +0x11CB then Display slot 0x150 with (10000,1).
// Evidence: retail mov eax,[0xDFE758]=TheWritableGlobalData cmp [eax+0x11CB],0 jne ret; mov ecx,[0xDFE9D8]=TheDisplay mov eax,[ecx] push 1 push 0x2710 call [eax+0x150]; caller 0x003CDC74; neighbours Rva003BCBC7Set Rva003BCCC6Do same dir.
#include "../../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

extern Display *TheDisplay;

void ScriptActions::Rva003BCCA2Do()
{
	if (TheWritableGlobalData->field11CB != 0)
		return;
	TheDisplay->slot84(10000, 1);
}
