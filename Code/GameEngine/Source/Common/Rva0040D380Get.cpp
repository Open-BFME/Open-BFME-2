// cl: /MD
// ?rva0040D380@ArmySummarySystem@@QAEHH@Z @0x0040D380 22B: army lookup 0x0040D008 then
// +0x2c (the state 0x0040F7E5 advances 3 -> 4) or 1 when null. Evidence: calls
// rowed 0x0040D008 on its own this; single caller GameLogic forwarder 0x0023D075
// (add ecx, 0x184; jmp). WorldBuilder's GetArmyReinforcementStateByID is the
// likely name (unproven: its body was not compared).
class BfmeY1038
{
public:
	char m_pad0[0x2c];
	int m_2c;
};
#include "../../Include/Common/ArmySummarySystem.h"
int ArmySummarySystem::rva0040D380(int v)
{
	BfmeY1038 *y = (BfmeY1038 *)rva0040D008(v);
	if (y == 0)
		return 1;
	return y->m_2c;
}
