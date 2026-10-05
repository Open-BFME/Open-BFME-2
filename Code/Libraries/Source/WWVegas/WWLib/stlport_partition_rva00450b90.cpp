// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$partition@PAPAURva00450B90Item@@VRva00450B90Predicate@@@_STL@@YAPAPAURva00450B90Item@@PAPAU1@0VRva00450B90Predicate@@@Z retail 0x00301295 27B
// Evidence: unlock lane; 3-arg wrapper over rowed __partition 0x003008A0;
// donor Code/GameEngine/Source/Common/Rva00450B90PointerPartition.cpp;
// unblocks 0x005BBDAC.
#include <algorithm>

struct Rva00450B90Item
{
	char m_beforeFlags[0x24];
	bool m_flag24;
	bool m_flag25;
	bool m_flag26;
};

class Rva00450B90Predicate
{
public:
	bool operator()(const Rva00450B90Item *item) const
	{
		if ((m_mask & 0x01) != 0 && item->m_flag26)
			goto selected26;
		if ((m_mask & 0x02) == 0 || item->m_flag26)
			return false;

	selected26:
		if ((item->m_flag24 && (m_mask & 0x04) != 0)
				|| (!item->m_flag24 && (m_mask & 0x08) != 0))
			return false;

		return !((item->m_flag25 && (m_mask & 0x10) != 0)
			|| (!item->m_flag25 && (m_mask & 0x20) != 0));
	}

	unsigned int m_mask;
};

template Rva00450B90Item **_STL::partition<Rva00450B90Item **, Rva00450B90Predicate>(Rva00450B90Item **, Rva00450B90Item **, Rva00450B90Predicate);
