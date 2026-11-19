// cl: -DNDEBUG -MD -EHsc -D_STLP_USE_STATIC_LIB -D_STLP_NO_EXCEPTIONS -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport
// ?insert@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@QAEPAVRva0054000B@@PAV3@ABV3@@Z @0x00540731 152B
// Vector single-insert striding 0x28 via rowed Construct 0x00540070 plus rowed copy 0x00540036 plus rowed overflow 0x00540412.
// Evidence: callees rowed except own copy_backward/assign emitted here; callers 0x00540A0C; sibling insert 0x00541D10 same 152B shape with /Os /G7.
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>

// The vector's insert copies elements through Rva0054000B's assignment,
// rowed at 0x00540053 (StlSweepW4Rva00540053.cpp).
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@VRva0054000B@@V?$allocator@VRva0054000B@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class Rva0054000B;
namespace _STL { template <> void vector<Rva0054000B,allocator<Rva0054000B> >::_M_clear(); }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAVRva0054000B@@V1@V?$allocator@VRva0054000B@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> Rva0054000B * _STLP_alloc_proxy<Rva0054000B *,Rva0054000B,allocator<Rva0054000B> >::allocate(unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@VRva0054000B@@@_STL@@QBEXPAVRva0054000B@@I@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).

namespace _STL { template <> void allocator<Rva0054000B>::deallocate(Rva0054000B *,unsigned int) const; }
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

class Rva0054000B
{
public:
	Rva0054000B();
	Rva0054000B(const Rva0054000B &other);
	Rva0054000B &operator=(const Rva0054000B &other);

private:
	char m_pad[40];
};

namespace _STL {
template<> void _Construct<Rva0054000B, Rva0054000B>(Rva0054000B *, const Rva0054000B &);
}

template Rva0054000B *_STL::vector<Rva0054000B>::insert(
	Rva0054000B *, const Rva0054000B &);
