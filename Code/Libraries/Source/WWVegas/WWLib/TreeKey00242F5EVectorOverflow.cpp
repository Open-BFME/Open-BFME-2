// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/shims/sweep
// stlport
// STLport 4.5.3 _M_insert_overflow; reference headers at BFME1 revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, BFME2 bfmealloc shim.
// Target 0x005244DC has a complete 178-byte boundary and 8-byte elements.
// Its copy/fill helpers 0x523E01/0x523E27 call placement construction
// 0x523DD4, whose copy constructor is the existing integer/string copy at
// 0xCF475 (integer plus AsciiString). This identifies the element footprint
// and copy behavior. Native Apt adder524845 passes std::make_pair to this
// vector; erase writes its first word, independently proving a mutable pair.
// The int spelling follows the existing producer's source view; signedness
// is not a recovered original signature. The application vector view stays.
// The queue's pair<SubsystemInterface*,void*> identity is refuted by that
// nontrivial copy chain. No SubsystemInterface layout is inferred here.
// All calls and all 178 bytes verify strictly. Allocation 0x523D6C,
// Destroy 0x48CE25 and clear 0xC060A independently reproduce existing bodies.
// The genuine external placement helper owns EH frame523DD4.
#define _STLP_NO_EXCEPTIONS 1
// TU-local overload avoids an incompatible shared max<unsigned> COMDAT.
// It implements the same unsigned comparison used by retail's growth path.
namespace _STL {
// ?max unsigned comparison adapter absent-from-retail
__forceinline const unsigned &max(const unsigned &a,const unsigned &b) {
 return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"
#include "TreeKey00242F5E.h"
extern template void _STL::_Construct<_STL::pair<int, AsciiString>, _STL::pair<int, AsciiString> >(_STL::pair<int, AsciiString> *, const _STL::pair<int, AsciiString> &);
namespace _STL {
// ?_Construct typed placement adapter absent-from-retail
__forceinline void _Construct(TreeKey00242F5E *p,const TreeKey00242F5E &x) {
 _STL::_Construct((_STL::pair<int, AsciiString> *)p, *(const _STL::pair<int, AsciiString> *)&x);
}
}
typedef _STL::vector<TreeKey00242F5E,_STL::allocator<TreeKey00242F5E> > TreeKeyVector;

// The native fill worker belongs to the mutable pair family, not every legacy
// TreeKey vector view. Keep this layout-only bridge inline in the caller.
namespace _STL {
// ?MutablePairFillView absent-from-retail
__forceinline TreeKey00242F5E *__uninitialized_fill_n(TreeKey00242F5E *first, unsigned int n,
 const TreeKey00242F5E &x, const __false_type &tag) {
 return (TreeKey00242F5E *)_STL::__uninitialized_fill_n(
  (_STL::pair<int, AsciiString> *)first,n,*(const _STL::pair<int, AsciiString> *)&x,tag);
}
}
template void TreeKeyVector::_M_insert_overflow(TreeKey00242F5E *,const TreeKey00242F5E &,const _STL::__false_type &,unsigned int,bool);
