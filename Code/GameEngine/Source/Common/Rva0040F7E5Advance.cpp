// cl: /MD
// ?rva0040F7E5@BfmeY1038@@QAEXXZ @0x0040F7E5 24B: member state advance 3 to 4
// through the 3-zero helper 0x0040F497. Evidence: same +0x2c state word as
// rowed ArmySummarySystem::rva0040D380 0x0040D380; helper read from REL32.
class BfmeY1038
{
public:
	void rva0040F7E5();

private:
	char m_pad[0x2C];
	int m_2C;
};

// 0x0040F497 is rowed as ArmySummary::Load(bool, bool, int) on this.
#include "../../Include/GameLogic/ArmySummary.h"

// ?CallArmyReinforcementIntoBattleByID@ArmySummarySystem@@QAEXH@Z @0x0040FAFE
// 23B: WorldBuilder's twin 0x0108DAC0 bears the name (ArmySummary.cpp:1920) and
// makes the same calls, the army lookup (twin 0x0108E170 of 0x0040D008) on its
// own this, then 0x0040F7E5's twin; GameLogic forwarder 0x0023D08B adds 0x184
// and tail-jumps here.
#include "../../Include/Common/ArmySummarySystem.h"

void BfmeY1038::rva0040F7E5()
{
	if (m_2C == 3) {
		m_2C = 4;
		((ArmySummary *)this)->Load(false, false, 0);
	}
}

void ArmySummarySystem::CallArmyReinforcementIntoBattleByID(int key)
{
	BfmeY1038 *p = (BfmeY1038 *)rva0040D008(key);
	if (!p)
		return;
	p->rva0040F7E5();
}

