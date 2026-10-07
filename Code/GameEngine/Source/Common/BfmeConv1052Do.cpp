// cl: /GS
// BfmeH1052::bfmeDo1052 @ 0x00800BD0 (164B).

void *Rva007F93E0(void *a, void *b, void *c) throw();

// The native calls in 0x0066CFB0 construct the same 0x34-byte message as
// BfmeMsgVJH_ctor.cpp (RVA 0x00655900), write words at +4/+8/+C/+1C/+20,
// then destroy it at 0x00655780. The provider proves a polymorphic vptr
// at +0; retain all existing field offsets and the (char*, int) ABI.
class BfmeMsgVJH
{
public:
	BfmeMsgVJH(char *buf, int n) throw();
	virtual ~BfmeMsgVJH();
	void bfmeSet3VJH(const char *k, int v) throw();

	int m_04;
	int m_08;
	int m_0c;
	char m_pad10[0x0c];
	int m_1c;
	int m_20;
	char m_pad24[0x10];
};

class BfmeI1052
{
public:
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
};

struct BfmeRecord00800C80
{
	int m_value;
	char m_pad[12];
	BfmeI1052 m_item;
};


class BfmeH1052
{
public:
	void bfmeDo1052(int a, BfmeI1052 *p, int r);
	void forward00800C80(BfmeRecord00800C80 *record);

	char m_pad[0x10];
	void *m_10;
};

void BfmeH1052::bfmeDo1052(int a, BfmeI1052 *p, int r)
{
	char buf[0x20];
	char fa = (char)a;
	BfmeMsgVJH msg(buf, 0x20);
	int f04 = p->m_04;
	int f08 = p->m_08;
	int f0c = p->m_0c;
	msg.m_04 = f04;
	msg.m_08 = f08;
	msg.m_0c = f0c;
	msg.m_1c = 0x50524F42;
	msg.m_20 = fa ? (int)0xC0000000 : 0;
	msg.bfmeSet3VJH((char *)"TID", r);
	msg.bfmeSet3VJH("TYPE", 1);
	Rva007F93E0(&msg, "->D", m_10);
}

// BFME1 donor at 0x00800C80 transfers byte-for-byte to BFME2 0x0066D060.
// The target call operands establish record offsets 0 and 0x10; semantic
// record naming remains donor-derived.
void BfmeH1052::forward00800C80(BfmeRecord00800C80 *record)
{
	bfmeDo1052(1, &record->m_item, record->m_value);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeDo1052@Rva00800E50Owner@@QAEXHPAURva00800E50Stamp@@H@Z=?bfmeDo1052@BfmeH1052@@QAEXHPAVBfmeI1052@@H@Z")
