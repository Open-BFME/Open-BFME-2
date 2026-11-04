// cl: /O1 /G7 /arch:SSE /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ArmySummarySystem members over its army id list (+0x14, a vector<int>),
// each id resolved through the rowed lookup 0x0040D008:
//  - GetArmyIDOfFirstWalkOnArmy, retail 0x0040D3FF (64 B; WB 0x0108DEF0,
//    ArmySummary.cpp:2015): the +0x1C id of the first summary whose +0x14
//    flag is set (WB asserts that state), else 0. Reached from GameLogic
//    through the forwarder 0x0023D0B7.
//  - rva0040D2C3, retail 0x0040D2C3 (58 B): sets every summary's +0x2C word
//    to 1. Its name is unknown.
#include <vector>

#include "../../../Include/GameLogic/ArmySummary.h"

class ArmySummarySystem
{
public:
	void *rva0040D008(int id);	// 0x0040D008
	int GetArmyIDOfFirstWalkOnArmy();
	void rva0040D2C3();
private:
	char m_pad00[0x14];
	_STL::vector<int> m_armyIDs;	// +0x14
};

int ArmySummarySystem::GetArmyIDOfFirstWalkOnArmy()
{
	for (unsigned int i = 0; i < m_armyIDs.size(); ++i)
	{
		ArmySummary *summary = (ArmySummary *)rva0040D008(m_armyIDs[i]);
		if (summary && summary->field14)
			return summary->field1C;
	}
	return 0;
}

void ArmySummarySystem::rva0040D2C3()
{
	for (unsigned int i = 0; i < m_armyIDs.size(); ++i)
	{
		ArmySummary *summary = (ArmySummary *)rva0040D008(m_armyIDs[i]);
		if (summary)
			summary->field2C = 1;
	}
}
