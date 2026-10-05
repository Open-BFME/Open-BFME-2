// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /O1 /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva002B7000Element@@V?$allocator@URva002B7000Element@@@_STL@@@_STL@@QAE@XZ @ 0x002B7000 63B
// Evidence: same 63B EH shape as sibling vector dtor 0x002B703F via twin-pinned _Destroy 0x005F97BC plus rowed _free 0x00030830; unblocks 0x002B964F; beside prev Member44 and next Rva0040DC56 vector.
#include <vector>

struct Rva002B7000Element
{
	~Rva002B7000Element();
};

template _STL::vector<Rva002B7000Element>::~vector();
