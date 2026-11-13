// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native push_back601A3A identifies this overflow60197D and its 12-byte stride.
// STLport 4.5.3 supplies the algorithm; the opaque name preserves the rowed
// caller's ABI view. No original payload type is asserted. /G7 reproduces
// the native allocator's IMUL12 and the overflow register allocation.
// Construction38/fill37/allocator28 are complete verified existing bodies.
// Their existing Coord3D provider labels do not establish this payload type.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "../../../../GameEngine/Include/Common/Rva00601A3AElement.h"
// Retail's element construction calls the rowed copy helper 0x0060173A: forward to it.
class Coord3D;
struct Coord3DBase;
void __cdecl Rva0060173ACopy(Coord3D *dst, const Coord3DBase &src);
namespace _STL {template<> __declspec(dllimport) __forceinline void _Construct<Rva00601A3AElement,Rva00601A3AElement>(Rva00601A3AElement*p,const Rva00601A3AElement&v)
{ Rva0060173ACopy(reinterpret_cast<Coord3D*>(p),reinterpret_cast<const Coord3DBase&>(v)); }}
template void _STL::vector<Rva00601A3AElement>::_M_insert_overflow(Rva00601A3AElement*,const Rva00601A3AElement&,const _STL::__false_type&,unsigned int,bool);
template Rva00601A3AElement *_STL::__uninitialized_copy<Rva00601A3AElement*,Rva00601A3AElement*>(Rva00601A3AElement*,Rva00601A3AElement*,Rva00601A3AElement*,const _STL::__false_type&);
template Rva00601A3AElement *_STL::__uninitialized_fill_n<Rva00601A3AElement*,unsigned int,Rva00601A3AElement>(Rva00601A3AElement*,unsigned int,const Rva00601A3AElement&,const _STL::__false_type&);
template Rva00601A3AElement *_STL::allocator<Rva00601A3AElement>::allocate(unsigned int,const void*) const;
template void _STL::vector<Rva00601A3AElement>::push_back(const Rva00601A3AElement&);
