// Open-BFME5 conversions (trimmed to the placed URC ctor; the other two are
// declared-only here).

// LINK: the bump call at 0x0061EEC0 is rowed as ?rva0061EEC0@Rva0061EEC0@@QAEXXZ.
class Rva0061EEC0
{
public:
	void rva0061EEC0(void);
};

class BfmeThingURB
{
public:
	int bfmeGoURB(void);
	char m_bfmePad[4];
	int m_bfmeFlags;
};

// ?bfmeGoURB@BfmeThingURB@@QAEHXZ, retail 0x00130FCE (28B).
int BfmeThingURB::bfmeGoURB(void)
{
	((Rva0061EEC0 *)this)->rva0061EEC0();
	return (m_bfmeFlags & 0xff0000) == 0x30000;
}


class BfmeSrcURC
{
public:
	char bfmeFillURC(void *a, char *out, void *n);
};

class BfmeThingURC
{
public:
	BfmeThingURC(BfmeSrcURC *p);
	BfmeSrcURC *m_bfmeOwner;
	char m_sessionId[4];
};

// ??0BfmeThingURC@@QAE@PAVBfmeSrcURC@@@Z
BfmeThingURC::BfmeThingURC(BfmeSrcURC *p)
{
	m_bfmeOwner = p;
	p->bfmeFillURC((char *)"sessionId", m_sessionId, (void *)0x40);
}
