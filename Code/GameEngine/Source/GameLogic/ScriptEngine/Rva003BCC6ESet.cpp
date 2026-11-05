// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCC6ESet@ScriptActions@@QAEX_N@Z @0x003BCC6E 19B: script sets ScriptEngine +0x1a4d6 byte from bool arg.
// Evidence: mov al,[esp+4] mov ecx,[0xDFE16C]=g_Va009FE16C mov [ecx+0x1a4d6],al ret 4; caller 0x003CDA9B; siblings Rva003BCA7BSet Rva003BCA8ESet same shape.
#include "../../../Include/GameLogic/ScriptEngine.h"

void ScriptActions::Rva003BCC6ESet(bool b)
{
	TheScriptEngine->m_ChooseVictimAlwaysUsesNormal = b;
}
