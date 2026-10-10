// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?_M_insert_overflow@?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@IAEXPAUQuantityModifier@@ABU3@ABU__false_type@2@I_N@Z @0x0049F729 178B: vector<QuantityModifier> growth path same 178B sar-3 shape as BfmeStringRecord overflow 0x00426DE2; QuantityModifier is ProductionUpdateModuleData +0x1C AsciiString-plus-int 8-byte element proven by ctor TU and caller push_back 0x0049FDC2 via INI parse 0x0049FDF9; calls allocate 0x523D6C plus copy 0x49DD38 plus Construct 0x49DD0B plus fill_n 0x49DD5E plus clear 0x4C3D8B.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <memory>
#include <vector>
#include "ascii_string.h"

struct QuantityModifier
{
	AsciiString m_templateName;
	int m_quantity;
};

namespace _STL {
template <> void _Construct<QuantityModifier, QuantityModifier>(QuantityModifier *, const QuantityModifier &);
}

template void _STL::vector<QuantityModifier>::_M_insert_overflow(
	QuantityModifier *,
	const QuantityModifier &,
	const _STL::__false_type &,
	unsigned int,
	bool);

// ?push_back@?$vector@UQuantityModifier@@V?$allocator@UQuantityModifier@@@_STL@@@_STL@@QAEXABUQuantityModifier@@@Z @0x0049FDC2 55B: vector<QuantityModifier>::push_back fast path via Construct 0x49DD0B else overflow 0x0049F729; caller INI parse 0x0049FDF9 to vector +0x1C.
template void _STL::vector<QuantityModifier>::push_back(const QuantityModifier &);
