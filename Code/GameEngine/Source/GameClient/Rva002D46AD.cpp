// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva002D46ADSet@@YAXH@Z retail 0x002D46AD 155B unlock lane.
// Evidence: static AsciiString "APT:PalantirResources" with atexit plus local
// AsciiString formatted "%d" or set to g_00BBD40C then
// BfmeAptWindowManager::rva00225375 with TheRva00222A8BTarget; caller 0x002D47D9.
#include "ascii_string.h"

#include "../../../Libraries/Source/Apt/BfmeAptWindowManager.h"

#include "../../Include/Common/Rva00222A8BTarget.h"

class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern const char g_00BBD40C[];

void Rva002D46ADSet(int count)
{
	static AsciiString s_key("APT:PalantirResources");
	AsciiString s_value;
	if (count >= 0)
		s_value.format("%d", count);
	else
		s_value.set(g_00BBD40C);
	g_bfmeAptWindowManager->rva00225375(s_key, s_value, false);
}
