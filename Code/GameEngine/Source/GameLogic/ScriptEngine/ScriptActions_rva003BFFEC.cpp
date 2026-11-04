// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -DNDEBUG -MD  /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
#include "../../../Include/GameLogic/ScriptActionsBFME2.h"
// ?Rva003BFFECDo@ScriptActions@@QAEXABVAsciiString@@_N@Z @0x003BFFEC 97B
// Display fullscreen plus trigger via Display virtual 0x114 check, rowed
// rva002B2466 0x002B2466 with 0 0 1 1, StringBase pin 0x000365F0 temp,
// Display virtual 0x108 with AsciiString plus 0x40 -1 -1.
// Evidence: TheDisplay 0x009FE9D8; caller 0x003CBBB6;
// precedent DisplayRva002B2466 fullscreen 0 0 1 1.
#include "ascii_string.h"

#include "../../../Include/GameClient/Display.h"

void ScriptActions::Rva003BFFECDo(const AsciiString &name, bool unused)
{
	(void)unused;
	if (TheDisplay->isMoviePlaying())
		return;
	TheDisplay->rva002B2466(0.0f, 0.0f, 1.0f, 1.0f);
	TheDisplay->rva0025C97E(name, 0x40, -1, -1);
}
