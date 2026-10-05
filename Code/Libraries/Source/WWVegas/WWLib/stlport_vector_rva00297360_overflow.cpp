// cl: /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva00297360Element@@V?$allocator@VRva00297360Element@@@_STL@@@_STL@@IAEXPAVRva00297360Element@@ABV3@ABU__false_type@2@I_N@Z,
// retail 0x00403AA6, 180 bytes. STLport 4.5.3 vector<Rva00297360Element>::_M_insert_overflow,
// false_type growth path. Element is the stride-0x10 record (int key, AsciiString at +4,
// two trailing ints; layout owner Rva00297360ElementCopy.cpp) whose _M_clear is the rowed
// 30B tidy at 0x0040399F. The range-copy, fill and placement-copy callees are the rowed
// BfmeStringRecord0040360E bodies at 0x00403666/0x0040368C/0x00403639 (identical 16B
// string-at-+4 footprint, ICF twins; Rva spellings pinned there) and allocate is the
// rowed 16B allocator at 0x002226BE (Rva spelling pinned). Caller is the push_back at
// 0x00403E3B; landing this makes it ready. Sits between the PoolKey row at 0x00403A61
// and the AttributeModifierPoolUpdate ctor at 0x00403BEF whose member is this vector.
//
// Retail 0x00403E3B, 55 bytes: vector<Rva00297360Element>::push_back, the fast-path
// caller of the overflow above (slow path) and of the pinned Rva _Construct.
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

class Rva00297360Element
{
	char m_pad[16];

public:
	Rva00297360Element(const Rva00297360Element &that);
	~Rva00297360Element();
};

namespace _STL
{
template <> void _Construct<Rva00297360Element, Rva00297360Element>(Rva00297360Element *, const Rva00297360Element &);
}

template void _STL::vector<Rva00297360Element>::_M_insert_overflow(
	Rva00297360Element *,
	const Rva00297360Element &,
	const _STL::__false_type &,
	unsigned int,
	bool);

template void _STL::vector<Rva00297360Element>::push_back(const Rva00297360Element &);
