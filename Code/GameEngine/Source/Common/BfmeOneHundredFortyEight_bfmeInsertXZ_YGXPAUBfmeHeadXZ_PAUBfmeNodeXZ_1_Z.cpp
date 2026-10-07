// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Four short pieces of chain and record keeping.

class BfmeHolderXU
{
public:
	unsigned char m_bfmeHead[0x58];		// 0x00
	unsigned char m_bfmeBusy;		// 0x58
};

class BfmeThingXU
{
public:
	int bfmeFreeXU(void) const;

private:
	int m_bfmeFirst;			// 0x0
	BfmeHolderXU *m_bfmeHolder;		// 0x4
};

// ?BfmeThingXU::bfmeFreeXU present-unmatched
int BfmeThingXU::bfmeFreeXU(void) const
{
	BfmeHolderXU *holder = m_bfmeHolder;

	if (holder != 0 && holder->m_bfmeBusy != 0)
		return 0;

	return 1;
}

class BfmeKeyXW
{
public:
	int bfmeDiffersXW(const BfmeKeyXW *other) const;

private:
	int m_bfmeNumber;			// 0x0
	unsigned short m_bfmeTag;		// 0x4
};

// Complete33B: both mismatch branches enter the return1 block at684B79.
// The old25B claim stopped before it and mislabeled that tail as shadow init.
// ?BfmeKeyXW::bfmeDiffersXW present-unmatched
int BfmeKeyXW::bfmeDiffersXW(const BfmeKeyXW *other) const
{
	if (m_bfmeNumber == other->m_bfmeNumber && m_bfmeTag == other->m_bfmeTag)
		return 0;

	return 1;
}

class BfmeLinkXX;

class BfmeReachXX
{
public:
	BfmeLinkXX *m_bfmeBack;			// 0x00
	unsigned char m_bfmeBody[0xc];		// 0x04
	BfmeReachXX *m_bfmeOn;			// 0x10
};

class BfmeLinkXX
{
public:
	void bfmeDropXX(void);

private:
	unsigned char m_bfmeHead[0x10];		// 0x00
	BfmeReachXX *m_bfmeOn;			// 0x10
	BfmeLinkXX *m_bfmeBack;			// 0x14
};

// BfmeLinkXX::bfmeDropXX is defined with its retail-matched body in Code/GameEngine/Source/Common/BfmeOneHundredFortyEight.cpp (0x00758490).

struct BfmeNodeXZ
{
	BfmeNodeXZ *m_bfmeNext;			// 0x0
};

struct BfmeHeadXZ
{
	BfmeNodeXZ *m_bfmeFirst;		// 0x0
	BfmeNodeXZ *m_bfmeSecond;		// 0x4
};

void __stdcall bfmeInsertXZ(BfmeHeadXZ *head, BfmeNodeXZ *node, BfmeNodeXZ *after)
{
	if (after != 0)
	{
		node->m_bfmeNext = after->m_bfmeNext;
		after->m_bfmeNext = node;
	}
	else
	{
		node->m_bfmeNext = head->m_bfmeSecond;
		head->m_bfmeSecond = node;
	}
}
