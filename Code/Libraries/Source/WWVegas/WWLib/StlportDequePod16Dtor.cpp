// cl: /EHsc- /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$deque@UBfmePod16@@V?$allocator@UBfmePod16@@@_STL@@@_STL@@QAE@XZ @0x0054FF17 87B
// STLport 4.5.3 deque<T>::~deque for a 16-byte record with a non-trivial
// destructor: destroy [begin, end) through the out-of-line
// _Destroy<_Deque_iterator<BfmePod16>> already rowed at 0x0054FEC8 (which
// names the element), then the _Deque_base destructor, folded at 0x0054FAAC.
// Same 87B EH shape and flags as the deque<BfmeOpaqueOwnedRecord492>
// destructor in StlportOwnedRecordDeque.cpp. Callers include
// ??1Rva006609D0 at 0x0054FFA5. Only the record's size and its copy and
// destroy declarations are claimed.
#include <deque>

struct BfmePod16
{
	unsigned char bytes[16];
	BfmePod16(const BfmePod16 &);
	~BfmePod16();
};

template _STL::deque<BfmePod16, _STL::allocator<BfmePod16> >::~deque();
