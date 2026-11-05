// cl: /O1 /G7 /MD /EHsc /Oi- /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/shims/iniexception
// stlport
//
// Rva003A47F3Parse, retail 0x003A47F3 (461 B). INI block parser for one upgrade-creation trigger
// (WorldBuilder twin 0x00FA67E0 carries the debug string "parseUpgradeCreation: Too many triggers,
// can only have %d."): a trigger holds a unit name, an FX list and two ModelCondition flag sets read
// from the tokens UNIT / NEWMODELCONDITION / FX / SPAWNERMODELCONDITION. The finished record is
// appended to the owner's vector at +8 when it names a unit and the new-condition set is not empty.
// Evidence: target bytes (0xA0-byte record built by the rowed ctor 0x00469187, rowed condition
// parser 0x0033394D, rowed push_back 0x003A47B9, the 0x4B limit and its INIException text) and the
// WorldBuilder twin. The owner class and the function name stay address-derived.
#include "ascii_string.h"
#include "Common/INIException.h"
#include <vector>
#include <string.h>

#include "../../Include/Common/INI/INI.h"

class FXList;
#include "../../Include/GameClient/FXListStore.h"
extern FXListStore *TheFXListStore;

class Rva000B664E
{
public:
	void rva0033394D(AsciiString);
	unsigned words[19];
};

class Rva00469187
{
public:
	Rva00469187();
	AsciiString unit;
	const FXList *fx;
	Rva000B664E newModel;
	Rva000B664E spawnerModel;
};

struct BfmePod160 { int a[40]; };
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod160, BfmePod160>(BfmePod160 *__p, const BfmePod160 &__val); }
template <> void _STL::vector<BfmePod160, _STL::allocator<BfmePod160> >::push_back(const BfmePod160 &);

class Rva003A47F3Owner
{
public:
	char pad00[8];
	_STL::vector<BfmePod160> triggers;
};

void Rva003A47F3Parse(INI *ini, Rva003A47F3Owner *owner)
{
	if (owner->triggers.size() >= 0x4B)
		throw INIException(1, "parseUpgradeCreation: Too many triggers, can only have %d.", 0x4B);
	Rva00469187 rec;
	const char *token = ini->getNextTokenOrNull(ini->m_sepsColon);
	while (token != 0 && *token != 0)
	{
		if (strcmp(token, "UNIT") == 0)
		{
			token = ini->getNextTokenOrNull(ini->m_sepsColon);
			if (token != 0 && *token != 0)
				rec.unit.set(token);
		}
		else if (strcmp(token, "NEWMODELCONDITION") == 0)
		{
			token = ini->getNextTokenOrNull(ini->m_sepsColon);
			if (token != 0 && *token != 0)
				rec.newModel.rva0033394D(AsciiString(token));
		}
		else if (strcmp(token, "FX") == 0)
		{
			token = ini->getNextTokenOrNull(ini->m_sepsColon);
			if (token != 0 && *token != 0)
				rec.fx = TheFXListStore->findFXList(token);
		}
		else if (strcmp(token, "SPAWNERMODELCONDITION") == 0)
		{
			token = ini->getNextTokenOrNull(ini->m_sepsColon);
			if (token != 0 && *token != 0)
				rec.spawnerModel.rva0033394D(AsciiString(token));
		}
		token = ini->getNextTokenOrNull(ini->m_sepsColon);
	}
	if (!rec.unit.isEmpty())
	{
		for (unsigned i = 0; i < 19; ++i)
		{
			if (rec.newModel.words[i] != 0)
			{
				owner->triggers.push_back(*(const BfmePod160 *)&rec);
				break;
			}
		}
	}
}
