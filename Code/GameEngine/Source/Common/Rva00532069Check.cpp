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
class PathfindZoneManager
{
public:
	bool rva00532069(int a, int b);
	char m_pad[0x1BA30];
	unsigned char m_flag1BA30;
	char m_pad2[0x1BA38 - 0x1BA30 - 1];
	Rva005312BEItem **m_ppItems;
	int m_outer;
	int m_inner;
};
bool PathfindZoneManager::rva00532069(int a, int b)
{
	if (a < 0 || b < 0)
		return false;
	int i = a / 16;
	int j = b / 16;
	if (i >= m_outer || j >= m_inner)
		return false;
	Rva005312BEItem &cell = m_ppItems[i][j];
	int *p = &cell.m_38;
	return p[0] != p[1];
}
