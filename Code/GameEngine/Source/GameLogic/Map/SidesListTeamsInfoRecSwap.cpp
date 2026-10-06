// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?swap@TeamsInfoRec@@QAEXPAV1@@Z retail 0x0032B651 63 bytes.
// TeamsInfoRec member-wise swap: rowed Rb_tree<int int> swap at 0x0032AC92
// for the map at +0x00, rowed vector<BfmeE12> swap at 0x00567ECD for the
// vector at +0x0C, plus word swaps for the shorts at +0x18/+0x1A.
// Evidence: TeamsInfoRec at +0xF44/+0xF60 via rowed SidesList::emptyTeams
// at 0x0032D05C and pinned clear at 0x0032C9C6; callers at 0x0032B711
// 0x0032B723 in SidesList swap at 0x0032B690 passing lea +0xF44/+0xF60.

#include <map>
#include <vector>
#include <algorithm>

struct BfmeE12
{
	float x;
	float y;
	float z;
};

class TeamsInfoRec
{
public:
	void swap(TeamsInfoRec *other);

private:
	std::map<int, int> m_map;
	std::vector<BfmeE12> m_vec;
	unsigned short m_s18;
	unsigned short m_s1a;
};

void TeamsInfoRec::swap(TeamsInfoRec *other)
{
	m_map.swap(other->m_map);
	m_vec.swap(other->m_vec);
	std::swap(m_s18, other->m_s18);
	std::swap(m_s1a, other->m_s1a);
}
