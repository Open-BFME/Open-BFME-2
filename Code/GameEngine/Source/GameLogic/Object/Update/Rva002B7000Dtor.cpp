// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva002B7000Element@@V?$allocator@URva002B7000Element@@@_STL@@@_STL@@QAE@XZ @ 0x002B7000 63B
// Evidence: same 63B EH shape as sibling vector dtor 0x002B703F via twin-pinned _Destroy 0x005F97BC plus rowed _free 0x00030830; unblocks 0x002B964F; beside prev Member44 and next Rva0040DC56 vector.
#include <vector>

// 4-byte owning-reference slot: retail's range destroy 0x005F97BC -> 0x004F72ED
// steps by 4 and releases each slot through 0x005F8FCC with flags 0.
struct Rva002B7000Element
{
	~Rva002B7000Element();
private:
	char m_pad[4];
};

#include "../../../../Include/Common/Rva005F8FCC.h"
namespace _STL {
template<> __declspec(noinline) inline void __destroy_aux<Rva002B7000Element *>(Rva002B7000Element *first, Rva002B7000Element *last, const __false_type &)
{
	for (; first != last; ++first) reinterpret_cast<Rva005F8FCC *>(first)->rva005F8FCC(0);
}
}

template _STL::vector<Rva002B7000Element>::~vector();
