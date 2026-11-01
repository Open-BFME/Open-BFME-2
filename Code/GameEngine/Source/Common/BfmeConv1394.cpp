// Open-BFME5 conversions (trimmed; only bfmeInitVJT is placed, bfmeGoVJU is
// declared-only).

class BfmeMsgVJT
{
public:
	char bfmeGetStrVJT(const char *k, char *b, int n);
};

class BfmeThingVJT
{
public:
	BfmeThingVJT *bfmeInitVJT(BfmeMsgVJT *m);
	BfmeMsgVJT *m_bfme00;
	char m_bfmeStart[0x20];
	char m_bfmeEnd[0x20];
};

// ?bfmeInitVJT@BfmeThingVJT@@QAEPAV1@PAVBfmeMsgVJT@@@Z
BfmeThingVJT *BfmeThingVJT::bfmeInitVJT(BfmeMsgVJT *m)
{
	m_bfme00 = m;
	m->bfmeGetStrVJT("startDate", m_bfmeStart, 0x20);
	m_bfme00->bfmeGetStrVJT("endDate", m_bfmeEnd, 0x20);
	return this;
}

class BfmeStackVJU
{
public:
	void bfmePushVJU();
	void bfmeSetVJU(void *p);
	void bfmePopVJU();
};

