// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Three more: a constructor seeded from three globals, a two-level
// comparator, and an angle from an inline arctangent.

class BfmeItemEG
{
public:
	int m_bfmeHead[5];					// +0x00
	int m_bfmeMinor;					// +0x14
	int m_bfmeMajor;					// +0x18
};

// ?bfmeLess@@YA_NPBVBfmeItemEG@@0@Z
bool __cdecl bfmeLess(const BfmeItemEG *first, const BfmeItemEG *second)
{
	if (first->m_bfmeMajor < second->m_bfmeMajor)
		return true;

	if (first->m_bfmeMajor > second->m_bfmeMajor)
		return false;

	return first->m_bfmeMinor < second->m_bfmeMinor;
}
