// cl: /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@U?$_Deque_iterator@UBfmeOpaqueOwnedRecord1432@@U?$_Nonconst_traits@UBfmeOpaqueOwnedRecord1432@@@_STL@@@_STL@@@_STL@@YAXU?$_Deque_iterator@UBfmeOpaqueOwnedRecord1432@@U?$_Nonconst_traits@UBfmeOpaqueOwnedRecord1432@@@_STL@@@0@0@Z @0x00556323 41B
// Leaf lane: STLport _Destroy over two 16-byte deque iterators for the
// 1432-byte owned record; pushes 0 and forwards to the rowed __destroy
// 0x00556085. Caller 0x00557B4B sets up iterators from +0 and +0x10.
#include <deque>

struct BfmeOpaqueOwnedRecord1432 {
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[1432];
	};
	BfmeOpaqueOwnedRecord1432();
	BfmeOpaqueOwnedRecord1432(const BfmeOpaqueOwnedRecord1432 &);
	~BfmeOpaqueOwnedRecord1432();
};

typedef _STL::_Deque_iterator<BfmeOpaqueOwnedRecord1432, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1432> > DeqIt1432;

template void _STL::_Destroy<DeqIt1432>(DeqIt1432, DeqIt1432);
