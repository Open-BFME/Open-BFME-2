// cl: /DNDEBUG /MD /EHsc
// ?rva0026EE30@UpgradeTemplate@@QAEHPAX0@Z @ 0x0026EE30 (112B) unlock: difficulty-gated cost factor via rowed Rva002A9BF2 plus pinned Rva002A8AB1 record plus float globals. Evidence: caller 0x005974B3 thiscall ecx=UpgradeTemplate proven by calcCostToBuild same edi; ret 8 two args; TheSkirmishAIManager plus literal 1.0f plus BfmeLogicFramesPerSecond; +0x30 factor; +0x854 limit.
class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};

struct Rva002A8AB1Record;
#include "../../../Include/GameLogic/Rva002A8F24.h"

extern class Rva002A8F24 *TheSkirmishAIManager;
extern int BfmeLogicFramesPerSecond;

#include "../../../Include/Common/Upgrade.h"

int UpgradeTemplate::rva0026EE30(void *player, void *arg2)
{
	(void)arg2;
	void *diff = ((Rva002A9BF2 *)player)->rva002A9BF2();
	if ((int)diff == 3) {
		if (TheSkirmishAIManager->rva002A8AB1(player)) {
			float *limitPtr = (float *)((char *)TheSkirmishAIManager + 0x854);
			float base = 1.0f;
			float cappedBase;
			if (base > *limitPtr)
				cappedBase = *limitPtr;
			else
				cappedBase = base;
			float excessFrames = base - cappedBase;
			excessFrames *= m_buildTime;
			excessFrames *= (float)BfmeLogicFramesPerSecond;
			return (int)excessFrames;
		}
	}
	float buildFrames = (float)BfmeLogicFramesPerSecond;
	buildFrames *= m_buildTime;
	return (int)buildFrames;
}
