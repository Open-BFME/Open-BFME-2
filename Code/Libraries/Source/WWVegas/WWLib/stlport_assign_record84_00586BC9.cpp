// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4BfmeAssignRecord84@@QAEAAU0@ABU0@@Z @0x00586BC9 78B
// Copy assignment over int veda3 veda3 byte ints dequeE12 int via rowed deque
// assign 0x00586A9C. Evidence: leaf lane called by 3 matched rows; pin name;
// prev/next record bodies; unblocks none (leaf end).
// The emitted unsigned max copy must match retail RVA 0x00013740.
// Define it for speed, then restore this unit's flags for its own bodies.
#include <stl/_algobase.h>
#pragma optimize("s", off)
#pragma optimize("t", on)
namespace _STL {
template <> inline const unsigned int &max<unsigned int>(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#pragma optimize("", on)

#include <deque>

struct BfmeE12
{
	int m_00;
	int m_04;
	int m_08;
};
// Reuse the retail 12-byte-POD iterator operation at 0x00585A18.
typedef _STL::_Deque_iterator<BfmeE12, _STL::_Nonconst_traits<BfmeE12> > BfmeE12CopyIterator;
namespace _STL {
template <> BfmeE12CopyIterator copy_backward<BfmeE12CopyIterator, BfmeE12CopyIterator>(
    BfmeE12CopyIterator, BfmeE12CopyIterator, BfmeE12CopyIterator);
}

struct Ints12
{
	int m_00;
	int m_04;
	int m_08;
};

struct BfmeAssignRecord84
{
	int m_00;
	Ints12 m_04;
	Ints12 m_10;
	unsigned char m_1C;
	char m_pad1D[3];
	int m_20;
	int m_24;
	_STL::deque<BfmeE12> m_28;
	int m_50;
	BfmeAssignRecord84 &operator=(const BfmeAssignRecord84 &other);
};

BfmeAssignRecord84 &BfmeAssignRecord84::operator=(const BfmeAssignRecord84 &other)
{
	m_00 = other.m_00;
	m_04 = other.m_04;
	m_10 = other.m_10;
	m_1C = other.m_1C;
	m_20 = other.m_20;
	m_24 = other.m_24;
	m_28 = other.m_28;
	m_50 = other.m_50;
	return *this;
}
