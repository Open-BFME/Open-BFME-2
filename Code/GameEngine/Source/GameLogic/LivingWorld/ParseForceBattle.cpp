// cl: /DNDEBUG /DWIN32 /MD /EHsc
// ParseForceBattle, retail RVA 0x004E16D9 (123 bytes). Target evidence:
// the callback table at VA 0x00C6CD60 registers ForceBattle to this body, and
// its error branch uses the matching literal at VA 0x00C61ABC. The local record
// spans 0x28 bytes, its target FieldParse table is at VA 0x00C61AE8, and the
// append thunk at RVA 0x0056652F adjusts owner this by +0x14. The record's
// target class identity is unknown; its name is address-derived.
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameLogic/
// LivingWorld/ParseForceBattle.cpp (RVA 0x003B7DC0, 157 bytes). It corroborates
// parser behavior and the eight field names/offsets. Donor type naming is not
// asserted as a target identity.

typedef int Int;

#include "../../../Include/Common/INI/FieldParse.h"


#include "../../../Include/Common/INI/INI.h"

class Rva004E16D9Record
{
public:
	Rva004E16D9Record();
	virtual ~Rva004E16D9Record();

private:
	char m_body[ 0x28 - 4 ];	// +0x04 (vptr at +0x00)
};

struct BfmePod40;

class Rva0056652FOwner
{
public:
  void rva0056652F(const BfmePod40 &record);
};

// Retail VA 0x00C61AE8: eight fields followed by the null sentinel.
// Names, callbacks and offsets come from this table, independently of BFME 1.
extern const FieldParse g_00C61AE8[9] =
{
	{ "Region", INI::parseAsciiString, 0, 0x04 },
	{ "EventName", INI::parseAsciiString, 0, 0x08 },
	{ "Position", INI::parseCoord2D, 0, 0x10 },
	{ "Movie", INI::parseAsciiString, 0, 0x18 },
	{ "PlayNextActAfterMovie", INI::parseBool, 0, 0x1C },
	{ "RemoveEvent", INI::parseBool, 0, 0x1D },
	{ "UseArmy", INI::parseAsciiString, 0, 0x0C },
	{ "ArmyAttackDirection", INI::parseCoord2D, 0, 0x20 },
	{ 0, 0, 0, 0 }
};

// ?ParseForceBattle@@YAXPAVINI@@PAX1PBX@Z
void ParseForceBattle( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva004E16D9Record record;
		ini->initFromINI( &record, g_00C61AE8 );
		((Rva0056652FOwner *)instance)->rva0056652F( *(const BfmePod40 *)&record );
	}
	else
		throw INIException( 3, "ParseForceBattle::Invalid data passed in." );
}

