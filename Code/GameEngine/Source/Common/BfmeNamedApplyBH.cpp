// cl: /DNDEBUG /MD /EHsc /Ob2 /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/BfmeNamedApplyBH.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// ScriptActions::bfmeAddBH 0x003C420A (59B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
//
// Open-BFME5: the named apply at retail 0x002F83D0, 62 bytes.  The name is
// handed to the registry by value; nothing happens unless it resolves.

// stlport
#include "ascii_string.h"
#include "GameLogic/ScriptActionsBFME2.h"

class SpecialPowerTemplate;
class SpecialPowerStore
{
public:
	const SpecialPowerTemplate *findSpecialPowerTemplate(AsciiString name);
};

// Retail loads the named store at VA 0x00E02D4C before its template lookup.
extern SpecialPowerStore *TheSpecialPowerStore;

class AsciiString;
class SpecialPowerTemplate;
struct Coord3D;

class BfmeTargetBH
{
public:
	char m_bfmePadTBH[0x38];
	char m_bfmePosition[4];
};

void ScriptActions::bfmeAddBH(const AsciiString &playerName, const AsciiString &name,
		BfmeTargetBH *target)
{
	const SpecialPowerTemplate *found = TheSpecialPowerStore->findSpecialPowerTemplate(name);

	if (found != 0)
		FireSpecialPowerAtPosition(playerName, found,
			(const Coord3D *)target->m_bfmePosition);
}
