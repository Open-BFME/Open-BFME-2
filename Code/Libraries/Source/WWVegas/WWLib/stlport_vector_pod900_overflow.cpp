// cl: /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@UBfmeRecordOwner900@@V?$allocator@UBfmeRecordOwner900@@@_STL@@@_STL@@IAEXPAUBfmeRecordOwner900@@ABU3@ABU__false_type@2@I_N@Z,
// retail 0x004CBA0F, 191 bytes. Dedicated TU.
//
// STLport 4.5.3 vector<BfmeRecordOwner900>::_M_insert_overflow, the growth path.
// Gate wants RecordOwner900 clear-construct (rowed 0x004CB8DE 0x004CB9D5) while
// allocate-copy-fill stay Pod900-ICF (pinned); /G7 for imul homing, _Construct
// declared-only, explicit member instantiation. Element is 900 bytes to match
// the 0x384 stride in retail.
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

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

struct BfmeRecordOwner900
{
	BfmeRecordOwner900(const BfmeRecordOwner900 &other);
	~BfmeRecordOwner900();
	unsigned char m_pad[900];
};

namespace _STL
{
template <> void _Construct<BfmeRecordOwner900, BfmeRecordOwner900>(BfmeRecordOwner900 *, const BfmeRecordOwner900 &);
}

template void _STL::vector<BfmeRecordOwner900>::_M_insert_overflow(
	BfmeRecordOwner900 *,
	const BfmeRecordOwner900 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
