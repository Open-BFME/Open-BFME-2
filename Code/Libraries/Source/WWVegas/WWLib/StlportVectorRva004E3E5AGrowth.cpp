// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Target4E2F54/4E2F7A are38B/37B construction loops called by the
// rowed push_back4E3E5A family's overflow4E3D52. Both step32 and call
// the same full45B rowed _Construct4E2F27. Preserve that existing element
// name as an opaque32B ABI view; its original name and payload are unknown.
// The native default/copy/destruction chain ties it to the existing opaque
// Rva004E2382 owner (ctor4E2382 and dtor4E2941); no set<AsciiString> or
// vector payload inference is carried from that owner's older views.
#include <vector>
struct Rva004E3E5AElement {
 unsigned char unknown[32];
 Rva004E3E5AElement(const Rva004E3E5AElement&);
 ~Rva004E3E5AElement();
};
namespace _STL {
template<> void _Construct<Rva004E3E5AElement,Rva004E3E5AElement>(Rva004E3E5AElement*,const Rva004E3E5AElement&);
}
template Rva004E3E5AElement *_STL::__uninitialized_copy<Rva004E3E5AElement*,Rva004E3E5AElement*>(Rva004E3E5AElement*,Rva004E3E5AElement*,Rva004E3E5AElement*,const _STL::__false_type&);
template Rva004E3E5AElement *_STL::__uninitialized_fill_n<Rva004E3E5AElement*,unsigned int,Rva004E3E5AElement>(Rva004E3E5AElement*,unsigned int,const Rva004E3E5AElement&,const _STL::__false_type&);

// Keep the existing complete cleanup provider and its destruction identity.
namespace _STL {template<> void vector<Rva004E3E5AElement>::_M_clear();}
template void _STL::vector<Rva004E3E5AElement>::_M_insert_overflow(Rva004E3E5AElement*,const Rva004E3E5AElement&,const _STL::__false_type&,unsigned int,bool);
