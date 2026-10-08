// ?bfmeFindByField30@Gen_003BD6A0@@QAEPAVGen_003BD6A0Elem@@H@Z
// partial score=0.8 date=2026-10-08
// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four more tiny ones: a field address with a shared default, a stamp and a
// flag cleared together, an emptiness test that answers through the carry, and
// a flag written into a singleton.

class Gen_003BD6A0Elem
{
public:
	char m_bfmeBytes00[0x24];			// +0x00
	int m_bfmeKey24;					// +0x24
	char m_bfmeBytes28[8];				// +0x28
	int m_bfmeKey30;					// +0x30
	int m_bfmeKey34;					// +0x34
};

class Gen_003BD6A0
{
public:
	int bfmeHasAny(void) const;
	Gen_003BD6A0Elem *bfmeFindByField24(int key);
	Gen_003BD6A0Elem *bfmeFindByField30(int key);
	Gen_003BD6A0Elem *bfmeFindByField34(int key);

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

// ?bfmeFindByField30@Gen_003BD6A0@@QAEPAVGen_003BD6A0Elem@@H@Z
Gen_003BD6A0Elem *Gen_003BD6A0::bfmeFindByField30(int key)
{
	unsigned int i = 0;
	if (m_bfmeFinish - m_bfmeStart != 0) {
		Gen_003BD6A0Elem **begin = (Gen_003BD6A0Elem **)m_bfmeStart;
		Gen_003BD6A0Elem **it = begin;
		do {
			if ((*it)->m_bfmeKey30 == key)
				return begin[i];
			++it;
			++i;
		} while (i < (unsigned int)(m_bfmeFinish - m_bfmeStart));
	}
	return 0;
}

// ?bfmeFindByField24@Gen_003BD6A0@@QAEPAVGen_003BD6A0Elem@@H@Z
Gen_003BD6A0Elem *Gen_003BD6A0::bfmeFindByField24(int key)
{
	unsigned int i = 0;
	if (m_bfmeFinish - m_bfmeStart != 0) {
		Gen_003BD6A0Elem **begin = (Gen_003BD6A0Elem **)m_bfmeStart;
		Gen_003BD6A0Elem **it = begin;
		do {
			if ((*it)->m_bfmeKey24 == key)
				return begin[i];
			++it;
			++i;
		} while (i < (unsigned int)(m_bfmeFinish - m_bfmeStart));
	}
	return 0;
}

// ?bfmeFindByField34@Gen_003BD6A0@@QAEPAVGen_003BD6A0Elem@@H@Z
Gen_003BD6A0Elem *Gen_003BD6A0::bfmeFindByField34(int key)
{
	if (!key)
		return 0;
	unsigned int i = 0;
	if (m_bfmeFinish - m_bfmeStart != 0) {
		Gen_003BD6A0Elem **begin = (Gen_003BD6A0Elem **)m_bfmeStart;
		Gen_003BD6A0Elem **it = begin;
		do {
			if ((*it)->m_bfmeKey34 == key)
				return begin[i];
			++it;
			++i;
		} while (i < (unsigned int)(m_bfmeFinish - m_bfmeStart));
	}
	return 0;
}
