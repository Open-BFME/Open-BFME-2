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

// PeerResponse is the 840-byte record; OwnedRecord840Copy.cpp rows its copy
// (0x00389C14) and teardown (0x0038A063).
class PeerResponse
{
public:
	PeerResponse(const PeerResponse &that);
	~PeerResponse();
};
struct BfmeOpaqueOwnedRecord840 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[840];
	};
	BfmeOpaqueOwnedRecord840();
	// The record is a PeerResponse: copy and teardown are its rowed members.
	__forceinline BfmeOpaqueOwnedRecord840(const BfmeOpaqueOwnedRecord840 &that)
	{ ((PeerResponse *)this)->PeerResponse::PeerResponse(*(const PeerResponse *)&that); }
	__forceinline ~BfmeOpaqueOwnedRecord840()
	{ ((PeerResponse *)this)->~PeerResponse(); }
};

// A separate deque node at RVA 0x0055315a advances by 0x580 bytes.
// Its owning type and tail meanings are not yet known.
// Its destructor is implicit: the target's out-of-line copy at 0x00555ADF
// is `add ecx, 8; jmp 0x00385371`, so the only nontrivial member sits at +8.

// Only the assignment and destructor ABI and complete 0x548-byte extent are
// consumed here. The provider's WorldBuilder-backed name and three-block
// layout are recorded in GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp
// (operator= 0x003874B0, implicit destructor 0x00385371).
class PSPlayerAllStats {
public:
	PSPlayerAllStats &operator=(const PSPlayerAllStats &);
	~PSPlayerAllStats();
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
	PSPlayerAllStats member;
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
	member = other.member;
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
// Instantiate the recovered queue operations and their storage dependencies.
template void _STL::deque<BfmeOpaqueOwnedRecord492>::push_back(const BfmeOpaqueOwnedRecord492 &);
template void _STL::deque<BfmeOpaqueOwnedRecord492>::pop_front();
template _STL::deque<BfmeOpaqueOwnedRecord492>::~deque();
template void _STL::deque<BfmeOpaqueOwnedRecord840>::push_back(const BfmeOpaqueOwnedRecord840 &);
template void _STL::deque<BfmeOpaqueOwnedRecord840>::pop_front();
template _STL::deque<BfmeOpaqueOwnedRecord840>::~deque();
template _STL::deque<BfmeOpaqueOwnedRecord840>::deque(const _STL::allocator<BfmeOpaqueOwnedRecord840> &);
template class _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> >;
template class _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> >;
template _STL::deque<BfmeOpaqueOwnedRecord2148>::deque(const _STL::allocator<BfmeOpaqueOwnedRecord2148> &);

// BuddyThread.cpp's queue<BuddyResponse> (0x864-byte records, built with exceptions)
// reaches the same no-exception deque base bodies at 0x00550858/0x00550A83/0x00550C06;
// it only declares them, so this unit emits the BuddyResponse-named copies (ICF folds).
// Only the record's size is consumed here.
class BuddyResponse
{
	unsigned int m_words[0x864 / 4];
};
template _STL::_Deque_base<BuddyResponse, _STL::allocator<BuddyResponse> >::_Deque_base(
	const _STL::allocator<BuddyResponse> &, unsigned int);
typedef _STL::queue<BfmeOpaqueOwnedRecord492> BfmeQueue492;
typedef _STL::queue<BfmeOpaqueOwnedRecord840> BfmeQueue840;
template _STL::queue<BfmeOpaqueOwnedRecord492>::queue();
template void _STL::queue<BfmeOpaqueOwnedRecord492>::pop();
template _STL::queue<BfmeOpaqueOwnedRecord840>::queue();
template void _STL::queue<BfmeOpaqueOwnedRecord840>::pop();

template _STL::_Deque_iterator<BfmeOpaqueOwnedRecord1432, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1432> > &
_STL::_Deque_iterator<BfmeOpaqueOwnedRecord1432, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1432> >::operator++();
template _STL::_Deque_iterator<BfmeOpaqueOwnedRecord1408, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1408> > &
_STL::_Deque_iterator<BfmeOpaqueOwnedRecord1408, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1408> >::operator++();
