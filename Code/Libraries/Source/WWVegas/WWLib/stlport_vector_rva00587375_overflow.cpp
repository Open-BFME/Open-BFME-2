// cl: /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva00587375>::_M_insert_overflow, retail 0x00587C40, 189 bytes.
// Masked-identical to landed BfmeFixedObject60; struct spelling for U-mangle.

#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
// Suppress this TU's non-retail copy of ??$fill@PAURva00587375@@U1@@_STL@@YAXPAURva00587375@@0ABU1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00587375;
namespace _STL { template <> void fill<Rva00587375 *,Rva00587375>(Rva00587375 *,Rva00587375 *,Rva00587375 const &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@URva00587375@@V?$allocator@URva00587375@@@_STL@@@_STL@@QAEXPAURva:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00587375;
namespace _STL { template <> void vector<Rva00587375,allocator<Rva00587375> >::_M_fill_insert(Rva00587375 *,unsigned int,Rva00587375 const &); }
// Suppress this TU's non-retail copy of ??$__copy_backward@PAURva00587375@@PAU1@H@_STL@@YAPAURva00587375@@PAU1@00ABUrandom_access_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00587375;
namespace _STL { template <> Rva00587375 * __copy_backward<Rva00587375 *,Rva00587375 *,int>(Rva00587375 *,Rva00587375 *,Rva00587375 *,random_access_iterator_tag const &,int *); }
struct Rva00587375Block16 { unsigned int words[4]; Rva00587375Block16(); };
struct Rva00587375 {
	unsigned int word_00, word_04, word_08;
	Rva00587375Block16 blocks_0C[3];
	Rva00587375();
	Rva00587375(const Rva00587375 &rhs);
	Rva00587375 &operator=(const Rva00587375 &rhs);
};
typedef char Rva00587375Extent[sizeof(Rva00587375) == 60 ? 1 : -1];
// Only the rowed member: the whole-class instantiation also emitted resize(n),
// insert(pos) and push_back(), which need a default constructor and operator=
// this unit never defines (real-link unresolved).
template void _STL::vector<Rva00587375, _STL::allocator<Rva00587375> >::_M_insert_overflow(
	Rva00587375 *, const Rva00587375 &, const _STL::__false_type &, unsigned int, bool);
