// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ?Rva0050EE72Set@@YAXHABVAsciiString@@HABVUnicodeString@@@Z @0x0050EE72 106B
// APT field setter: key.format APT:_level%u.%s_field%d via rowed 0x00038150
// plus pinned bfmeSetText 0x00225301 plus releaseBuffer 0x00036410;
// team AsciiString empty via ""; manager 0x009FE4CC.
#include "../../../Include/Common/BfmeStringData.h"
#include "ascii_string.h"
#include "unicode_string.h"
class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &, const UnicodeString &, bool);
};
class Rva00222A8BTarget
{
};
class Rva00222A8BTarget;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct TeamNameRef
{
	const char *m_name08;
};

void __cdecl Rva0050EE72Set(int level, const AsciiString &team, int field, const UnicodeString &value)
{
	AsciiString key;
	const char *teamName;
	const BfmeStringData<char> *h = *(const BfmeStringData<char> *const *)&team;
	if (h)
		teamName = (const char *)&h->text[0];
	else
		teamName = "";
	key.format("APT:_level%u.%s_field%d", level, teamName, field);
	g_bfmeAptWindowManager->bfmeSetText(key, value, false);
}
