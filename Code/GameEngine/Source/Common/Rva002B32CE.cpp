// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B32CE@Rva002B32CE@@QAE_NXZ @0x002B32CE 87B.
// Filtered all-of loop over pointer vector at +0x10C calling pinned byte predicate
// at 0x00318F42 only when element id at +0x54 matches ref at +0x98 id at +0x14; empty returns true.
// Evidence: same family as 0x002B3288 all-of loop, extra cmp [ecx+0x54] vs [edx+0x14] with ref at +0x98, caller 0x002B5EB5 tests al.
#include <vector>

class Mbr002E0B30
{
public:
	unsigned char pred();
public:
	char m_pad[0x54];
	int m_id;
};

struct Ref002B32CE
{
	char m_pad[0x14];
	int m_id;
};

class Rva002B32CE
{
public:
	bool rva002B32CE();
private:
	char m_pad0[0x98];
	Ref002B32CE *m_ref;
	char m_pad1[0x10C - 0x9C];
	_STL::vector<Mbr002E0B30 *> m_items;
};

bool Rva002B32CE::rva002B32CE()
{
	for (unsigned int i = 0; i < m_items.size(); ++i)
	{
		if (m_items[i]->m_id == m_ref->m_id)
		{
			if (!m_items[i]->pred())
				return false;
		}
	}
	return true;
}
