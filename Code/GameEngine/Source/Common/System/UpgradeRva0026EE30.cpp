// cl: /DNDEBUG /MD /EHsc
// ?rva0026EE30@UpgradeTemplate@@QAEHPAX0@Z @ 0x0026EE30 (112B) unlock: difficulty-gated cost factor via rowed Rva002A9BF2 plus pinned Rva002A8AB1 record plus float globals. Evidence: caller 0x005974B3 thiscall ecx=UpgradeTemplate proven by calcCostToBuild same edi; ret 8 two args; TheSkirmishAIManager plus g_Va00BBB8D8 plus BfmeLogicFramesPerSecond; +0x30 factor; +0x854 limit.
class Rva002A9BF2
{
public:
	void *rva002A9BF2();
};

struct Rva002A8AB1Record;
#include "../../../Include/GameLogic/Rva002A8F24.h"

extern class Rva002A8F24 *TheSkirmishAIManager;
extern float g_Va00BBB8D8;
extern int BfmeLogicFramesPerSecond;

#include "../../../Include/Common/Upgrade.h"

int UpgradeTemplate::rva0026EE30(void *arg1, void *arg2)
{
	(void)arg2;
	void *diff = ((Rva002A9BF2 *)arg1)->rva002A9BF2();
	if ((int)diff == 3) {
		if (TheSkirmishAIManager->rva002A8AB1(arg1)) {
			float *limitPtr = (float *)((char *)TheSkirmishAIManager + 0x854);
			float base = g_Va00BBB8D8;
			float v;
			if (base > *limitPtr)
				v = *limitPtr;
			else
				v = base;
			float r = base - v;
			r *= m_buildTime;
			r *= (float)BfmeLogicFramesPerSecond;
			return (int)r;
		}
	}
	float r2 = (float)BfmeLogicFramesPerSecond;
	r2 *= m_buildTime;
	return (int)r2;
}
