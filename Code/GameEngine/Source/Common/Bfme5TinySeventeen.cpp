// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Five more tiny ones: a pair of floats accumulated from a caller's pair, a
// search for the first free slot of twelve, an unsigned count turned into a
// float and subtracted, a countdown that reloads itself, and a pair written
// into an indexed object.

class BfmeOwnerCH
{
public:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeReload;					// +0x08
};

class Gen_00291BB0
{
public:
	unsigned char bfmeTick(void);

private:
	int m_bfmeTag;						// +0x00
	BfmeOwnerCH *m_bfmeOwner;				// +0x04
	int m_bfmeGap[6];					// +0x08
	int m_bfmeCount;					// +0x20
};

// ?bfmeTick@Gen_00291BB0@@QAEEXZ
unsigned char Gen_00291BB0::bfmeTick(void)
{
	int count = m_bfmeCount;

	if (count == 0)
	{
		m_bfmeCount = m_bfmeOwner->m_bfmeReload;

		return 1;
	}

	m_bfmeCount = count - 1;

	return 0;
}