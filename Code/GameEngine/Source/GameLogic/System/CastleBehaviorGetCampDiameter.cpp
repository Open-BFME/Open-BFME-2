// cl: /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?getCampDiameter@CastleBehavior@@QAEMPBVPlayer@@@Z
// Retail 0x00396E92..0x00396F2C (154 bytes).
// Returns the camp diameter listed for the player's side: walks the 12-byte
// records of the vector at module data +0x5C (two strings and a Real) copying
// each one and returns the Real of the first whose leading string equals the
// player's side string (Player +0x58); 0.0 for a null player or no match.
// Evidence: WorldBuilder 0x00EB9930 (CastleSystem.cpp:771 assert "Need player
// pointer" names CastleBehavior::getCampDiameter) has the same null check
// count/12 loop record copy compare and Real result. Target facts: module
// data at CastleBehavior +4 (as in registerOwnedObject); rowed callees
// record copy 0x00395E75 / record dtor 0x00395D77 (the ledger names the
// copy and the dtor of this one 12-byte record type separately so the view
// derives one name from the other) and StringBase<char>::compare 0x000069D6
// through the shim's non-throwing AsciiString::compare, which is why retail
// stores no EH state between the copy and the compare. Player +0x58 side
// string as in evaluateSkirmishPlayerIsFaction. Record field meanings past
// the side string are not established.
#include <vector>
#include "ascii_string.h"

typedef float Real;

class Player
{
public:
	const AsciiString &getSide() const { return m_side; }
	unsigned char m_pad00[0x58];
	AsciiString m_side; // +0x58
};

struct Rva00395D77
{
	~Rva00395D77();
	AsciiString m_side;  // +0x00
	AsciiString m_text;  // +0x04
	Real m_diameter;     // +0x08
};

struct BfmeStringRecord00395E75 : public Rva00395D77
{
	BfmeStringRecord00395E75(const BfmeStringRecord00395E75 &other);
};

class CastleBehaviorModuleData
{
public:
	unsigned char m_pad00[0x5C];
	_STL::vector<BfmeStringRecord00395E75> m_campDiameters; // +0x5C
};

class CastleBehavior
{
public:
	Real getCampDiameter(const Player *player);
private:
	void *m_vtable;
	const CastleBehaviorModuleData *m_moduleData; // +0x04
};

Real CastleBehavior::getCampDiameter(const Player *player)
{
	if (!player)
		return 0.0f;
	const CastleBehaviorModuleData *data = m_moduleData;
	int count = data->m_campDiameters.size();
	for (int i = 0; i < count; ++i)
	{
		BfmeStringRecord00395E75 record = data->m_campDiameters[i];
		if (record.m_side == player->getSide())
			return record.m_diameter;
	}
	return 0.0f;
}
