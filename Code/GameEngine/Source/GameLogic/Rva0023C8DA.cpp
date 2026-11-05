// cl: /O1 /DNDEBUG /MD /EHsc
// Target evidence: Ghidra bounds 0x0023C8DA at 40 bytes. Retail calls the
// pinned 0x00210DC9 query through the 0x00DFE1C8 singleton, then conditionally
// calls 0x0040F87E on this+0x184. Matched GameLogic::LivingWorldTacticalBattleComplete
// confirms GameLogic's +0x184 member is ArmySummarySystem; this method and the
// nested operation's purpose remain address-derived.

class Rva00DFE1C8Host
{
public:
	bool rva00210DC9();
};

// g_00DFE1C8 is only an alias of the owned global TheLivingWorldManager (ledger names column); this unit reads the owner through its own view type.
extern class LivingWorldManager *TheLivingWorldManager;
#define g_00DFE1C8 (*(Rva00DFE1C8Host * *)&TheLivingWorldManager)

#include "../../Include/Common/ArmySummarySystem.h"

class GameLogic
{
public:
	void rva0023C8DA(unsigned char value);

private:
	unsigned char m_pad00[0x184];
	ArmySummarySystem m_armySummarySystem;
};

// ?rva0023C8DA@GameLogic@@QAEXE@Z
// Retail returns with whatever al the last call left and its only caller,
// GameLogic::startNewGame 0x00248558, discards it: the method returns void.
void GameLogic::rva0023C8DA(unsigned char value)
{
	if (g_00DFE1C8->rva00210DC9() && value == 0)
		m_armySummarySystem.rva0040F87E();
}
