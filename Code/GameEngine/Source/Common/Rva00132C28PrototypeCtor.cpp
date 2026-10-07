// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
//
// ??0Rva00132C28Prototype@@QAE@PAX00@Z @0x0013213B 80B
// Three-arg ctor for 0x54-byte record: base BfmeThingSJ at +0 via rowed
// 0x001320D0, vtable 0x007D2630 at +0, StringClass at +0x3C via rowed
// 0x000F0ED1, Rva0013101E at +0x40 via rowed 0x0013101E, int zero at +0x50.
// Evidence: caller 0x00132C5D allocates 0x54 and pushes three dwords;
// ret 0xC confirms thiscall; offsets from lea pairs; and-zero tail.
class StringClass
{
public:
	StringClass(const char *name, bool flag);
private:
	char *m_Buffer;
};

class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
	virtual void handle();
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};

class Gen_00920A20
{
public:
	Gen_00920A20(int mode);
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
	int m_bfmeD;
	int m_bfmeE;
};

class BfmeThingSJ : public GenBase009EB7D0
{
public:
	BfmeThingSJ(int what);
	virtual void handle();
	int m_bfme14;
	StringClass m_bfmeName;
	Gen_00920A20 m_bfmeData;
	int m_bfme30;
	int m_bfme34;
	int m_bfme38;
};

class Rva0013101E
{
public:
	Rva0013101E &rva0013101E(const Rva0013101E *src) throw();
	unsigned m_a : 3;
	unsigned m_b : 27;
	unsigned m_c : 1;
	unsigned m_keep : 1;
	unsigned m_d1;
	unsigned m_d2;
	unsigned m_d3;
};

class Rva00132C28Prototype : public BfmeThingSJ
{
public:
	Rva00132C28Prototype(void *a, void *b, void *c);
private:
	StringClass m_3C;
	Rva0013101E m_40;
	int m_50;
};

Rva00132C28Prototype::Rva00132C28Prototype(void *a, void *b, void *c)
	: BfmeThingSJ((int)b)
	, m_3C((const char *)a, false)
{
	m_40.rva0013101E((const Rva0013101E *)c);
	m_50 = 0;
}
