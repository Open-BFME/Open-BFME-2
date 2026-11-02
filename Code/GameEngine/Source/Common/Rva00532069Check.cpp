// cl: /MD
// ?rva00532069@PathfindZoneManager@@QAE_NHH@Z @ 0x00532069 (88B): __thiscall bounded cell predicate, (a/16,b/16) against m_outer/m_inner, returns cell+0x38 != cell+0x3C.
// Evidence: offsets 0x1BA38/0x1BA3C/0x1BA40 plus 0x44 element stride shared with Rva005312BEClear.cpp siblings (0x00531512 bounded getter shape); idiv-16 coordinate split; caller at 0x002F7886.
class Rva005312BEItem
{
public:
	char m_pad[0x38];
	int m_38;
	int m_3C;
	char m_pad40[0x44 - 0x40];
};
#include "../../Include/GameLogic/PathfindZoneManager.h"
bool PathfindZoneManager::rva00532069(int a, int b)
{
	if (a < 0 || b < 0)
		return false;
	int i = a / 16;
	int j = b / 16;
	if (i >= field1BA3C || j >= field1BA40)
		return false;
	Rva005312BEItem &cell = field1BA38[i][j];
	int *p = &cell.m_38;
	return p[0] != p[1];
}
