// Open-BFME5 conversions.

class BfmePoolVMP
{
public:
	virtual void bfmeSlot0VMP();
	virtual void bfmeSlot1VMP();
	virtual void bfmeSlot2VMP();
	virtual void bfmeFreeVMP(void *p, int f);
};

class GenAlloc; GenAlloc *Gen007EFFC0();
void bfmeDeleteVMP(void *p, unsigned n);

struct BfmeBufVMP
{
	int m_bfme00;
	int m_bfme04;
	void *m_bfme08;
};

class BfmeCtxVMP
{
public:
	void reset();
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	int m_bfme10;
	int m_bfme14;
	BfmeBufVMP *m_buffer;
};

void BfmeCtxVMP::reset()
{
	BfmeBufVMP *buffer = m_buffer;

	if (buffer != 0)
	{
		((BfmePoolVMP *)Gen007EFFC0())->bfmeFreeVMP(buffer->m_bfme08, 1);
		buffer->m_bfme04 = 0;
		buffer->m_bfme00 = 0;
		buffer->m_bfme08 = 0;
		bfmeDeleteVMP(buffer, 0xc);
	}
	m_bfme04 = 0;
	m_bfme00 = 0;
	m_bfme08 = 0;
	m_bfme0c = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;
	m_buffer = 0;
}
