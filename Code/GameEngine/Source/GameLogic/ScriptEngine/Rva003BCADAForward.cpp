// cl: -O1 -arch:SSE -G7  /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva003BCADAForward@ScriptActions@@QAEXABVAsciiString@@0@Z @0x003BCADA 14B: script forwards to TheTacticalView slot 0xa0.
// Evidence: mov ecx,[0xDFEA3C]=TheTacticalView mov eax,[ecx] jmp [eax+0xa0]; caller 0x003CD771; sibling Rva003BBE91Set same TheTacticalView virtual shape.
#include "../../../Include/GameClient/View.h"
extern View *TheTacticalView;

void ScriptActions::Rva003BCADAForward(const AsciiString &asciiString, const AsciiString &b)
{
	TheTacticalView->cameraEnableSlaveMode(asciiString, b);
}
