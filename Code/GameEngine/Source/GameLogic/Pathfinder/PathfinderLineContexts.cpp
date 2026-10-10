// cl: /O1 /MD
// Native002ED0CC..002ED159 RET12 (142B). The existing context identity
// Rva002ED15AInfo is independently used by IsHordeMeleeLinePassable
// 2F1BA2 and its typed cell walker2F0CF6; WB D3E6C0 confirms the
// 5C-byte member accesses. ZH linePassableCallback is the semantic lead,
// while the additional16B query/layout and reset counter are target facts.
// Keep the existing generic init ABI; original constructor spelling remains
// unresolved. The count reset precedes the query copy in WB as in retail.
class Object
{
public:
	bool rva0028AC62() const;
	bool rva0028AFBB() const;
};

class Rva002E6FDF
{
public:
	Rva002E6FDF *rva002E6FDF();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	unsigned char m_10;
	unsigned char m_11;
	char m_pad12[2];
	int m_14;
	int m_18;
	int m_1C;
	unsigned char m_20;
	unsigned char m_21;
	char m_pad22[2];
	int m_24;
	unsigned char m_28;
	char m_pad29[3];
	int m_2C;
	unsigned char m_30;
	unsigned char m_31;
	unsigned char m_32;
	char m_pad33[1];
	int m_34;
};

void __cdecl Rva002EBCA7Split(void *p, int *outHalf, unsigned char *outOdd);

struct Rva002ED0CCInner
{
	char m_pad[0x56C];
	int m_56C;
	char m_pad2[0x634 - 0x56C - 4];
	unsigned char m_634;
};

struct Rva002ED0CCBlock16
{
	int m_00;
	unsigned char m_04;
	unsigned char m_05;
	char m_pad06[2];
	int m_08;
	unsigned char m_0C;
	char m_pad0D[3];
};

struct Rva002ED15AInfo
{
public:
	Rva002ED15AInfo *init(void *a, void *b, void *c);
private:
	void *m_00;
	Object *m_04;
	Rva002E6FDF m_08;
	char m_40[8];
	Rva002ED0CCBlock16 m_48;
	int m_58;
};

Rva002ED15AInfo *Rva002ED15AInfo::init(void *a, void *b, void *c)
{
	m_00 = a;
	m_04 = (Object *)b;
	m_08.rva002E6FDF();
	Rva002ED0CCInner *inner = *(Rva002ED0CCInner **)((char *)b + 4);
	unsigned char ok1;
	unsigned char v634;
	int v56c = inner->m_56C;
	v634 = inner->m_634;
	ok1 = ((Object*)b)->rva0028AC62();
	bool ok2 = ((Object*)b)->rva0028AFBB();
	Rva002ED0CCBlock16 *p48 = &m_48;
	p48->m_00 = (int)c;
	p48->m_04 = (v634 == 0);
	p48->m_05 = ok2;
	p48->m_0C = ok1;
	p48->m_08 = v56c - 1;
	m_58 = 0;
	*(Rva002ED0CCBlock16 *)&m_08.m_1C = m_48;
	m_08.m_11 = 0;
	m_08.m_14 = 12;
	Rva002EBCA7Split(m_04, &m_08.m_0C, &m_08.m_10);
	return this;
}

// Native002E931F..002E93A6 RET12 (136B); IsLineBlocked2F1B32 and
// its typed2F0CB7 walker independently identify this related58B context.
// WB D3E0E0 confirms previous coordinates50/54 form one two-int object,
// zeroed before the16B query copy. Radius is0 and centre istrue here.
struct PreviousCellCoord {int x,y;void zero(){x=0;y=0;}};
struct Rva002ED01EInfo
{
public:
	Rva002ED01EInfo *init(void *a, void *b, void *c);
private:
	void *m_00;
	Object *m_04;
	Rva002E6FDF m_08;
	Rva002ED0CCBlock16 m_48;
	PreviousCellCoord previous;
};

Rva002ED01EInfo *Rva002ED01EInfo::init(void *a, void *b, void *c)
{
	m_00 = a;
	m_04 = (Object *)b;
	m_08.rva002E6FDF();
	Rva002ED0CCInner *inner = *(Rva002ED0CCInner **)((char *)b + 4);
	unsigned char ok1;
	unsigned char v634;
	int v56c = inner->m_56C;
	v634 = inner->m_634;
	ok1 = ((Object*)b)->rva0028AC62();
	bool ok2 = ((Object*)b)->rva0028AFBB();
	Rva002ED0CCBlock16 *p48 = &m_48;
	p48->m_00 = (int)c;
	p48->m_04 = (v634 == 0);
	p48->m_05 = ok2;
	p48->m_0C = ok1;
	p48->m_08 = v56c - 1;
	previous.zero();
	*(Rva002ED0CCBlock16 *)&m_08.m_1C = m_48;
	m_08.m_11 = 0;
	m_08.m_14 = 12;
	m_08.m_18=0;
	m_08.m_0C=0;
	m_08.m_10=1;
	return this;
}
