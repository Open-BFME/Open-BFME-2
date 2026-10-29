// cl: /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport46
//
// Three STLport _Destroy(T*) instantiations at 0x0022D9D3, 0x0022D9DC and
// 0x0022D9E5 (9B each): load the pointer and tail-jump into the element's
// destructor, the rowed ??1Rva0022D1DF (0x0022D1DF), ??1Rva0022D214
// (0x0022D214) and ??1Rva0022D249 (0x0022D249) in address order. Retail keeps
// no caller of them. The element classes keep their address-derived names;
// only their destructors are needed here.
#include <memory>

class Rva0022D1DF { public: ~Rva0022D1DF(); };
class Rva0022D214 { public: ~Rva0022D214(); };
class Rva0022D249 { public: ~Rva0022D249(); };

template void _STL::_Destroy<Rva0022D1DF>(Rva0022D1DF *);
template void _STL::_Destroy<Rva0022D214>(Rva0022D214 *);
template void _STL::_Destroy<Rva0022D249>(Rva0022D249 *);
