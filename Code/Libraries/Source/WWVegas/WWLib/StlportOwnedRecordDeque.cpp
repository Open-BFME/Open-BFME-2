// cl: /G7 /arch:SSE /O1 /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 views of target records with nontrivial copy and destruction.
// Sizes, four-byte alignment and lifetime calls are target evidence;
// original record names and member meanings remain unknown.
#include <deque>
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
struct BfmeOpaqueOwnedRecord1408 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[1408];
	};
	BfmeOpaqueOwnedRecord1408();
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &);
	~BfmeOpaqueOwnedRecord1408();
};

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

typedef char BfmeOpaqueOwnedRecord492_size_check[
	sizeof(BfmeOpaqueOwnedRecord492) == 492 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord840_size_check[
	sizeof(BfmeOpaqueOwnedRecord840) == 840 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1408_size_check[
	sizeof(BfmeOpaqueOwnedRecord1408) == 1408 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1432_size_check[
	sizeof(BfmeOpaqueOwnedRecord1432) == 1432 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord492_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord492) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord840_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord840) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1408_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord1408) == 4 ? 1 : -1];
typedef char BfmeOpaqueOwnedRecord1432_alignment_check[
	__alignof(BfmeOpaqueOwnedRecord1432) == 4 ? 1 : -1];

typedef _STL::deque<BfmeOpaqueOwnedRecord492,
	_STL::allocator<BfmeOpaqueOwnedRecord492> > BfmeDeque492;
typedef _STL::deque<BfmeOpaqueOwnedRecord840,
	_STL::allocator<BfmeOpaqueOwnedRecord840> > BfmeDeque840;
typedef _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> > BfmeDeque1408;
typedef _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> > BfmeDeque1432;
template class _STL::deque<BfmeOpaqueOwnedRecord492,
	_STL::allocator<BfmeOpaqueOwnedRecord492> >;
template class _STL::deque<BfmeOpaqueOwnedRecord840,
	_STL::allocator<BfmeOpaqueOwnedRecord840> >;
template class _STL::deque<BfmeOpaqueOwnedRecord1408,
	_STL::allocator<BfmeOpaqueOwnedRecord1408> >;
template class _STL::deque<BfmeOpaqueOwnedRecord1432,
	_STL::allocator<BfmeOpaqueOwnedRecord1432> >;
