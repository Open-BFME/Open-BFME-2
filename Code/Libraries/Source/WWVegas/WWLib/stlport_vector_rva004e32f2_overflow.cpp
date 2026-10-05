// cl: /G7 /arch:SSE /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?_M_insert_overflow@?$vector@VRva004E32F2@@V?$allocator@VRva004E32F2@@@_STL@@@_STL@@IAEXPAVRva004E32F2@@ABV3@ABU__false_type@2@I_N@Z, retail 0x00566ACA, 183 bytes.
// STLport 4.5.3 vector<Rva004E32F2>::_M_insert_overflow false_type growth path.
// Evidence: chain lane calls just-landed _Construct 0x0052D4A2; callees uninit_copy 0x0052D4CF fill_n 0x00566A75 allocate shared 24B fold 0x00395944 ScrapStorage 0x00565A24; same 183B shape as rowed 0x00565C34.
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

class Rva004E32F2
{
public:
	Rva004E32F2(const Rva004E32F2 &o);
	virtual ~Rva004E32F2();
private:
	char m_pad[0x14];
};

namespace _STL
{
template <> void _Construct<Rva004E32F2, Rva004E32F2>(Rva004E32F2 *, const Rva004E32F2 &);
}

template void _STL::vector<Rva004E32F2>::_M_insert_overflow(
	Rva004E32F2 *,
	const Rva004E32F2 &,
	const _STL::__false_type &,
	unsigned int,
	bool);
