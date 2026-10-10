// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??4BfmeAssignRecord84@@QAEAAU0@ABU0@@Z @0x00586BC9 78B
// Copy assignment over int veda3 veda3 byte ints dequeE12 int via rowed deque
// assign 0x00586A9C. Evidence: leaf lane called by 3 matched rows; pin name;
// prev/next record bodies; unblocks none (leaf end).
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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
// The complete deque assignment has a matched provider in stlport_deque_e12_o1.cpp.
template <> deque<BfmeE12> &deque<BfmeE12>::operator=(const deque<BfmeE12> &);
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
