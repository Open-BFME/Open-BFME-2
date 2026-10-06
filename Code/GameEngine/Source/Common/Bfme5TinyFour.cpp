// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more tiny ones: a field address with a shared default, a stamp and a
// flag cleared together, an emptiness test that answers through the carry, and
// a flag written into a singleton.

class Gen_003BD6A0
{
public:
	int bfmeHasAny(void) const;

private:
	int m_bfmeHead[5];					// +0x00
	int *m_bfmeStart;					// +0x14
	int *m_bfmeFinish;					// +0x18
};

// ?bfmeHasAny@Gen_003BD6A0@@QBEHXZ
int Gen_003BD6A0::bfmeHasAny(void) const
{
	return 0 < (unsigned int)(m_bfmeFinish - m_bfmeStart);
}