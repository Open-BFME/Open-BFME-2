// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport

// ??1?$vector@URva005C847BRecord@@V?$allocator@URva005C847BRecord@@@_STL@@@_STL@@QAE@XZ @0x005C8494 size 63
#include <vector>

struct Rva005C847BRecord {
	~Rva005C847BRecord();
};

template _STL::vector<Rva005C847BRecord>::~vector();
