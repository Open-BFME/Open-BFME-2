// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception /D_STLP_USE_STATIC_LIB
// stlport
//
// Rva00468908Parse, retail 0x00468908 (215 B). INI field callback of the transport upgrade-creation
// trigger list (WorldBuilder twin 0x01158200, "iniParseQuery: Too many triggers, can only have %d."):
// refuses a fifth trigger, reads two tokens, and when both are present builds a trigger record
// {upgrade name, object name, count (default 99999)}, lets INI::parseUnsignedInt fill the count and
// appends the record to the owner's trigger vector at +0x180. Evidence: target bytes, the WorldBuilder
// twin, rowed callees (record dtor 0x00466E23, push_back 0x004688D1, parseUnsignedInt 0x0002EF72) and
// the record layout used by TransportContain::UpdateUpgradeCreationTriggers (0x00468045).
#include "ascii_string.h"
#include "Common/INIException.h"
#include <vector>

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanInt(const char *token);
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
};

class Rva00466E23
{
public:
	Rva00466E23() : count(99999) {}
	~Rva00466E23();
	AsciiString upgrade;
	AsciiString object;
	unsigned count;
};

struct BfmeStringRecord00466E64 { int a[3]; };
template <> void _STL::vector<BfmeStringRecord00466E64, _STL::allocator<BfmeStringRecord00466E64> >::push_back(const BfmeStringRecord00466E64 &);

class Rva00468908Owner
{
public:
	char pad00[0x180];
	_STL::vector<BfmeStringRecord00466E64> triggers;
};

void Rva00468908Parse(INI *ini, void *instance, void *store, const void *userData)
{
	Rva00468908Owner *owner = (Rva00468908Owner *)instance;
	if (owner->triggers.size() >= 4)
		throw INIException(1, "iniParseQuery: Too many triggers, can only have %d.", 4);
	const char *first = ini->getNextTokenOrNull(0);
	const char *second = ini->getNextTokenOrNull(0);
	if (first != 0 && *first != 0 && second != 0 && *second != 0)
	{
		Rva00466E23 record;
		record.upgrade.set(first);
		record.object.set(second);
		INI::parseUnsignedInt(ini, instance, &record.count, userData);
		owner->triggers.push_back(*(const BfmeStringRecord00466E64 *)&record);
	}
}
