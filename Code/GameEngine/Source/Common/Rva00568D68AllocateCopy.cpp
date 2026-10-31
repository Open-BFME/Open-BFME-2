// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00568A20>::_M_allocate_and_copy, retail 0x00568D68, 45 bytes.
// Allocates n slots through the end-of-storage proxy (12-byte allocator
// pinned for Rva00568A20 at 0x00395928 as ICF twin of rowed BfmeE12 allocate)
// and copies the range with the rowed __uninitialized_copy at 0x00568C95.
// Spelled after the STLport _Vector_base shape: _M_start at +0 _M_finish
// at +4 the allocating proxy at +8. Callers at 0x00569E57 become ready
// with idiv 0xC stride.

// 12-byte stand-in whose allocator row (0x00395928) retail reuses for every
// 12-byte vector element; same size as Rva00568A20 so the call folds.
struct BfmePoolHolder88;
class BfmePoolRef10
{
	BfmePoolHolder88 *m_target;
public:
	BfmePoolRef10(const BfmePoolRef10 &other);
};
class HostClass005C8E0A;
class Rva00568A20
{
public:
	BfmePoolRef10 m_ref;
	HostClass005C8E0A *m_host;
	unsigned char m_byte;
	char m_pad[3];
	Rva00568A20(const Rva00568A20 &o);
};
#include <vector>

namespace _STL
{
template <> void _Construct<Rva00568A20, Rva00568A20>(Rva00568A20 *, const Rva00568A20 &);
template <> Rva00568A20 *allocator<Rva00568A20>::allocate(unsigned int, const void *) const;
}

template Rva00568A20 *_STL::vector<Rva00568A20, _STL::allocator<Rva00568A20> >::_M_allocate_and_copy<const Rva00568A20 *>(unsigned int, const Rva00568A20 *, const Rva00568A20 *);
