// ?clear@TeamsInfoRec@@QAEXXZ
// partial score=0.9 date=2026-10-04
// cl: /O1
// stlport
// ?clear@TeamsInfoRec@@QAEXXZ retail 0x0032C9C6 58 bytes.
// BFME 2's TeamsInfoRec (layout in SidesListTeamsInfoRecSwap.cpp: map<int,int>
// at +0x00, vector<BfmeE12> at +0x0C, shorts at +0x18/+0x1A) clears by
// swapping its vector with a one-element temporary (vector(size_type) 0x0032BDE7,
// rowed swap 0x00567ECD, temporary's dtor 0x0032C3A3), clearing the map
// (_Rb_tree::clear 0x0032BEBF: erase from the root, reset leftmost / root /
// rightmost / count) and zeroing both shorts. The Zero Hour TeamsInfoRec is a
// different (array) shape; only the name carries over, from the pin's callers
// SidesList::emptyTeams 0x0032D065 / 0x0032D071.

#include <map>
#include <vector>

struct BfmeE12
{
	float x;
	float y;
	float z;
};

class TeamsInfoRec
{
public:
	void clear();

private:
	std::map<int, int> m_map;
	std::vector<BfmeE12> m_vec;
	unsigned short m_s18;
	unsigned short m_s1a;
};

void TeamsInfoRec::clear()
{
	std::vector<BfmeE12>(1).swap(m_vec);
	m_map.clear();
	m_s18 = 0;
	m_s1a = 0;
}
