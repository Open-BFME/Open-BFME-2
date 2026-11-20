// BfmeThingUNC constructor, retail 0x00674ED0 (62B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv1338.cpp
// (BFME1 0x00808FD0). Only the placed constructor is defined here; the
// donor's UNA/UNB/UND helpers stay out, so the unmatched-definition gate
// passes. Retail installs the UNC vtable, runs the base helper, stores the
// owner and int members, takes an id from the global counter, then chains
// owner->mid->sink and registers through the sink vtable slot.

// The deletion and allocation paths use the same native six-slot table as
// BfmeA1053's initialization, now defined there under its existing name.
typedef void (*Bfme1053Slot)();
extern "C" Bfme1053Slot const bfmeVft1053A[6];
extern "C" void *__identifier("??_7Rva00666BA0@@6B@")[];

void bfmeFreeRecUNA(void *p);
void bfmeFreeUNA(void *p, int n);

class BfmeThingUNA
{
public:
	void *bfmeDelUNA(unsigned char flags);
	const void *m_bfmeVft;
	int m_bfme04;
	void *m_bfmeRec;
};

void *BfmeThingUNA::bfmeDelUNA(unsigned char flags)
{
	m_bfmeVft = bfmeVft1053A;
	bfmeFreeRecUNA(m_bfmeRec);
	m_bfmeRec = 0;
	m_bfme04 = 0;
	m_bfmeVft = __identifier("??_7Rva00666BA0@@6B@");
	if (flags & 1)
		bfmeFreeUNA(this, 0x14);
	return this;
}

void *bfmeAllocUNB(unsigned n);
void *bfmeMakeRecUNB(int n);

class BfmeThingUNB
{
public:
	const void *m_bfmeVft;
	int m_bfme04;
	void *m_bfmeRec;
	int m_bfme0c;
	char m_bfme10;
};

BfmeThingUNB *bfmeNewUNB(void)
{
	BfmeThingUNB *p = (BfmeThingUNB *)bfmeAllocUNB(0x14);
	if (p) {
		p->m_bfmeVft = bfmeVft1053A;
		p->m_bfmeRec = bfmeMakeRecUNB(0x1000);
		p->m_bfme04 = 0;
		p->m_bfme0c = 0;
		p->m_bfme10 = 0;
		return p;
	}
	return 0;
}

extern "C" void *__identifier("??_7Gen0080ACD0@@6B@")[];

class BfmeThingUNC;

class BfmeSinkUNC
{
public:
	virtual void bfmeV0UNC() = 0;
	virtual void bfmeRegisterUNC(BfmeThingUNC *p) = 0;
};

struct BfmeMidUNC
{
	char m_bfmePad[0x2a0];
	BfmeSinkUNC *m_bfmeSink;
};

struct BfmeOwnerUNC
{
	char m_bfmePad[0xc];
	BfmeMidUNC *m_bfmeMid;
};

int bfmeNextIdUNC(void);

class Gen_00808B80
{
public:
	void bfmeReset(void);
};
class BfmeThingUNC
{
public:
	BfmeThingUNC(int a, BfmeOwnerUNC *o);
	void *m_bfmeVft;
	int m_bfmeA;
	BfmeOwnerUNC *m_bfmeOwner;
	int m_bfmeId;
	BfmeSinkUNC *m_bfmeSink;
};

// ??0BfmeThingUNC@@QAE@HPAUBfmeOwnerUNC@@@Z, retail 0x00674ED0 (62B).
BfmeThingUNC::BfmeThingUNC(int a, BfmeOwnerUNC *o)
{
	m_bfmeVft = __identifier("??_7Gen0080ACD0@@6B@");
	((Gen_00808B80 *)this)->bfmeReset();
	m_bfmeOwner = o;
	m_bfmeA = a;
	m_bfmeId = bfmeNextIdUNC();
	m_bfmeSink = o->m_bfmeMid->m_bfmeSink;
	m_bfmeSink->bfmeRegisterUNC(this);
}

