// ?rva0054C64A@Rva0054C64A@@QAEXH@Z
// partial score=0.93 date=2026-10-05
// cl: /O1 /MD
// stlport
// ?rva0054C64A@Rva0054C64A@@QAEXH@Z @ 0x0054C64A 223B
// Sorts deque range [m_begin,m_end) of BfmeCopyRecord8 by mode 1..4 using the
// four rowed deque sorts, then resets m_cur to m_begin. Evidence: retail calls
// 0x0054C476/0x0054C4EB/0x0054C560/0x0054C5D5 selected by dec-chain on [ebp+8],
// empty check of begin._M_cur vs end._M_cur, final 16B copy +0x14 -> +0x04.
#include <algorithm>
#include <deque>

struct Foo00549DCB;

struct BfmeCopyRecord8
{
	Foo00549DCB *a;
	float b;
	BfmeCopyRecord8() {}
	BfmeCopyRecord8(const BfmeCopyRecord8 &o) : a(o.a), b(o.b) {}
};

struct BfmeCopyRecord8Cmp
{
	bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const;
};

struct BfmeCopyRecord8CmpDescending
{
	bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const;
};

struct BfmeCopyRecord8KeyAscending
{
	bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const;
};

struct BfmeCopyRecord8KeyDescending
{
	bool operator()(const BfmeCopyRecord8 &x, const BfmeCopyRecord8 &y) const;
};

typedef _STL::_Deque_iterator<BfmeCopyRecord8, _STL::_Nonconst_traits<BfmeCopyRecord8> > CopyRecord8Iterator;

class Rva0054C64A
{
public:
	void *vfptr;
	CopyRecord8Iterator m_it[3];
	void rva0054C64A(int mode);
};

// ?rva0054C64A@Rva0054C64A@@QAEXH@Z present-unmatched
void Rva0054C64A::rva0054C64A(int mode)
{
	if (m_it[1] == m_it[2])
		return;
	switch (mode) {
	case 1:
		_STL::sort(m_it[1], m_it[2], BfmeCopyRecord8Cmp());
		break;
	case 2:
		_STL::sort(m_it[1], m_it[2], BfmeCopyRecord8CmpDescending());
		break;
	case 3:
		_STL::sort(m_it[1], m_it[2], BfmeCopyRecord8KeyAscending());
		break;
	case 4:
		_STL::sort(m_it[1], m_it[2], BfmeCopyRecord8KeyDescending());
		break;
	default:
		break;
	}
	m_it[0] = m_it[1];
}
