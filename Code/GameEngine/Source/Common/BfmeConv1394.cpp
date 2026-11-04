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
	BfmeThingVJT *bfmeInitVJT(BfmeMsgVJT *message);
	BfmeMsgVJT *m_bfme00;
	char m_bfmeStart[0x20];
	char m_bfmeEnd[0x20];
};

// ?bfmeInitVJT@BfmeThingVJT@@QAEPAV1@PAVBfmeMsgVJT@@@Z
BfmeThingVJT *BfmeThingVJT::bfmeInitVJT(BfmeMsgVJT *message)
{
	m_bfme00 = message;
	message->bfmeGetStrVJT("startDate", m_bfmeStart, 0x20);
	m_bfme00->bfmeGetStrVJT("endDate", m_bfmeEnd, 0x20);
	return this;
}
