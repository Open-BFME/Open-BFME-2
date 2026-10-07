// cl: /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$_Destroy@U?$_Deque_iterator@UBfmeOpaqueOwnedRecord1408@@U?$_Nonconst_traits@UBfmeOpaqueOwnedRecord1408@@@_STL@@@_STL@@@_STL@@YAXU?$_Deque_iterator@UBfmeOpaqueOwnedRecord1408@@U?$_Nonconst_traits@UBfmeOpaqueOwnedRecord1408@@@_STL@@@0@0@Z @0x0055634C 41B
// Leaf lane sibling of 0x00556323: STLport _Destroy over two 16-byte deque
// iterators for the 1408-byte owned record; pushes 0 and forwards to the
// rowed __destroy 0x005560B2. Caller 0x00557BDC.
#include <deque>

// The +8 stats record's implicit destructor is 0x00385371; only its ABI and
// 0x548-byte extent are consumed here (layout: PersistentStorageThread.cpp).
class PSPlayerAllStats {
public:
	~PSPlayerAllStats();
private:
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[0x548];
	};
};

struct BfmeOpaqueOwnedRecord1408 {
	unsigned int head[2];
	PSPlayerAllStats member;
	unsigned int tail[12];
	BfmeOpaqueOwnedRecord1408();
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &);
};

typedef _STL::_Deque_iterator<BfmeOpaqueOwnedRecord1408, _STL::_Nonconst_traits<BfmeOpaqueOwnedRecord1408> > DeqIt1408;

template void _STL::_Destroy<DeqIt1408>(DeqIt1408, DeqIt1408);
