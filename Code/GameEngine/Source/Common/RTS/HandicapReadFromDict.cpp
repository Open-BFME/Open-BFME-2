// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?readFromDict@Handicap@@QAEXPBVDict@@@Z @0x003B0EBD 227B
// Handicap::readFromDict loads 2x2 multipliers from Dict via HANDICAP_<type>_<thing> keys.
// Evidence: neighbour Handicap::getHandicap proves 2x2 table; donor open-bfme-1
// game/GameEngine/Source/Common/RTS/Handicap_readFromDict_Thunk.cpp same key
// construction; callees nameToKey 0x9FA65 getReal 0x3131FC releaseBuffer 0x36410
// set 0x55F5 concat 0x5629 TheNameKeyGenerator match retail call order.
#include "ascii_string.h"

typedef float Real;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &s);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Dict
{
public:
	float getReal(int key, bool *exists) const;
};

class Handicap
{
public:
	enum HandicapType
	{
		BUILDCOST,
		BUILDTIME
	};

	void readFromDict(const Dict *d);

private:
	enum ThingType
	{
		GENERIC,
		BUILDINGS
	};

	Real m_handicaps[2][2];
};

void Handicap::readFromDict(const Dict *d)
{
	const char *htNames[2] =
	{
		"BUILDCOST",
		"BUILDTIME",
	};

	const char *ttNames[2] =
	{
		"GENERIC",
		"BUILDINGS",
	};

	AsciiString c;
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			((StringBase<char> *)&c)->clear();
			((StringBase<char> *)&c)->set("HANDICAP_");
			((StringBase<char> *)&c)->concat(htNames[i]);
			((StringBase<char> *)&c)->concat("_");
			((StringBase<char> *)&c)->concat(ttNames[j]);
			NameKeyType k = TheNameKeyGenerator->nameToKey(c);
			bool exists;
			Real r = d->getReal(k, &exists);
			if (exists)
				m_handicaps[i][j] = r;
		}
	}
}
