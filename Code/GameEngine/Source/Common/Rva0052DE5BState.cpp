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

#include "../../Include/Common/MixFileInfoBuffer.h"

extern int TheMixFileInfoPool;

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

#include "../../Include/GameLogic/PathfindCell.h"

void PathfindCell::ReleaseInfo()
{
	if ((m_0C & 0xf) == 4)
		return;
	MixFileInfoBuffer *node = (MixFileInfoBuffer *)m_info;
	if (node == 0)
		return;
	for (int i = 0; i < 5; ++i)
	{
		if (node->field14[i] != 0)
			return;
	}
	if (node->field38 != 0)
		return;
	if ((node->m_flags & 0x18) != 0)
		return;
	node->releaseInto(&TheMixFileInfoPool);
	m_info = 0;
}

void PathfindCell::rva0052DED3()
{
	field04 = 0;
	m_zone = 0xffff;
	m_0C = (m_0C & 0xff000010) | 0x10;
	ReleaseInfo();
}

// ??0PathfindCell@@QAE@XZ (formerly rowed as the method rva0052DFF2): the
// default constructor new PathfindCell[] passes to the vector constructor
// iterator in PathfindLayer::allocateCells 0x0036683D.
PathfindCell::PathfindCell()
{
	m_info = 0;
	rva0052DED3();
}

bool PathfindCell::rva0052DFB1(const Rva0052DFB1Arg *arg)
{
	bool result = false;
	unsigned int flags = m_0C;
	if ((flags & 0xf) == 3)
	{
		m_0C = flags & ~0xfu;
		result = true;
	}
	MixFileInfoBuffer *node = (MixFileInfoBuffer *)m_info;
	if (node != 0 && node->field28 == arg->m_value)
	{
		m_0C &= ~0xfu;
		node->field28 = 0;
		ReleaseInfo();
		result = true;
	}
	return result;
}

// WorldBuilder PathfindCell::SetOpen, WB VA 0x012D7A40 (align lead, score 1).
void PathfindCell::SetOpen(bool flag)
{
	if (flag)
		((MixFileInfoBuffer *)m_info)->m_flags |= 8u;
	else
		((MixFileInfoBuffer *)m_info)->m_flags &= ~8u;
}

void PathfindCell::PutOnClosedList(MixFileInfoBuffer **head)
{
	if ((((MixFileInfoBuffer *)m_info)->m_flags & 0x10) != 0)
		return;
	((MixFileInfoBuffer *)m_info)->m_flags |= 0x10u;
	((MixFileInfoBuffer *)m_info)->bfmeLinkInto(head);
}

// WorldBuilder PathfindCell::RemoveFromClosedList, WB VA 0x012D7DC0 (align lead, score 1; no args).
void PathfindCell::RemoveFromClosedList()
{
	((MixFileInfoBuffer *)m_info)->bfmeUnlink();
	((MixFileInfoBuffer *)m_info)->m_flags &= ~0x10u;
}

bool PathfindCell::rva0052DEEF(const Rva0052DEEFArg *a, bool b, In002E6BA1 *c)
{
	unsigned int low = m_0C & 0xFu;
	if (low != 0 && low != 5)
		return false;
	Rva0052DEEFView *view = a->m_254;
	if (view != 0 && view->v8() == 3) {
		m_0C = (m_0C & ~0xCU) | 3U;
		MixFileInfoBuffer *node = (MixFileInfoBuffer *)m_info;
		if (node == 0)
			return true;
		node->field28 &= 0;
		ReleaseInfo();
		return true;
	}
	m_0C = (m_0C & ~0xBU) | 4U;
	MixFileInfoBuffer *node = (MixFileInfoBuffer *)m_info;
	if (node == 0) {
		if (*(MixFileInfoBuffer **)&TheMixFileInfoPool == (MixFileInfoBuffer *)m_info)
			Rva0052DBCDInit();
		node = Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (int)this, c);
		m_info = (PathfindCellInfo *)node;
	} else {
		node->m_0C &= 0;
	}
	((MixFileInfoBuffer *)m_info)->field28 = a->m_74;
	unsigned int nb = (unsigned int)b << 1;
	((MixFileInfoBuffer *)m_info)->m_flags ^= ((nb ^ ((MixFileInfoBuffer *)m_info)->m_flags) & 2u);
	unsigned int v = a->m_04->m_110;
	unsigned int t1 = v >> 10;
	unsigned char c1 = (unsigned char)t1;
	unsigned int t2 = (unsigned int)c1 << 2;
	((MixFileInfoBuffer *)m_info)->m_flags ^= ((t2 ^ ((MixFileInfoBuffer *)m_info)->m_flags) & 4u);
	return true;
}

// ?TheMixFileInfoPool@@3HA: matched references place it at VA 0xe049d0; also referenced as ?g_00A049D0@@3PAVMixFileInfoBuffer@@A.
int TheMixFileInfoPool;
