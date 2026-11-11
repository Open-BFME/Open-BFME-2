// cl: /DNDEBUG /MD /EHsc
// stlport
// ?rva002AC425@Player@@QAEXABV?$vector@HV?$allocator@H@_STL@@@_STL@@@Z @0x002AC425 (26B)
// Player 4-byte-POD vector assign guard: assigns the vector at +0x2F0 (the
// ScienceVec proven by hasScience 0x002AB7D5 and addScience push_back) from
// the src vector only when src is non-empty (begin != end). Uses the int
// spelling of the folded assign (rowed as dup_0021c21b with int pin at
// 0x0021C21B for RankInfo; ScienceType and int are both 4B PODs with identical
// codegen per that row). Caller 0x0040F94F passes [edi+0x1CC] with
// this=Player from getNthPlayer.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> int * allocator<int>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@HV?$allocator@H@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void vector<int, allocator<int> >::_M_clear(); }

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
}

// Native 0x0021C21B is owned by the non-POD-traited four-byte record
// specialization in StlSweepW5Rva0021C21B.cpp. Preserve this caller's
// storage and argument ABI while naming the verified out-of-line provider.
#include "../../../../Libraries/Source/WWVegas/WWLib/Rva0021C21BElement.h"
typedef _STL::vector<Rva0021C21BElement, _STL::allocator<Rva0021C21BElement> > RetailAssignVector;
namespace _STL {
template <> vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &
vector<Rva0021C21BElement, allocator<Rva0021C21BElement> >::operator=(
    const vector<Rva0021C21BElement, allocator<Rva0021C21BElement> > &);
}

typedef std::vector<int> IntVec;

class Player
{
	char m_pad[0x2F0];
	IntVec m_vec2F0; // +0x2F0 (ScienceVec folded as int)
public:
	void rva002AC425(const IntVec &src);
};

void Player::rva002AC425(const IntVec &src)
{
	if (src.begin() != src.end())
		*(RetailAssignVector *)&m_vec2F0 = *(const RetailAssignVector *)&src;
}
