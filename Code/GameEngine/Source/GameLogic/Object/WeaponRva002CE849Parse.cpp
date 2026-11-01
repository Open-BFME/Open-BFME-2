// cl: /DNDEBUG /MD /EHs-c- /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ?Rva002CE849Parse@@YAXPAVINI@@PAX@Z @0x002CE849 97B: INI X/Y float plus unsigned parse pushing Coord3D to vector at +0x4C via rowed push_back 0x002CE7DC.
// Evidence: chain lane calls 0x002CE7DC; callees rowed getNextSubToken 0x2E06B scanReal 0x2EDA5 scanUnsignedInt 0x2ED3A; no callers.
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
#include "../../../../Libraries/Include/Lib/Coord3D.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void vector<Coord3D,allocator<Coord3D> >::push_back(Coord3D const &); }
// bfme link decl-only begin
namespace _STL { template <> void vector<Coord3D, allocator<Coord3D> >::_M_insert_overflow(Coord3D *, Coord3D const &, __false_type const &, unsigned int, bool); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
// bfme link decl-only end
// Declaration-only _Construct: retail's push_back calls the pinned out-of-line
// helper (0x002CA82C) instead of inlining the element copy (row 35 family-LK3).
namespace _STL {
template <> void _Construct<Coord3D, Coord3D>(Coord3D *, const Coord3D &);
}
#include "../../../Include/Common/INI/INI.h"
// g_00BBE3C8 was the retail address alias (RVA 0x007BE3C8) of the constant "X"; the literal is the source.
// g_00BBE3C4 was the retail address alias (RVA 0x007BE3C4) of the constant "Y"; the literal is the source.
struct Rva002CE849Holder {
  char m_pad[0x4C];
  _STL::vector<Coord3D> m_vec;
};
void Rva002CE849Parse(INI *ini, void *instance)
{
  Coord3D tmp;
  tmp.x = ini->scanReal(ini->getNextSubToken("X"));
  tmp.y = ini->scanReal(ini->getNextSubToken("Y"));
  *(unsigned int *)&tmp.z = ini->scanUnsignedInt(ini->getNextSubToken("T"));
  ((Rva002CE849Holder *)instance)->m_vec.push_back(tmp);
}
