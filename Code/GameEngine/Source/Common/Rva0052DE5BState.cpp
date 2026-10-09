// cl: /DNDEBUG /MD /EHsc
//
// PathfindCell::ReleaseInfo (retail 0x0052DE5B, 64 bytes): finish-reset that
// releases the node buffer back to the pool at 0x00A049D0 when the low nibble
// of the state flags is not 4, the node exists, five dwords at +0x14 are all
// zero, the backlink at +0x38 is null and the node flags at +0x2c have none of
// 0x18 set, then clears the node. Ported from Open-BFME-1
// Code/GameEngine/Source/Common/Rva003F7380State.cpp finishReset, with link
// and flag fields shifted +8 (value at +0x28, flags at +0x2c, link at +0x38)
// and the low-nibble mask widened 7 -> 0xf plus five zero-checked dwords at
// +0x14. Callees are declared-only so the gate resolves them; retail homes
// this in esi.

class MixFileInfoBuffer
{
private:
	void bfmeUnlink();
	void bfmeLinkInto(MixFileInfoBuffer **head);
public:
	void releaseInto(void *pool);
	friend class PathfindCell;
};

extern int TheMixFileInfoPool;

struct Rva0052DE5BNode
{
	unsigned char m_pad0[0x14];
	unsigned int m_check[5];
	int m_value;
	unsigned int m_nodeFlags;
	unsigned char m_pad1[8];
	void *m_link;
};

struct In002E6BA1
{
	int m_00;
	int m_04;
};

void Rva0052DBCDInit(void);
MixFileInfoBuffer *Rva002E8B7AInit(MixFileInfoBuffer **pp, int a, In002E6BA1 *in);

class Rva0052DEEFView
{
public:
	virtual int v0();
	virtual int v1();
	virtual int v2();
	virtual int v3();
	virtual int v4();
	virtual int v5();
	virtual int v6();
	virtual int v7();
	virtual int v8();
};

struct Rva0052DEEFInner04
{
	unsigned int _00[0x44];
	unsigned int m_110;
};

struct Rva0052DEEFArg
{
	char _00[4];
	Rva0052DEEFInner04 *m_04;
	char _08[0x6C];
	int m_74;
	char _78[0x1DC];
	Rva0052DEEFView *m_254;
};

struct Rva0052DFB1Arg
{
	unsigned char m_pad[0x74];
	int m_value;
};

class PathfindCell
{
public:
	void ReleaseInfo();
	void rva0052DED3();
	PathfindCell();
	bool rva0052DFB1(const Rva0052DFB1Arg *arg);
	bool rva0052DEEF(const Rva0052DEEFArg *a, bool b, In002E6BA1 *c);
	void rva0052DAE9(bool flag);
	void PutOnClosedList(MixFileInfoBuffer **head);
	void rva0052DAFF();

private:
	Rva0052DE5BNode *m_node;
	unsigned int m_4;
	unsigned short m_8;
	unsigned short m_A;
	unsigned int m_flags;
};

void PathfindCell::ReleaseInfo()
{
	if ((m_flags & 0xf) == 4)
		return;
	Rva0052DE5BNode *node = m_node;
	if (node == 0)
		return;
	for (int i = 0; i < 5; ++i)
	{
		if (node->m_check[i] != 0)
			return;
	}
	if (node->m_link != 0)
		return;
	if ((node->m_nodeFlags & 0x18) != 0)
		return;
	((MixFileInfoBuffer *)node)->releaseInto(&TheMixFileInfoPool);
	m_node = 0;
}

void PathfindCell::rva0052DED3()
{
	m_4 = 0;
	m_8 = 0xffff;
	m_flags = (m_flags & 0xff000010) | 0x10;
	ReleaseInfo();
}

// ??0PathfindCell@@QAE@XZ (formerly rowed as the method rva0052DFF2): the
// default constructor new PathfindCell[] passes to the vector constructor
// iterator in PathfindLayer::allocateCells 0x0036683D.
PathfindCell::PathfindCell()
{
	m_node = 0;
	rva0052DED3();
}

bool PathfindCell::rva0052DFB1(const Rva0052DFB1Arg *arg)
{
	bool result = false;
	unsigned int flags = m_flags;
	if ((flags & 0xf) == 3)
	{
		m_flags = flags & ~0xfu;
		result = true;
	}
	Rva0052DE5BNode *node = m_node;
	if (node != 0 && node->m_value == arg->m_value)
	{
		m_flags &= ~0xfu;
		node->m_value = 0;
		ReleaseInfo();
		result = true;
	}
	return result;
}

void PathfindCell::rva0052DAE9(bool flag)
{
	if (flag)
		m_node->m_nodeFlags |= 8u;
	else
		m_node->m_nodeFlags &= ~8u;
}

void PathfindCell::PutOnClosedList(MixFileInfoBuffer **head)
{
	if ((m_node->m_nodeFlags & 0x10) != 0)
		return;
	m_node->m_nodeFlags |= 0x10u;
	((MixFileInfoBuffer *)m_node)->bfmeLinkInto(head);
}

void PathfindCell::rva0052DAFF()
{
	((MixFileInfoBuffer *)m_node)->bfmeUnlink();
	m_node->m_nodeFlags &= ~0x10u;
}

bool PathfindCell::rva0052DEEF(const Rva0052DEEFArg *a, bool b, In002E6BA1 *c)
{
	unsigned int low = m_flags & 0xFu;
	if (low != 0 && low != 5)
		return false;
	Rva0052DEEFView *view = a->m_254;
	if (view != 0 && view->v8() == 3) {
		m_flags = (m_flags & ~0xCU) | 3U;
		Rva0052DE5BNode *node = m_node;
		if (node == 0)
			return true;
		node->m_value &= 0;
		ReleaseInfo();
		return true;
	}
	m_flags = (m_flags & ~0xBU) | 4U;
	Rva0052DE5BNode *node = m_node;
	if (node == 0) {
		if (*(Rva0052DE5BNode **)&TheMixFileInfoPool == m_node)
			Rva0052DBCDInit();
		node = (Rva0052DE5BNode *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (int)this, c);
		m_node = node;
	} else {
		*(int *)((char *)node + 0x0C) &= 0;
	}
	m_node->m_value = a->m_74;
	unsigned int nb = (unsigned int)b << 1;
	m_node->m_nodeFlags ^= ((nb ^ m_node->m_nodeFlags) & 2u);
	unsigned int v = a->m_04->m_110;
	unsigned int t1 = v >> 10;
	unsigned char c1 = (unsigned char)t1;
	unsigned int t2 = (unsigned int)c1 << 2;
	m_node->m_nodeFlags ^= ((t2 ^ m_node->m_nodeFlags) & 4u);
	return true;
}

// ?TheMixFileInfoPool@@3HA: matched references place it at VA 0xe049d0; also referenced as ?g_00A049D0@@3PAVMixFileInfoBuffer@@A.
int TheMixFileInfoPool;
#pragma comment(linker, "/alternatename:?g_00A049D0@@3PAVMixFileInfoBuffer@@A=?TheMixFileInfoPool@@3HA")
