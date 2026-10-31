// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
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
#include <vector>
#include "ascii_string.h"

class Rva00297360Element
{
public:
	Rva00297360Element(const Rva00297360Element &that);
	~Rva00297360Element();
	int index;
	AsciiString name;
	unsigned expiration;
	unsigned upgrade;
};

// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

// Retail's placement copy here is the rowed _Construct<BfmeStringRecord0040360E> at 0x00403639;
// bind the calls to that row rather than an unprovided _Construct<Rva00297360Element>.
struct BfmeStringRecord0040360E;
namespace _STL { template <> void _Construct<BfmeStringRecord0040360E, BfmeStringRecord0040360E>(
	BfmeStringRecord0040360E *, const BfmeStringRecord0040360E &); }
namespace _STL
{
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva00297360Element *dest, const Rva00297360Element &source)
{
	_Construct<BfmeStringRecord0040360E, BfmeStringRecord0040360E>(
		reinterpret_cast<BfmeStringRecord0040360E *>(dest),
		*reinterpret_cast<const BfmeStringRecord0040360E *>(&source));
}
}

// bfme link decl-only begin
namespace _STL { template <> void vector<Rva00297360Element,_STL::allocator<Rva00297360Element> >::_M_clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<Rva00297360Element *,Rva00297360Element,_STL::allocator<Rva00297360Element> >::deallocate(Rva00297360Element *,unsigned int); }
namespace _STL { template <> void allocator<Rva00297360Element>::deallocate(Rva00297360Element *,unsigned int) const; }
// bfme link decl-only end

template void _STL::vector<Rva00297360Element>::_M_insert_overflow(
	Rva00297360Element *,
	const Rva00297360Element &,
	const _STL::__false_type &,
	unsigned int,
	bool);

template void _STL::vector<Rva00297360Element>::push_back(const Rva00297360Element &);
