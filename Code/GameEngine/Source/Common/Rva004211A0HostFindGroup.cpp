// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Rva004211A0Host::rva004210F8, retail 0x004210F8 (126 B; WB 0x010EE2D0,
// unnamed; callee of the rowed 0x004211A0): the index of the first group in
// the +0x0C list whose id list (+0x18) holds the template's final-override
// id (+0x14, through Overridable::friend_getFinalOverride 0x00288609),
// else -1. Names are structural.
#include <vector>

#include "../../Include/Common/Overridable.h"

struct Rva004210F8IDView
{
	char m_pad00[0x14];
	int m_id;			// +0x14
};

struct Rva004210F8Group
{
	char m_pad00[0x18];
	_STL::vector<int> m_ids;	// +0x18
};

class Rva004211A0Host
{
public:
	int rva004210F8(const Overridable *thing);
private:
	char m_pad00[0x0C];
	_STL::vector<Rva004210F8Group *> m_groups;	// +0x0C
};

int Rva004211A0Host::rva004210F8(const Overridable *thing)
{
	unsigned int i = 0;
	if (i < m_groups.size())
	{
		Rva004210F8Group **group = m_groups.begin();
		do
		{
			Rva004210F8Group *g = *group;
			unsigned int j = 0;
			if (j < g->m_ids.size())
			{
				int *id = g->m_ids.begin();
				do
				{
					if (*id == ((const Rva004210F8IDView *)thing->friend_getFinalOverride())->m_id)
						return i;
				} while (++j, ++id, j < g->m_ids.size());
			}
		} while (++i, ++group, i < m_groups.size());
	}
	return -1;
}
