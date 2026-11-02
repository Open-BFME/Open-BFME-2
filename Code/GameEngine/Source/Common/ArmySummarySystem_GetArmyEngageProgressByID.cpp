// cl: /MD
// ?GetArmyEngageProgressByID@ArmySummarySystem@@QAEMH@Z @0x0040D3B6 31B: chain from the army lookup ArmySummarySystem::rva0040D008 0x0040D008 then ArmySummary::rva0040C9A4 0x0040C9A4 returns BfmeZeroRange when null. Evidence: calls rowed 0x0040D008 0x0040C9A4; BfmeZeroRange at VA 0x00BBAEAC; single caller jmp at 0x0023D09C; prev 0x0040D380 next 0x0040D3E8 in Common.
class BfmeY1038
{
public:
	char m_pad0[0x34];
};
#include "../../Include/GameLogic/ArmySummary.h"
extern const float BfmeZeroRange;
class ArmySummarySystem
{
public:
	float GetArmyEngageProgressByID(int v);
	void *rva0040D008(int id);
};

float ArmySummarySystem::GetArmyEngageProgressByID(int v)
{
	BfmeY1038 *y = (BfmeY1038 *)rva0040D008(v);
	if (y == 0)
		return BfmeZeroRange;
	return ((ArmySummary *)y)->rva0040C9A4();
}
