// cl: /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 views of target records with nontrivial copy and destruction.
// Sizes, four-byte alignment and lifetime calls are target evidence;
// original record names and member meanings remain unknown.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
#include <queue>
#include <new>

struct BfmeOpaqueOwnedRecord492 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[492];
	};
	BfmeOpaqueOwnedRecord492();
	BfmeOpaqueOwnedRecord492(const BfmeOpaqueOwnedRecord492 &);
	~BfmeOpaqueOwnedRecord492();
};

struct BfmeOpaqueOwnedRecord840 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[840];
	};
	BfmeOpaqueOwnedRecord840();
	BfmeOpaqueOwnedRecord840(const BfmeOpaqueOwnedRecord840 &);
	~BfmeOpaqueOwnedRecord840();
};

// A separate deque node at RVA 0x0055315a advances by 0x580 bytes.
// Its owning type and member meanings are not yet known.
// Its destructor is implicit: the target's out-of-line copy at 0x00555ADF
// is `add ecx, 8; jmp 0x00385371`, so the only nontrivial member sits at +8.
struct BfmeOpaqueOwnedRecord1408Member {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[0x548];
	};
	~BfmeOpaqueOwnedRecord1408Member();
};

// Only the assignment ABI and complete 0x548-byte extent are consumed here.
// The provider's WorldBuilder-backed name and three-block layout are recorded
// in GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp (0x003874B0).
class PSPlayerAllStats {
public:
	PSPlayerAllStats &operator=(const PSPlayerAllStats &);
private:
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[0x548];
	};
};

struct BfmeOwnedRecord1408Tail5 {
	unsigned int values[5];
};

struct BfmeOpaqueOwnedRecord1408 {
	unsigned int head[2];
	BfmeOpaqueOwnedRecord1408Member member;
	BfmeOwnedRecord1408Tail5 tail550;
	unsigned int value564;
	unsigned int value568;
	unsigned int value56C;
	unsigned int value570;
	unsigned int value574;
	unsigned int value578;
	unsigned char value57C;
	unsigned char value57D;
	BfmeOpaqueOwnedRecord1408();
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &);
	BfmeOpaqueOwnedRecord1408 &operator=(const BfmeOpaqueOwnedRecord1408 &);
};

// Ghidra [0x00556132,0x005561CD), 155 bytes, RET 4. Copies the two head
// words, assigns the +8 stats subobject through complete rowed 0x003874B0,
// copies five words at +0x550 as a subobject, then six loose words and two
// flags. The record's original name and tail meanings remain unknown.
BfmeOpaqueOwnedRecord1408 &BfmeOpaqueOwnedRecord1408::operator=(
	const BfmeOpaqueOwnedRecord1408 &other)
{
	head[0] = other.head[0];
	head[1] = other.head[1];
	*(PSPlayerAllStats *)&member = *(const PSPlayerAllStats *)&other.member;
	tail550 = other.tail550;
	value564 = other.value564;
	value568 = other.value568;
	value56C = other.value56C;
	value570 = other.value570;
	value574 = other.value574;
	value578 = other.value578;
	value57C = other.value57C;
	value57D = other.value57D;
	return *this;
}

// A sibling deque at RVA 0x005530d7 advances its node pointer by 0x598.
struct BfmeOpaqueOwnedRecord1432 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[1432];
	};
	BfmeOpaqueOwnedRecord1432();
	BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &);
	~BfmeOpaqueOwnedRecord1432();
};

// The deque at RVA 0x00550a83 advances by 0x864 bytes per node.
struct BfmeOpaqueOwnedRecord2148 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[2148];
	};
	BfmeOpaqueOwnedRecord2148();
	BfmeOpaqueOwnedRecord2148(const BfmeOpaqueOwnedRecord2148 &);
	~BfmeOpaqueOwnedRecord2148();
};

typedef char BfmeOpaqueOwnedRecord492_size_check[
	sizeof(BfmeOpaqueOwnedRecord492) == 492 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord840_size_check[
	sizeof(BfmeOpaqueOwnedRecord840) == 840 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1408_size_check[
	sizeof(BfmeOpaqueOwnedRecord1408) == 1408 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1432_size_check[
	sizeof(BfmeOpaqueOwnedRecord1432) == 1432 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord2148_size_check[
	sizeof(BfmeOpaqueOwnedRecord2148) == 2148 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord492_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord492) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord840_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord840) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1408_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord1408) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1432_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord1432) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord2148_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord2148) == 4 ? 1 : -1];

typedef _STL::deque<BfmeOpaqueOwnedRecord492,
	_STL::allocator<BfmeOpaqueOwnedRecord492> > BfmeDeque492;
typedef _STL::deque<BfmeOpaqueOwnedRecord840,
	_STL::allocator<BfmeOpaqueOwnedRecord840> > BfmeDeque840;
typedef _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> > BfmeDeque1408;
typedef _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> > BfmeDeque1432;
typedef _STL::deque<BfmeOpaqueOwnedRecord2148,
	_STL::allocator<BfmeOpaqueOwnedRecord2148> > BfmeDeque2148;
template class _STL::deque<BfmeOpaqueOwnedRecord492,
	_STL::allocator<BfmeOpaqueOwnedRecord492> >;
template class _STL::deque<BfmeOpaqueOwnedRecord840,
	_STL::allocator<BfmeOpaqueOwnedRecord840> >;
template class _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> >;
template class _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> >;
template class _STL::deque<BfmeOpaqueOwnedRecord2148,
	_STL::allocator<BfmeOpaqueOwnedRecord2148> >;
typedef _STL::queue<BfmeOpaqueOwnedRecord492> BfmeQueue492;
typedef _STL::queue<BfmeOpaqueOwnedRecord840> BfmeQueue840;
template class _STL::queue<BfmeOpaqueOwnedRecord492>;
template class _STL::queue<BfmeOpaqueOwnedRecord840>;

template _STL::_Deque_iterator<BfmeOpaqueOwnedRecord1432, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1432> > &
_STL::_Deque_iterator<BfmeOpaqueOwnedRecord1432, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1432> >::operator++();
template _STL::_Deque_iterator<BfmeOpaqueOwnedRecord1408, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1408> > &
_STL::_Deque_iterator<BfmeOpaqueOwnedRecord1408, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1408> >::operator++();
