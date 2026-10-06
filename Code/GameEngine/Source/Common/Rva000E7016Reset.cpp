// cl: /MD
// ?rva000E7016@Rva000E7016@@QAEXXZ 0x000E7016 195B
// Reset after Rva000E6AC0::rva000E65B1: release FirstElem pair at +0x19EC/+0x19F0
// stride 0xA0 bounded by count at +0x4FB58, zero floats at +0x1948/+0x194C,
// reload floats at +0x1950/+0x1954 from g_Va00BBB8D8, clear count, set dirty
// at +0x4FB5C, release 0x40 RefItem array at +0x4FB70 stride 0x5C, fill -1 over
// [0x5C0,0x1948), zero tail at +0x51270.
// Evidence: calls rowed rva000E65B1; count/dirty/tail offsets match Rva000E6FE3
// Rva000E76B8 neighbours and Rva000EA24D second-array pattern; callers at
// 0x0006D5DE 0x000E9BCA 0x000E9CAD 0x000682B2.

class Rva000E6AC0
{
public:
	void rva000E65B1();
};

class RefItem
{
public:
	virtual void Release();
	int m_ref;
};

struct FirstElem
{
	unsigned char flag;
	unsigned char pad0[3];
	unsigned char data0[0x4C];
	RefItem *p0;
	RefItem *p1;
	unsigned char data1[0xA0 - 0x58];
};

struct SecondElem
{
	RefItem *p;
	char pad[0x5C - 4];
};

extern float g_Va00BBB8D8;

class Rva000E7016
{
public:
	void rva000E7016();
private:
	char _pad0[0x5C0];
	int m_fill[0x4E2];
	float m_f1948;
	float m_f194C;
	float m_f1950;
	float m_f1954;
	char _pad1[0x199C - 0x1958];
	FirstElem m_elems[1999];
	char _gap[0x5C];
	int m_count;
	unsigned char m_dirty;
	char _pad2[0x4FB70 - 0x4FB5D];
	SecondElem m_array2[0x40];
	int m_tail;
};

void Rva000E7016::rva000E7016()
{
	((Rva000E6AC0 *)this)->rva000E65B1();
	for (int i = 0; i < m_count; ++i)
	{
		RefItem *p0 = m_elems[i].p0;
		if (p0 != 0)
		{
			if (--p0->m_ref == 0)
				p0->Release();
			m_elems[i].p0 = 0;
		}
		RefItem *p1 = m_elems[i].p1;
		if (p1 != 0)
		{
			if (--p1->m_ref == 0)
				p1->Release();
			m_elems[i].p1 = 0;
		}
	}
	m_f194C = 0.0f;
	m_f1948 = 0.0f;
	float tmp = g_Va00BBB8D8;
	m_count = 0;
	m_f1954 = tmp;
	m_f1950 = tmp;
	m_dirty = 1;
	for (int i = 0; i < 0x40; ++i)
	{
		RefItem *&slot = m_array2[i].p;
		RefItem *p = slot;
		if (p != 0)
		{
			if (--p->m_ref == 0)
				p->Release();
			slot = 0;
		}
	}
	for (int i = 0; i < 0x4E2; ++i)
		m_fill[i] = -1;
	m_tail = 0;
}
