// ??0Rva006CBDE0@@QAE@HPAXPAVAptValue@@@Z
// partial score=0.95 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc
// ??0Rva006CBDE0@@QAE@HPAXPAVAptValue@@@Z @0x006CBDE0 200B Apt value ctor.
// Retail calls base BfmeAptValue(type,0), clears EAStringC at +8, stores vtable
// 0x008E8C24, inits 15 floats (1.0 at +0x0c/+0x18/+0x24/+0x28/+0x2c/+0x30 else
// 0), stores arg2 at +0x4c and arg3 at +0x48 with conditional AddRef, inits
// GC bits at +0x5c/+0x58 and clears bit 5 of base flags. Evidence: unlock lane;
// callees rowed (Bfme HI ctor clear setGCRootCount); 5 callers; unblocks 5.
class BfmeAptValue006DCD20
{
	virtual void vtableSlot0();
	void setTypeAt006DBBC0(int type);
public:
	BfmeAptValue006DCD20(int type, unsigned int unused);
	virtual ~BfmeAptValue006DCD20();
	void setGCRootCount(unsigned int n);
	unsigned int m_flags;
};

class EAStringC
{
public:
	EAStringC() { clear(); }
	EAStringC &clear();
	~EAStringC();
};

class AptValue
{
public:
	virtual void AddRef();
	virtual void Release();
};

class Rva006CBDE0 : public BfmeAptValue006DCD20
{
	EAStringC m_str;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	AptValue *m_48;
	void *m_4c;
	unsigned char m_pad[0x58 - 0x50];
	unsigned int m_58;
	unsigned int m_5c;
public:
	Rva006CBDE0(int type, void *p1, AptValue *p2);
	virtual ~Rva006CBDE0();
};

Rva006CBDE0::Rva006CBDE0(int type, void *p1, AptValue *p2) : BfmeAptValue006DCD20(type, 0)
{
	m_4c = p1;
	m_0c = 0x3F800000;
	m_10 = 0;
	m_14 = 0;
	m_18 = 0x3F800000;
	m_1c = 0;
	m_20 = 0;
	m_24 = 0x3F800000;
	m_28 = 0x3F800000;
	m_2c = 0x3F800000;
	m_30 = 0x3F800000;
	m_34 = 0;
	m_38 = 0;
	m_3c = 0;
	m_40 = 0;
	m_44 = 0;
	m_48 = p2;
	if (p2 != 0)
		p2->AddRef();
	m_5c &= 0xFFF0FFFF;
	*(unsigned short *)&m_5c = 0;
	setGCRootCount(1);
	m_58 |= 0x7FFE0000;
	m_flags &= ~0x20;
}
