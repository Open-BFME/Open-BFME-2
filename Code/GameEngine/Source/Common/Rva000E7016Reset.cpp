// cl: /MD
// ?rva000E7016@W3DShrubBuffer@@QAEXXZ 0x000E7016 195B
// Reset after Rva000E6AC0::rva000E65B1: release FirstElem pair at +0x19EC/+0x19F0
// stride 0xA0 bounded by count at +0x4FB58, zero floats at +0x1948/+0x194C,
// reload floats at +0x1950/+0x1954 from g_Va00BBB8D8, clear count, set dirty
// at +0x4FB5C, release 0x40 RefItem array at +0x4FB70 stride 0x5C, fill -1 over
// [0x5C0,0x1948), zero tail at +0x51270.
// Evidence: calls rowed rva000E65B1; count/dirty/tail offsets match Rva000E6FE3
// W3DShrubBuffer::rva000E76B8 neighbours and W3DTreeBuffer second-array pattern; callers at
// 0x0006D5DE 0x000E9BCA 0x000E9CAD 0x000682B2. 0x000E9CAD is the W3DShrubBuffer
// ctor on its own this; +0x4FB58/+0x4FB70/+0x51270 are its count, type array
// and type count, past the Rva000E6AC0 base.

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

struct ShrubRecord
{
	unsigned char pad00[0x44];
	unsigned char flag;
	unsigned char pad0[3];
	unsigned char data0[0x10];
	unsigned key;
	unsigned char pad5C[0x28];
	unsigned guard;
	unsigned char pad88[8];
	unsigned state;
	RefItem *p0;
	RefItem *p1;
	unsigned char pad9C[4];
};

struct SecondElem
{
	RefItem *p;
	char pad[0x5C - 4];
};

extern float g_Va00BBB8D8;

struct FloatPair;

class W3DShrubBuffer
{
public:
	int getPartitionBucket(FloatPair const *p);
	bool rva000E90DB(unsigned key, int mode);
	void startMorph(int index, int mode);
	void rva000E7016();
	unsigned char m_pad0[0x5C0];
	int m_fill[0x4E2];
	float m_minX;
	float m_minY;
	float m_maxX;
	float m_maxY;
	ShrubRecord m_records[2000];
	int m_count;
	unsigned char m_dirty;
	char _pad2[0x4FB70 - 0x4FB5D];
	SecondElem m_array2[0x40];
	int m_tail;
};

void W3DShrubBuffer::rva000E7016()
{
	((Rva000E6AC0 *)this)->rva000E65B1();
	for (int i = 0; i < m_count; ++i)
	{
		RefItem *refItem = m_records[i].p0;
		if (refItem != 0)
		{
			if (--refItem->m_ref == 0)
				refItem->Release();
			m_records[i].p0 = 0;
		}
		RefItem *p1 = m_records[i].p1;
		if (p1 != 0)
		{
			if (--p1->m_ref == 0)
				p1->Release();
			m_records[i].p1 = 0;
		}
	}
	m_minY = 0.0f;
	m_minX = 0.0f;
	float tmp = g_Va00BBB8D8;
	m_count = 0;
	m_maxY = tmp;
	m_maxX = tmp;
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
