// Open-BFME5 conversions (trimmed; only bfmeGo1015L is placed, the rest is
// declared-only).

class BfmeMgr1015
{
public:
	virtual void bfmeVM01015();
	virtual void bfmeVM11015();
	virtual void bfmeVM21015();
	virtual void bfmeFree1015(int h, int f);
};

class GenAlloc; GenAlloc *Gen007EFFC0();

class BfmeL1015
{
public:
	void bfmeGo1015L(void);
	void bfmeReset1015(void);

	char m_bfmePad[0x10];
	int m_bfmeCount;
	int m_bfmeH;
};

// ?bfmeGo1015L@BfmeL1015@@QAEXXZ
void BfmeL1015::bfmeGo1015L(void)
{
	if (m_bfmeH != 0)
		((BfmeMgr1015 *)Gen007EFFC0())->bfmeFree1015(m_bfmeH, 0);

	m_bfmeH = 0;
	m_bfmeCount = 0;
	bfmeReset1015();
}
