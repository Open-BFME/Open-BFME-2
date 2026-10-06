// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva007E3190BfmeSendIfState7.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?sendIfState7@BfmeB996@@QAE_NPAVBfmePkt996@@@Z 0x001068A7 (42B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// BfmeB996 state-7 packet send recovered at retail 0x007E3190.

class BfmePkt996
{
public:
	char m_pad[4];
	int m_size;
};

class BfmeDev996S7
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual int send(BfmePkt996 *pkt, int size);
};

class BfmeB996
{
public:
	bool sendIfState7(BfmePkt996 *pkt);

private:
	char m_bfmePad[4];
	BfmeDev996S7 *m_bfmeDev;
	int m_bfmeKind;
};

bool BfmeB996::sendIfState7(BfmePkt996 *pkt)
{
	if (m_bfmeKind == 7)
	{
		BfmeDev996S7 *dev = m_bfmeDev;
		BfmePkt996 *p = pkt;
		int want = p->m_size;
		int got = dev->send(p, want);
		return got == p->m_size;
	}
	return false;
}
