// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ??0?$vector@URva00500DA0Element@@V?$allocator@URva00500DA0Element@@@_STL@@@_STL@@QAE@ABV01@@Z @0x00500DA0 96B
// vector<Rva00500DA0Element> copy ctor. 0x14-byte element forces the
// idiv-by-0x14 count shape with __EH_prolog frame. Non-trivial element
// (user-declared dtor) selects the exception-guarded copy path with the
// out-of-line _Vector_base and uninitialized_copy callees, like the rowed
// vector<PrereqUnitRec> copy at 0x002CFE45 (96B idiv 0x0C). Pins carry the
// Rva00500DA0Element spellings to the folded bodies: get_allocator at
// 0x0021983A and _Vector_base at 0x004FF36C and uninitialized_copy PBU at
// 0x005008A0. Callers 0x005017B4 and 0x0059B8FD.
#include <vector>

struct Rva00500DA0Element
{
	unsigned int m_data[5];
	~Rva00500DA0Element() {}
};

template class _STL::vector<Rva00500DA0Element>;
