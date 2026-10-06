// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Six more: a complement that hands itself back, a clamped difference, a size
// test, a band search, a flag test, and a counter that reports when it fills a
// mask.

class BfmeTripleDF
{
public:
	int m_bfmeData[3];					// 12 bytes
};

class Gen_001EFA70
{
public:
	bool bfmeHasAny(void) const;

private:
	unsigned int bfmeSize(void) const
	{
		return m_bfmeFinish - m_bfmeStart;
	}

	int m_bfmeHead[17];					// +0x00
	BfmeTripleDF *m_bfmeStart;				// +0x44
	BfmeTripleDF *m_bfmeFinish;				// +0x48
};

// ?bfmeHasAny@Gen_001EFA70@@QBE_NXZ
bool Gen_001EFA70::bfmeHasAny(void) const
{
	return bfmeSize() > 0;
}
