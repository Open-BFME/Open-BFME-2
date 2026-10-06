// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva002D46ADSet@@YAXH@Z retail 0x002D46AD 155B unlock lane.
// Evidence: static AsciiString "APT:PalantirResources" with atexit plus local
// AsciiString formatted "%d" or set to g_00BBD40C then
// BfmeAptWindowManager::rva00225375 with TheRva00222A8BTarget; caller 0x002D47D9.
#include "ascii_string.h"

class BfmeAptWindowManager
{
public:
	void rva00225375(const AsciiString &key, const AsciiString &value, bool flag);
};

class Rva00222A8BTarget
{
public:
	void rva00225375(const AsciiString &key, const AsciiString &value, bool flag);
};

extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_00BBD40C[];

void Rva002D46ADSet(int count)
{
	static AsciiString s_key("APT:PalantirResources");
	AsciiString s_value;
	if (count >= 0)
		s_value.format("%d", count);
	else
		s_value.set(g_00BBD40C);
	((BfmeAptWindowManager *)TheRva00222A8BTarget)->rva00225375(s_key, s_value, false);
}
