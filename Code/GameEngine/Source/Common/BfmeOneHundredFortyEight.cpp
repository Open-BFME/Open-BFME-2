// Four short pieces of chain and record keeping (trimmed to the placed
// link-drop body; the other three are declared-only here).

class BfmeHolderXU
{
public:
	unsigned char m_bfmeHead[0x58];		// 0x00
	unsigned char m_bfmeBusy;		// 0x58
};

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

// ?bfmeDropXX@BfmeLinkXX@@QAEXXZ
void BfmeLinkXX::bfmeDropXX(void)
{
	if (m_bfmeOn != 0)
	{
		if (m_bfmeBack != 0)
			m_bfmeBack->m_bfmeOn = m_bfmeOn;

		m_bfmeOn->m_bfmeBack = m_bfmeBack;
		m_bfmeOn = 0;
	}
}

struct BfmeNodeXZ;
struct BfmeHeadXZ;
void __stdcall bfmeInsertXZ(BfmeHeadXZ *head, BfmeNodeXZ *node, BfmeNodeXZ *after);
