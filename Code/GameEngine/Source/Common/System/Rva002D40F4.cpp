// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /EHsc
//
// ?rva002D40F4@Rva002D3573@@QAEXXZ retail 0x002D40F4 332B.
// Slot 14 of 0x00802AA8 (class of ??1Rva002D3573@@UAE@XZ in
// Rva002D3573Dtor.cpp). Resets the pointee at +0x10: clears three owned
// holders at +0xC4/+0xC8/+0xCC via OwnedPointerResets rows, zeroes float at
// +0xB0, sets -2 at +0xA4/+0xA8/+0xAC with 0 at +0xA0, clears flag bits at
// +0x7E/+0x7F, sets +0x88=1 +0xE8=0 +0x84=-1 +0xF4=0 +0xF0=-1, releases the
// AsciiString at +0xF8 via shared header, fills [0xFC,0x11C) and
// [0x12C,0x144) with zero BfmeE8 via rowed _STL::fill at 0x000AD7E4, zeroes
// [0x64]->+0x1F4 when set, walks the circular list at +0x148 clearing byte
// +0x14 of each entry, sets +0x7D=1. Caller 0x001042EB (110B) calls this then
// fills its own ranges. Flags follow System /O1 neighbours but use /Os to
// keep retail's late reloads of [this+0x10] and /arch:SSE for movss/xorps.

class Rva000AD6F4
{
public:
	void clear();
private:
	char m_pad[8];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
private:
	char m_pad04[8];
};

#include "Common/Snapshot.h"
#include "ascii_string.h"

class Rva0052710C
{
public:
	~Rva0052710C();
};

class Rva002D3894
{
public:
	Rva0052710C *m_ptr;
	void clear();
};

class Rva00527CCE
{
public:
	~Rva00527CCE();
};

class Rva002D38D1
{
public:
	Rva00527CCE *m_ptr;
	void clear();
};

class Rva00527FA2
{
public:
	~Rva00527FA2();
};

class Rva002D3931
{
public:
	Rva00527FA2 *m_ptr;
	void clear();
};

struct BfmeE8
{
	int a;
	int b;
};

namespace _STL
{
template <typename _ForwardIter, typename _Tp>
void fill(_ForwardIter __first, _ForwardIter __last, const _Tp &__val);
}

struct Rva002D40F4_P64
{
	char m_pad[0x1F4];
	int m1F4;
};

struct Rva002D40F4_EntryMark
{
	char m_pad[0x14];
	unsigned char m14;
};

struct Rva002D40F4_Node
{
	Rva002D40F4_Node *m_next;
	char m_pad04[4];
	Rva002D40F4_EntryMark *m_mark;
};

struct Rva002D40F4_Sub98
{
	char m_pad00[8];
	unsigned char mA0;
	char m_padA1[3];
	int mA4;
	int mA8;
	int mAC;
};

struct Rva002D40F4_Inner
{
	char m_pad00[0x64];
	Rva002D40F4_P64 *m64;
	char m_pad68[0x15];
	unsigned char m7D;
	unsigned char m7E;
	unsigned char m7F;
	char m_pad80[4];
	int m84;
	int m88;
	char m_pad8C[0xC];
	Rva002D40F4_Sub98 m98;
	float mB0;
	char m_padB4[0x10];
	Rva002D3894 mC4;
	Rva002D38D1 mC8;
	Rva002D3931 mCC;
	char m_padD0[0x18];
	int mE8;
	char m_padEC[4];
	int mF0;
	unsigned char mF4;
	char m_padF5[3];
	AsciiString mF8;
	BfmeE8 mFC[4];
	char m_pad11C[0x10];
	BfmeE8 m12C[3];
	char m_pad144[4];
	Rva002D40F4_Node *m148;
};

class Rva002D3573 : public GameEngineDeletingBase, public Snapshot
{
public:
	void rva002D40F4();
	void rva001042EB();
private:
	Rva002D3573 *m_self10;
	char m_pad14[4];
	char m_pad18[0x10];
	BfmeE8 m28[12];
};

void Rva002D3573::rva002D40F4()
{
	Rva002D40F4_Inner *inner = *(Rva002D40F4_Inner **)&m_self10;
	((Rva002D3894 *)((char *)inner + 0xC4))->clear();
	inner = *(Rva002D40F4_Inner **)&m_self10;
	((Rva002D38D1 *)((char *)inner + 0xC8))->clear();
	inner = *(Rva002D40F4_Inner **)&m_self10;
	((Rva002D3931 *)((char *)inner + 0xCC))->clear();
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->mB0 = 0.0f;
	Rva002D40F4_Sub98 *sub = (Rva002D40F4_Sub98 *)((char *)inner + 0x98);
	sub->mA4 = -2;
	sub->mA8 = -2;
	sub->mAC = -2;
	sub->mA0 = 0;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x01;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x02;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x08;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x10;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x20;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m88 = 1;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->mE8 = 0;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m84 |= -1;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->mF4 = 0;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->mF0 |= -1;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	((StringBase<char> *)&inner->mF8)->clear();
	inner = *(Rva002D40F4_Inner **)&m_self10;
	{
		BfmeE8 zero;
		*(float *)&zero.a = 0.0f;
		*(float *)&zero.b = 0.0f;
		_STL::fill((BfmeE8 *)((char *)inner + 0xFC), (BfmeE8 *)((char *)inner + 0x11C), zero);
	}
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x40;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7E &= (unsigned char)~0x80;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7F &= (unsigned char)~0x01;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	{
		BfmeE8 zero;
		zero.a = 0;
		*(unsigned char *)&zero.b = 0;
		_STL::fill((BfmeE8 *)((char *)inner + 0x12C), (BfmeE8 *)((char *)inner + 0x144), zero);
	}
	inner = *(Rva002D40F4_Inner **)&m_self10;
	Rva002D40F4_P64 *p64 = inner->m64;
	if (p64 != 0)
		p64->m1F4 = 0;
	inner = *(Rva002D40F4_Inner **)&m_self10;
	Rva002D40F4_Node *head = inner->m148;
	Rva002D40F4_Node *cur = head->m_next;
	while (cur != head)
	{
		cur->m_mark->m14 = 0;
		cur = cur->m_next;
	}
	inner = *(Rva002D40F4_Inner **)&m_self10;
	inner->m7D = 1;
}

// ?rva001042EB@Rva002D3573@@QAEXXZ retail 0x001042EB 110B chain of 0x002D40F4.
// Calls rva002D40F4 then fills [0x28,0x48) [0x48,0x68) [0x68,0x88) with zero
// BfmeE8 via the same rowed fill. Same class (same this) and same /Os SSE
// flags as its callee; layout extends Rva002D3573 with 12 BfmeE8 at +0x28.
void Rva002D3573::rva001042EB()
{
	rva002D40F4();
	{
		BfmeE8 zero;
		*(float *)&zero.a = 0.0f;
		*(float *)&zero.b = 0.0f;
		_STL::fill(m28, m28 + 4, zero);
	}
	{
		BfmeE8 zero;
		*(float *)&zero.a = 0.0f;
		*(float *)&zero.b = 0.0f;
		_STL::fill(m28 + 4, m28 + 8, zero);
	}
	{
		BfmeE8 zero;
		*(float *)&zero.a = 0.0f;
		*(float *)&zero.b = 0.0f;
		_STL::fill(m28 + 8, m28 + 12, zero);
	}
}
