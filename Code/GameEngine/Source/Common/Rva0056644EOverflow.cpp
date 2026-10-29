// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
//
// ?_M_insert_overflow@?$vector@URva0056644EElement@@V?$allocator@URva0056644EElement@@@_STL@@@_STL@@IAEXPAURva0056644EElement@@ABU3@ABU__false_type@2@I_N@Z retail 0x0056644E 180B
// Evidence: chain lane; calls allocate 0x002226BE plus copy 0x0052C9AD plus Construct 0x0052C404 plus fill 0x0056574B plus scrap 0x0056612F; caller push_back 0x00566575 55B; sar 4 stride 0x10; prev Pod40 same-shape push_back plus next Rva00566AB7 same flags.
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

// Retail destroys these elements through the rowed ~Rva004E1A04 (called by the
// range destroy 0x0052CEDD that the vector clear 0x0056612F uses).
class Rva004E1A04
{
public:
	~Rva004E1A04();
};

struct Rva0056644EElement {
	char opaque[16];
	Rva0056644EElement(const Rva0056644EElement &);
	Rva0056644EElement &operator=(const Rva0056644EElement &);
	~Rva0056644EElement() { ((Rva004E1A04 *)this)->Rva004E1A04::~Rva004E1A04(); }
};

// Retail's placement copy here is the rowed ?Rva0052C404Construct@@YAXPAXPBX@Z at 0x0052C404;
// bind the calls to that row rather than an unprovided _Construct<Rva0056644EElement>.
void Rva0052C404Construct(void *dest, const void *source);
namespace _STL {
// ?_STL::_Construct absent-from-retail
static __forceinline void _Construct(Rva0056644EElement *dest, const Rva0056644EElement &source)
{
	Rva0052C404Construct(dest, &source);
}
}

template void _STL::vector<Rva0056644EElement>::_M_insert_overflow(
	Rva0056644EElement *, const Rva0056644EElement &,
	const _STL::__false_type &, unsigned int, bool);
template void _STL::vector<Rva0056644EElement>::push_back(const Rva0056644EElement &);
