// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva001F8C5B@@QAE@ABV?$vector@PAXV?$allocator@PAX@_STL@@@_STL@@@Z, retail 0x001F8C5B, 103 bytes.
//
// Vector ctor at this+0 from a pointer vector: base E16 init, reserve
// src.size, then push each element mapped through virtual slot 1.
// Evidence: callers 0x001F90B8 and 0x001F9CA1; callees rowed Vector_base
// 0x00211E58 plus ModuleData reserve 0x002B712E plus push_back 0x004DFCB0;
// unblocks 0x001F9C73; follows Rva001F8E45 filter shape with slot 1.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class ModuleData;

struct BfmeE16 { float x, y, z, w; };

class Rva001F8C5BIface
{
public:
	virtual void dummy0();
	virtual const ModuleData* getData();
};

class Rva001F8C5B
{
public:
	Rva001F8C5B(const _STL::vector<void*>& src);
private:
	_STL::vector<BfmeE16> m_vec;
};

Rva001F8C5B::Rva001F8C5B(const _STL::vector<void*>& src)
	: m_vec(_STL::allocator<BfmeE16>())
{
	((_STL::vector<const ModuleData*>&)m_vec).reserve(src.size());
	for (void* const* it = (void* const*)src.begin(); it != (void* const*)src.end(); ++it) {
		Rva001F8C5BIface* obj = (Rva001F8C5BIface*)*it;
		const ModuleData* md = obj->getData();
		((_STL::vector<const ModuleData*>&)m_vec).push_back(md);
	}
}
