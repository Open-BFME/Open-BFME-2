// cl: /MD
// ?CallArmyToEngageInBattleByID@ArmySummarySystem@@QAEXH@Z @0x0040D396 32B: chain from the army lookup ArmySummarySystem::rva0040D008 0x0040D008 then ArmySummary::rva0040C985 0x0040C985 with TheGameLogic frame does nothing when null. Evidence: calls rowed 0x0040D008 0x0040C985; TheGameLogic at VA 0x009FE78C; single caller jmp at 0x0023D086; prev 0x0040D380 next 0x0040D3B6 in Common.
class BfmeY1038
{
public:
	char m_pad0[0x34];
};
class Rva00DFE78C
{
public:
	char m_pad[0x40];
	int m_40;
};
class GameLogic;
extern GameLogic *TheGameLogic;
#include "../../Include/GameLogic/ArmySummary.h"
class ArmySummarySystem
{
public:
	void CallArmyToEngageInBattleByID(int v);
	void *rva0040D008(int id);
};

void ArmySummarySystem::CallArmyToEngageInBattleByID(int v)
{
	BfmeY1038 *y = (BfmeY1038 *)rva0040D008(v);
	if (y == 0)
		return;
	((ArmySummary *)y)->rva0040C985(((Rva00DFE78C *)TheGameLogic)->m_40);
}
