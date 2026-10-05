// cl: /O1 /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native push_back601A3A identifies this overflow60197D and its 12-byte stride.
// STLport 4.5.3 supplies the algorithm; the opaque name preserves the rowed
// caller's ABI view. No original payload type is asserted. /G7 reproduces
// the native allocator's IMUL12 and the overflow register allocation.
// Construction38/fill37/allocator28 are complete verified existing bodies.
// Their existing Coord3D provider labels do not establish this payload type.
#include <vector>
struct Rva00601A3AElement {unsigned char unknown[12];};
namespace _STL {template<> void _Construct<Rva00601A3AElement,Rva00601A3AElement>(Rva00601A3AElement*,const Rva00601A3AElement&);}
template void _STL::vector<Rva00601A3AElement>::_M_insert_overflow(Rva00601A3AElement*,const Rva00601A3AElement&,const _STL::__false_type&,unsigned int,bool);
template Rva00601A3AElement *_STL::__uninitialized_copy<Rva00601A3AElement*,Rva00601A3AElement*>(Rva00601A3AElement*,Rva00601A3AElement*,Rva00601A3AElement*,const _STL::__false_type&);
template Rva00601A3AElement *_STL::__uninitialized_fill_n<Rva00601A3AElement*,unsigned int,Rva00601A3AElement>(Rva00601A3AElement*,unsigned int,const Rva00601A3AElement&,const _STL::__false_type&);
template Rva00601A3AElement *_STL::allocator<Rva00601A3AElement>::allocate(unsigned int,const void*) const;

#pragma comment(linker, "/alternatename:??$_Construct@URva00601A3AElement@@U1@@_STL@@YAXPAURva00601A3AElement@@ABU1@@Z=?Rva0060173ACopy@@YAXPAVCoord3D@@ABUCoord3DBase@@@Z")
