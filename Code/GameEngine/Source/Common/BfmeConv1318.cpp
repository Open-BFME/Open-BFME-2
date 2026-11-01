// A flag-gated stop plus item free (trimmed from a four-body donor; the
// other three are declared-only here).
//
// The T2 body needs two ledger pins at 0x006728E0 (the BFME1 callee carries
// two names for one body); the TU spells the donor's bfmeFreeTMB call.

class BfmeSinkTMB
{
public:
	virtual void bfmeV0TMB() = 0;
	virtual void bfmeStopTMB() = 0;
};

void bfmeFreeTMB(void *p);

class BfmeThingTMB
{
public:
	void bfmeGoTMB();
	char m_bfmePad[4];
	BfmeSinkTMB *m_bfmeSink;
	void *m_bfmeItem;
	int m_bfmeCount;
	char m_bfmeFlag;
};

// ?bfmeGoTMB@BfmeThingTMB@@QAEXXZ
void BfmeThingTMB::bfmeGoTMB()
{
	char f = m_bfmeFlag;
	m_bfmeCount = 0;
	if (f) {
		m_bfmeFlag = 0;
		m_bfmeSink->bfmeStopTMB();
	}
	bfmeFreeTMB(m_bfmeItem);
}




