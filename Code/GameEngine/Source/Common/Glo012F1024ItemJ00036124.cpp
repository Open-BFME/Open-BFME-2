// cl: /DNDEBUG /MD /EHsc
// ?j_00036124@Glo012F1024Item@@QAEXXZ @0x0056552C 176B BFME1 donor j_00036124 adapted to BFME2 layout Outer at +0x9C and single global g_009FE1C8 with rowed forwarders 0x00210EBF 0x00210ECF 0x00210EE1. Evidence: caller 0x005669A3 bfmeEnter plus donor game/GameEngine/Source/Common/Glo012F1024Entry_bfmeStep.cpp plus retail offsets +0x9C +0xA0 stride 0xC inner stride 8.

class LivingWorldManager;
// 0x009FE1C8 under its data-ledger primary name (defined in Rva003FD7CEParse.cpp).
extern LivingWorldManager *TheLivingWorldManager;

class User;
class BfmeIntVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	int *m_bfmeBegin;
	int *m_bfmeEnd;
};
class BfmeElem4Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }
	User **bfmeAt(unsigned int index) const { return m_bfmeBegin + index; }
	User **bfmeBegin(void) const { return m_bfmeBegin; }

	User **m_bfmeBegin;
	User **m_bfmeEnd;
};
class BfmeElem16
{
public:
	char m_bfmeBody[0x10];
};
class BfmeElem16Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem16 *m_bfmeBegin;
	BfmeElem16 *m_bfmeEnd;
};
class BfmeElem20
{
public:
	char m_bfmeHead[0x10];
	unsigned char m_bfmeByte;
	char m_bfmeTail[0x03];
};
class BfmeElem20Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem20 *m_bfmeBegin;
	BfmeElem20 *m_bfmeEnd;
};
class BfmeFlag24
{
public:
	char m_bfmeHead[0x08];
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x0F];
};
class BfmeFlag24Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeFlag24 *m_bfmeBegin;
	BfmeFlag24 *m_bfmeEnd;
};
class BfmeFlag32
{
public:
	char m_bfmeHead[0x1C];
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x03];
};
class BfmeFlag32Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeFlag32 *m_bfmeBegin;
	BfmeFlag32 *m_bfmeEnd;
};
struct BfmeE8
{
	char m_bfmeBody[0x08];
};
class BfmeElem8Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeE8 *m_bfmeBegin;
	BfmeE8 *m_bfmeEnd;
};
class BfmeElem12Rec
{
public:
	char m_bfmeBody[0x0C];
};
class BfmeElem12RecVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem12Rec *m_bfmeBegin;
	BfmeElem12Rec *m_bfmeEnd;
};
class BfmeElem12
{
public:
	BfmeElem8Vector m_bfmeInner;
	char m_bfmeTail[0x04];
};
class BfmeElem12Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem12 *m_bfmeBegin;
	BfmeElem12 *m_bfmeEnd;
};
class BfmeSubA
{
public:
	BfmeSubA() : m_item(0) {}
	BfmeSubA(const BfmeSubA &other);
	~BfmeSubA();

private:
	void *m_item;
};
struct BfmeElem8Str
{
	int m_first;
	BfmeSubA m_name;
};
class BfmeElem8StrVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem8Str *m_bfmeBegin;
	BfmeElem8Str *m_bfmeEnd;
};
// BFME 2's +0x90 vector holds 16-byte entries (0x005652F7 steps by 0x10).
struct Rva005652F7Entry
{
	int m_first;
	int m_second;
	char m_rest[0x10 - 0x08];
};
class Rva005652F7EntryVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	Rva005652F7Entry *m_bfmeBegin;
	Rva005652F7Entry *m_bfmeEnd;
};
class Glo012F1024Item
{
public:
	void bfmeEnter(void);					// ILT 0x0000BC5D

	void j_0003152a(void);
	void j_000250d6(void);
	void j_0001eb9b(void);
	void j_0000df76(void);
	void j_00008053(void);
	void j_0000d1d4(void);
	void j_00010712(void);
	void j_0002d3e4(void);
	bool j_0000ca59(void);
	void j_0002a969(void);
	void j_00021f26(void);
	void j_0002eeec(void);
	void j_00019eca(void);
	void j_00040c32(void);
	void j_00036124(void);
	void j_00010bcc(void);

	void run(void);
	void rva005652F7(void);

	char m_bfmeHead[0x08];
	BfmeElem8StrVector m_bfmeEarly;				// +0x08
	char m_bfmeHeadRest[0x38 - 0x10];
	BfmeIntVector m_bfmeItems;
	char m_bfmeMiddleA[0x44 - 0x40];
	BfmeElem4Vector m_bfmeNames;
	char m_bfmeMiddle[0x6C - 0x4C];
	BfmeElem20Vector m_bfmeTable;
	char m_bfmePad74[0x04];
	BfmeFlag32Vector m_bfmeFlag32;				// +0x78
	char m_bfmePad80[0x04];
	BfmeFlag24Vector m_bfmeFlag24;				// +0x84
	char m_bfmePad8C[0x04];
	Rva005652F7EntryVector m_bfmeFlag20;			// +0x90
	char m_bfmePad98[0x04];
	BfmeElem12Vector m_bfmeOuter;				// +0x9C, 12-byte entries (0x0056552C steps by 0x0C)
	char m_bfmeMiddleB[0xB4 - 0xA4];
	BfmeElem16Vector m_bfmeQueue;
	char m_bfmeMiddleC[0xC0 - 0xBC];
	BfmeElem12Vector m_bfmeOuterC0;
	char m_bfmePadC8[0x04];
	BfmeElem12RecVector m_bfmeLate;				// +0xCC
	char m_bfmeTail[0xDC - 0xD4];
};

class Rva00210EBF
{
public:
	void rva00210EBF();
};

class Rva00210ECF
{
public:
	void rva00210ECF(const BfmeE8 &x);
};

class Rva00210EE1
{
public:
	void rva00210EE1();
};

void Glo012F1024Item::j_00036124()
{
	if (m_bfmeOuter.bfmeSize() != 0)
	{
		((Rva00210EBF *)TheLivingWorldManager)->rva00210EBF();
		for (unsigned int outer = 0; outer < m_bfmeOuter.bfmeSize(); ++outer)
		{
			BfmeElem12 *element = m_bfmeOuter.m_bfmeBegin + outer;
			for (unsigned int inner = 0; inner < element->m_bfmeInner.bfmeSize(); ++inner)
				((Rva00210ECF *)TheLivingWorldManager)->rva00210ECF(*(element->m_bfmeInner.m_bfmeBegin + inner));
		}
		((Rva00210EE1 *)TheLivingWorldManager)->rva00210EE1();
	}
}
