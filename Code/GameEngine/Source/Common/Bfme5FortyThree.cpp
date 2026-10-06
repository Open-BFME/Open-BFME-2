// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// A bit test over a word array and a constant select.

class BfmeTripleDL
{
public:
	int m_bfmeData[3];					// 12 bytes
};

class Gen_001EFCE0
{
public:
	int bfmeCost(void) const;

private:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	int m_bfmeHead[17];					// +0x00
	BfmeTripleDL *m_bfmeStart;				// +0x44
	BfmeTripleDL *m_bfmeFinish;				// +0x48
};

// Two constants either way, so the answer comes out as a borrow masked with
// their difference.
// ?bfmeCost@Gen_001EFCE0@@QBEHXZ
int Gen_001EFCE0::bfmeCost(void) const
{
	return bfmeSize() > 0 ? 1 : 0x3FFFFFFF;
}
